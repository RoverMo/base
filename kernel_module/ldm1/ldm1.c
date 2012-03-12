/*
 * This is a simple linux kernel module. It's a example to show how to
 * programm in kernel space
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init ldm1_init(void)
{
	printk("Hello Kernel!\n");

	return 0;
}

static void __exit ldm1_exit(void)
{
	printk("Bye Kernel!\n");
}

module_init(ldm1_init);
module_exit(ldm1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <myzmzz@126.com>");
MODULE_DESCRIPTION("A simple kernel module");
