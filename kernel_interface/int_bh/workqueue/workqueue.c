#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/errno.h>

static struct work_struct work;
static struct workqueue_struct *wqueue;

static void workqueue_hander(struct work_struct *work)
{
	printk("%s():%d\n", __FUNCTION__, __LINE__);
}

static int __init driver_init(void)
{
	const char *str = "Hello World!";

	wqueue = create_singlethread_workqueue("Rover");
	if (NULL == wqueue) {
		return -ENOMEM;
	}

	INIT_WORK(&work, workqueue_hander);
	schedule_work(&work);

	return 0;
}

static void __exit driver_exit(void)
{
	destroy_workqueue(wqueue);
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@m126.com>");
MODULE_DESCRIPTION("workqueue");
