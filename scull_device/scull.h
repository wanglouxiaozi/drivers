/*
 * scull.h -- definitions for the char module
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
 * $Id: scull.h,v 1.15 2004/11/04 17:51:18 rubini Exp $
 */

#ifndef _SCULL_H_
#define _SCULL_H_

#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */

#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0   /* dynamic major by default */
#endif

/*
struct cdev {
    struct kobject kobj;
    struct module *owner; 
    const struct file_operations *ops;  
    struct list_head list;
    dev_t dev;          
    unsigned int count;
};
 */


struct scull_dev {
	char data[4000];
	unsigned int data_size;
	struct cdev cdev;          /* Char device structure                */
};

extern int scull_major;     /* main.c */


ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
		loff_t *f_pos);
ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
		loff_t *f_pos);

#endif
