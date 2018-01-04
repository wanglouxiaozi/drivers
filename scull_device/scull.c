/*
 * main.c -- the bare scull char module
 *
 * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet
 * Copyright (C) 2001 O'Reilly & Associates
 *
 * The source code in this file can be freely used, adapted,
 * and redistributed in source or binary form, so long as an
 * acknowledgment appears in derived source files.  The citation
 * should list that the code comes from the book "Linux Device
 * Drivers" by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.   No warranty is attached;
 * we cannot take responsibility for errors or fitness for use.
 *
 */

//#include <linux/config.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>        /* printk() */
#include <linux/slab.h>          /* kmalloc() */
#include <linux/fs.h>            /* everything... */
#include <linux/errno.h>         /* error codes */
#include <linux/types.h>         /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>         /* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>

#include <asm/switch_to.h>          /* cli(), *_flags */
#include <asm/uaccess.h>         /* copy_*_user */

#include "scull.h"               /* local definitions */

#define AUTO_CREATE_DEV_INODE

#ifdef AUTO_CREATE_DEV_INODE
#include <linux/device.h>
	struct class *myclass =NULL;
	dev_t dev_num;

#endif


/*
 * Our parameters which can be set at load time.
 */
/*
   MAJOR(dev_t dev)
   MINOR(dev_t dev)
   MKDEV(int major,int minor) 
#define MINORBITS       20
#define MINORMASK       ((1U << MINORBITS) - 1)
#define MAJOR(dev)      ((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev)      ((unsigned int) ((dev) & MINORMASK))
#define MKDEV(ma,mi)    (((ma) << MINORBITS) | (mi))
 */

int scull_major =   SCULL_MAJOR;
int scull_minor =   0;


module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);

MODULE_AUTHOR("Alessandro Rubini, Jonathan Corbet");
MODULE_LICENSE("Dual BSD/GPL");

struct scull_dev *scull_devices;        /* allocated in scull_init_module */


int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev; /* device information */
	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev; /* for other methods */
	return 0;          /* success */
}

int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}


ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
		loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	unsigned long ret;

	void *start;
	start = dev->data;
	if(dev->data_size < count)
		count = dev->data_size;
	ret =copy_to_user(buf, start, count);

	return count;
}

ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
		loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	void *start;
	unsigned long ret;

	start = dev->data;
	if(count > 4000)
		count = 4000 - 1;
	ret = copy_from_user(start, buf, count);
	dev->data_size = count;

	return count;
}


struct file_operations scull_fops = {
	.owner =    THIS_MODULE,
//  .llseek =   scull_llseek,
	.read =     scull_read,
	.write =    scull_write,
//  .ioctl =    scull_ioctl,
	.open =     scull_open,
	.release =  scull_release,
};

/*
 * Finally, the module stuff
 */

/*
 * The cleanup function is used to handle initialization failures as well.
 * Thefore, it must be careful to work correctly even if some of the items
 * have not been initialized
 */

void scull_cleanup_module(void)
{

	dev_t devno = MKDEV(scull_major, scull_minor);

	/*
	   void cdev_del(struct cdev *);
	 */
#ifdef AUTO_CREATE_DEV_INODE
	device_destroy(myclass,dev_num);
	class_destroy(myclass);
#endif

	cdev_del(&scull_devices->cdev);
	kfree(scull_devices);

	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(devno, 1);
}


/*
 * Set up the char_dev structure for this device.
 */

static void scull_setup_cdev(struct scull_dev *dev)
{
	int err, devno = MKDEV(scull_major, scull_minor);
	/*
	   void cdev_init(struct cdev *, const struct file_operations *);
	 */   
	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add (&dev->cdev, devno, 1);
	/* Fail gracefully if need be */
	if (err)
		printk(KERN_NOTICE "Error %d adding scull", err);
}


int scull_init_module(void)
{
	int result;
	dev_t dev = 0;

	/*
	 * Get a range of minor numbers to work with, asking for a dynamic
	 * major unless directed otherwise at load time.
	 */
	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, 1, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor, 1, "scull");
		scull_major = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
		return result;
	}

	/*
	 * allocate the devices -- we can't have them static, as the number
	 * can be specified at load time
	 */
	scull_devices = kmalloc(sizeof(struct scull_dev), GFP_KERNEL);
	if (!scull_devices) {
		result = -ENOMEM;
		goto fail;  /* Make this more graceful */
	}
	memset(scull_devices, 0, sizeof(struct scull_dev));

	/* Initialize each device. */

#ifdef AUTO_CREATE_DEV_INODE
	dev_num = dev;
	myclass = class_create(THIS_MODULE,"scull");
	device_create(myclass,NULL,dev_num,NULL,"scull0");
	//class_device_create(myclass,NULL,dev_num,NULL,"scull0");
#endif
	scull_setup_cdev(scull_devices);


	return 0; /* succeed */

fail:
	scull_cleanup_module();
	return result;
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
