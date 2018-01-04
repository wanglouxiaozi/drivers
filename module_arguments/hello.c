#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/kernel.h>

/*
 * insmod hello.ko int_var=10 str_var="TVU-networks" buf="just do it"
 * 
 * rmmod hello.ko
 */
#define MAX_ARRAY 6
static int int_var = 0;
static const char *str_var = "default";
static const char *buf = "tvu";
static int int_array[MAX_ARRAY];
static char str_array[MAX_ARRAY];
static char str_array2[MAX_ARRAY];

module_param(int_var, int, S_IRUGO);
module_param(str_var, charp, S_IRUGO);
module_param(buf, charp, S_IRUGO);
module_param_array(int_array, int, &int_var, S_IRUGO);
module_param_array(str_array, charp, &int_var, S_IRUGO);
module_param_array(str_array2, charp, &int_var, S_IRUGO);


static int hello_init(void)
{
	int i;
	printk(KERN_ALERT "Hello, world\n");
	printk(KERN_ALERT "int_var %d\n", int_var);
	printk(KERN_ALERT "str_var %s\n", str_var);

	for(i = 0; i < int_var; i++) {
		int_array[i] = i;
	}
	for(i = 0; i < int_var; i++) {
		printk("int_array[%d] = %d\n", i, int_array[i]);
	}
	strcpy(str_array, buf);
	memcpy(str_array2, buf, int_var);
	printk("str_array[%d] = %s\n", MAX_ARRAY, str_array);
	printk("str_array2[%d] = %s\n", MAX_ARRAY, str_array2);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Bye, world\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("allen");
