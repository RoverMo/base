#include "ldm5.h"

static struct resource ldm5_res[] = {
	[0] = {
		.start	= 0x10000,
		.end	= 0x20000,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= 0x20000 + 4,
		.end	= 0x30000,
		.flags	= IORESOURCE_MEM,
	},
	[2] = {
		.start	= 0x30000 + 4,
		.end	= 0x40000,
		.flags	= IORESOURCE_MEM,
	},
	[3] = {
		.start	= 0x40000 + 4,
		.end	= 0x50000,
		.flags	= IORESOURCE_MEM,
	},
	[4] = {},
};

static void __devexit ldm5_dev_close(struct device *dev)
{
	struct platform_device *ldm4_dev;

	PRINT();
	ldm4_dev = to_platform_device(dev);

	printk("Close %s\n", ldm4_dev->name);
}

static struct platform_device ldm5_dev[] = {
	[0] = {
		.name		= "ldm5_dev_1",
		.resource	= &ldm5_res[0],
		.dev		= {
			.release = ldm5_dev_close,
		},
	},
	[1] = {
		.name		= "ldm5_dev_2",
		.resource	= &ldm5_res[1],
		.dev	= {
			.release = ldm5_dev_close,
		},
	},
	[2] = {
		.name		= "ldm5_dev_3",
		.resource	= &ldm5_res[2],
		.dev		= {
			.release = ldm5_dev_close,
		},
	},
	[3] = {
		.name		= "ldm5_dev_4",
		.resource	= &ldm5_res[3],
		.dev		= {
			.release = ldm5_dev_close,
		},
	},
};

static int __init ldm5_dev_init(void)
{
	int i;
	int ret;

	PRINT();

	for (i = 0; i < ARRAY_SIZE(ldm5_dev); i++) {
		ret = platform_device_register(&ldm5_dev[i]);
		if (ret < 0) {
			printk("Line %d platform_device_register() fail\n", __LINE__);
			goto platform_device_register_err;
		}
	}

	return 0;

platform_device_register_err:
	while (i > 0) {
		platform_device_unregister(&ldm5_dev[i - 1]);
		i--;
	}

	return ret;
}

static void __exit ldm5_dev_exit(void)
{
	int i;

	PRINT();

	for (i = 0; i < ARRAY_SIZE(ldm5_dev); i++) {
		platform_device_unregister(&ldm5_dev[i]);
	}
}

module_init(ldm5_dev_init);
module_exit(ldm5_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo<rover.mo@maxwit.com>");
MODULE_DESCRIPTION("ldm5 device");
