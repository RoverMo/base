#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

#define PRINT() printk("%s() : %d\n", __func__, __LINE__)

static void ldm3_dev_close(struct device *dev)
{
	PRINT();
}

static struct platform_device ldm3_dev = {
	.name	= "ldm3",
	.dev	= {
		.release = ldm3_dev_close,
	},
};

static int __init ldm3_dev_init(void)
{
	int ret;

	PRINT();
	ret = platform_device_register(&ldm3_dev);
	if (ret < 0)
	{
		printk("platform_device_register() fail : %d\n", __LINE__);
		return ret;
	}

	return 0;
}

static void __exit ldm3_dev_exit(void)
{
	PRINT();
	platform_device_unregister(&ldm3_dev);
}

module_init(ldm3_dev_init);
module_exit(ldm3_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("A platform device");
