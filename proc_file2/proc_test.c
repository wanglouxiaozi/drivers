#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>

static unsigned int variable;
//static unsigned char variable[20] = "default\n";
static struct proc_dir_entry *test_dir, *test_entry;

static int test_proc_show(struct seq_file *seq, void *v)
{
/*	unsigned char *ptr_var = seq->private;
	seq_printf(seq, "%s\n", ptr_var);
*/	
	unsigned int *ptr_var = seq->private;
	seq_printf(seq, "%u\n", *ptr_var);

	return 0;
}
/*
static int run_test(void)
{
	int a = 1920, b= 12, c= 2132;
	sprintf(variable, "%d\n""%d\n""%d\n", a, b, c);
	return 0;
}
*/
static ssize_t test_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
	struct seq_file *seq = file->private_data;
	unsigned int *ptr_var = seq->private;
	
	*ptr_var = simple_strtoul(buffer, NULL, 10);
	return count;
}

static int test_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, test_proc_show, PDE_DATA(inode));
}

static const struct file_operations test_proc_fops =
{
	.owner = THIS_MODULE,
	.open  = test_proc_open,
	.read  = seq_read,
	.write = test_proc_write,
	.llseek = seq_lseek,
	.release = single_release,
};

static __init int test_proc_init(void)
{
	test_dir = proc_mkdir("test_dir", NULL);
	if (test_dir) {
		test_entry = proc_create_data("test_rw", 0, test_dir, &test_proc_fops, &variable);
		if (test_entry) {
//			run_test();
			return 0;
		}
	}

	return -ENOMEM;
}

static __exit void test_proc_cleanup(void)
{
	remove_proc_entry("test_rw", test_dir);
	remove_proc_entry("test_dir", NULL);
}

module_init(test_proc_init);
module_exit(test_proc_cleanup);
