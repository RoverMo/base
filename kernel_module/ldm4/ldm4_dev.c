#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

#define PRINT()	printk("%s():%d\n", __FUNCTION__, __LINE__)

static void ldm4_dev_close(struct device *dev)
{
	struct platform_device *ldm4_dev;

	PRINT();
	ldm4_dev = to_platform_device(dev);

	printk("Close %s\n", ldm4_dev->name);
}

static struct resource resrc[] = {
	[0] = {
		.start	= 0x100,
		.end	= 0x200,
		.flags	= IORESOURCE_MEM,
	},

	[1] = {
		.start	= 0x300,
		.end	= 0x400,
		.flags	= IORESOURCE_MEM,
	},

	[2] = {
		.start	= 0x500,
		.end	= 0x600,
		.flags	= IORESOURCE_DMA,
	},

	[3] = {},
};

static struct platform_device ldm4_dev[] = {
	[0] = {
		.name		= "ldm4_dev_1",
		.resource	= &resrc[0],
		.dev		= {
			.release = ldm4_dev_close,
		},
	},

	[1] = {
		.name		= "ldm4_dev_2",
		.resource	= &resrc[1],
		.dev		= {
			.release = ldm4_dev_close,
		},
	},

	[2] = {
		.name		= "ldm4_dev_3",
		.resource	= &resrc[2],
		.dev		= {
			.release = ldm4_dev_close,
		},
	},
};

static int __init ldm4_dev_init(void)
{
	int ret;
	int i;

	PRINT();

	for (i = 0; i < ARRAY_SIZE(ldm4_dev); i++) {
		ret = platform_device_register(&ldm4_dev[i]);
		if (ret < 0) {
			printk("%s%d\n", "platform_device_register() fail", __LINE__);
			goto platform_device_register_err;
		}
	}

	return 0;

platform_device_register_err:
	while (i > 0) {
		platform_device_unregister(&ldm4_dev[i - 1]);
		i--;
	}

	return ret;
}

static void __exit ldm4_dev_exit(void)
{
	int i;

	PRINT();

	for (i = 0; i < ARRAY_SIZE(ldm4_dev); i++) {
		platform_device_unregister(&ldm4_dev[i]);
	}
}

module_init(ldm4_dev_init);
module_exit(ldm4_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("ldm4 device");
