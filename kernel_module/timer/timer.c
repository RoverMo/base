#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list timer;

static void timer_hander(unsigned long context)
{
	printk("%s\n", (char *)context);
	mod_timer(&timer, jiffies + HZ * 5);
	printk("%s():%d\n", __FUNCTION__, __LINE__);
}

static int __init timer_init(void)
{
	const char *str = "Hello Rover";

	init_timer(&timer);
	timer.function	= timer_hander;
	timer.expires	= jiffies + HZ * 5;
	timer.data		= (unsigned long)str;
	add_timer(&timer);

	return 0;
}

static void __exit timer_exit(void)
{
	del_timer(&timer);
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@126.com>");
MODULE_DESCRIPTION("Timer");
