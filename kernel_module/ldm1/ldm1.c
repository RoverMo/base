/*
 * This is a simple linux kernel module. It print all kernel
 * thread name and pid.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>

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
MODULE_AUTHOR("Rover Mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("A simple kernel module");
