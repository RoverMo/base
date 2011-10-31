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
	struct task_struct *task;

	PRINT();

	for_each_process(task) {
		printk("%s[%d]\n", task->comm, task->pid);
	}

	return 0;
}

static void __exit ldm1_exit(void)
{
	PRINT();
}

module_init(ldm1_init);
module_exit(ldm1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("A simple kernel module");
