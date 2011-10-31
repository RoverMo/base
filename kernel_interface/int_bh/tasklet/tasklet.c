#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

static struct tasklet_struct tasklet;

static void tasklet_hander(unsigned long data)
{
	printk("%s():%d\n", __FUNCTION__, __LINE__);
	printk("%s\n", (char *)data);
}

static int __init driver_init(void)
{
	const char *str = "Hello World!";

	tasklet_init(&tasklet, tasklet_hander, (unsigned long)str);
	tasklet_schedule(&tasklet);

	return 0;
}

static void __exit driver_exit(void)
{
	tasklet_kill(&tasklet);
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@m126.com>");
MODULE_DESCRIPTION("Tasklet");
