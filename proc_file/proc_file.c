#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>

#define DRV_NAME "proc_file.ko"

static struct proc_dir_entry *example_dir, *test_file;
static int proc_show_ver(struct seq_file *file, void *v)
{
	int  cnt = 0;
	seq_printf(file, "Driver:%s\n0", DRV_NAME);
	return cnt;
}

static int proc_key_open(struct inode *inode, struct file *file) 
{
	single_open(file, proc_show_ver, NULL);
	return 0;
}

struct file_operations proc_fops = 
{
	.open = proc_key_open,
	.read = seq_read,
	.release = single_release,
	.owner = THIS_MODULE,
};

static int __init proc_test_init(void)
{
	example_dir = proc_mkdir("proc_test", NULL);
	test_file = proc_create("test-allen", 0, example_dir, &proc_fops);
	if (!test_file) {
		printk(KERN_DEBUG "create /proc/proc_test/proc-allen failed!\n");
		return -EAGAIN;
	}
	
	return 0;
}

static void __exit proc_test_exit(void)
{
	remove_proc_entry("test-allen", example_dir);
	remove_proc_entry("proc_test", NULL);
}

module_init(proc_test_init);
module_exit(proc_test_exit);

MODULE_LICENSE("GPL");
