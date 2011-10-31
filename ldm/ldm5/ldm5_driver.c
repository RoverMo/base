#include "ldm5.h"
#include <linux/slab.h>

const static struct platform_device_id ldm5_id[] = {
	{
		.name = "ldm5_dev_1",
	},
	{
		.name = "ldm5_dev_2",
	},
	{
		.name = "ldm5_dev_3",
	},
	{
	},
};

static int ldm5_drv_open(struct ldm5_device *ldm5_dev)
{
	PRINT();

	return 0;
}

static ssize_t ldm5_drv_read(struct ldm5_device *ldm5_dev)
{
	PRINT();

	return 0;
}

static ssize_t ldm5_drv_write(struct ldm5_device *ldm5_dev)
{
	PRINT();

	return 0;
}

static int ldm5_drv_close(struct ldm5_device *ldm5_dev)
{
	PRINT();

	return 0;
}

static int __devinit ldm5_probe(struct platform_device *dev)
{
	int ret;
	struct ldm5_device *ldm5_dev;

	PRINT();

	ldm5_dev = (struct ldm5_device *)kmalloc(sizeof(*ldm5_dev), GFP_KERNEL);
	if (NULL == ldm5_dev) {
		return -ENOMEM;
	}

	(ldm5_dev->fops).open	= ldm5_drv_open;
	(ldm5_dev->fops).read	= ldm5_drv_read;
	(ldm5_dev->fops).write	= ldm5_drv_write;
	(ldm5_dev->fops).close	= ldm5_drv_close;

	ret = register_ldm5_dev(ldm5_dev);
	if (ret < 0) {
		goto register_ldm5_dev_err;
	}

	platform_set_drvdata(dev, ldm5_dev);

	return 0;

register_ldm5_dev_err:
	kfree(ldm5_dev);
	return ret;
}

static int __devexit ldm5_remove(struct platform_device *dev)
{
	struct ldm5_device *ldm5_dev;

	PRINT();

	ldm5_dev = (struct ldm5_device *)platform_get_drvdata(dev);
	if (NULL == ldm5_dev) {
		return -1;
	}

	unregister_ldm5_dev(ldm5_dev);

	kfree(ldm5_dev);

	return 0;
}

static struct platform_driver ldm5_drv = {
	.probe		= ldm5_probe,
	.remove		= ldm5_remove,
	.id_table	= ldm5_id,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "ldm5",
	},
};

static int __init ldm5_drv_init(void)
{
	int ret;

	PRINT();

	ret = platform_driver_register(&ldm5_drv);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

static void __exit ldm5_drv_exit(void)
{
	PRINT();

	platform_driver_unregister(&ldm5_drv);
}

module_init(ldm5_drv_init);
module_exit(ldm5_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo<rover.mo@maxwit.com>");
MODULE_DESCRIPTION("ldm5 driver");
