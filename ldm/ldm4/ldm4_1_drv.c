#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define BUF_SIZE	32
#define MIJOR_CNT	8
#define MAX_DEV_CNT	5

#define PRINT()		printk("%s():%d\n", __FUNCTION__, __LINE__)

static struct	device	*ldm4_dev[MAX_DEV_CNT];
static struct	class	*ldm4_cls;
static int		dev_cnt;
static int		major;
static char		kbuf[BUF_SIZE];

static int ldm4_open(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static ssize_t ldm4_read(struct file *pfile, char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_to_user(ubuf, kbuf, n);

	return 0;
}

static ssize_t ldm4_write(struct file *pfile, const char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_from_user(kbuf, ubuf, n);

	return 0;
}

static int ldm4_close(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static const struct file_operations ldm4_fops = {
	.owner	= THIS_MODULE,
	.open	= ldm4_open,
	.read	= ldm4_read,
	.write	= ldm4_write,
	.release= ldm4_close,
};

static int __devinit ldm4_probe(struct platform_device *dev)
{
	int ret;

	PRINT();

	if (0 == dev_cnt) {
		major = register_chrdev(0, "ldm4", &ldm4_fops);
		if (major < 0) {
			return major;
		}

		ldm4_cls = class_create(THIS_MODULE, "ldm4");
		if (NULL == ldm4_cls) {
			ret = -1;
			goto class_create_err;
		}
	}

	ldm4_dev[dev_cnt] = device_create(ldm4_cls, NULL, MKDEV(major, dev_cnt), NULL, "%s", dev->name);
	if (NULL == ldm4_dev[dev_cnt]) {
		ret = -1;
		goto device_create_err;
	}

	dev_cnt++;

	return 0;

device_create_err:
	while (dev_cnt > 0) {
		device_destroy(ldm4_cls, MKDEV(major, dev_cnt - 1));
		dev_cnt--;
	}
	class_destroy(ldm4_cls);
class_create_err:
	unregister_chrdev(major, "ldm4");

	return ret;
}

static int __devexit ldm4_remove(struct platform_device *dev)
{
	int i;

	PRINT();

	for (i = 0; i < dev_cnt; i++) {
		device_destroy(ldm4_cls, MKDEV(major, i));
	}

	class_destroy(ldm4_cls);

	unregister_chrdev(major, "ldm4");

	return 0;
}

static const struct platform_device_id ldm4_ids[] = {
	[0] = {
		.name = "ldm4_dev_1",
	},
	[1] = {
		.name = "ldm4_dev_2",
	},
	[2] = {
		.name = "ldm4_dev_3",
	},
	[3] = {
	},
};

static struct platform_driver ldm4_drv = {
	.probe		= ldm4_probe,
	.remove		= ldm4_remove,
	.id_table	= ldm4_ids,
	.driver	= {
		.name = "ldm4",
		.owner= THIS_MODULE,
	},
};

static int __init ldm4_drv_init(void)
{
	int ret;

	PRINT();

	ret = platform_driver_register(&ldm4_drv);
	if (ret < 0) {
		printk("Line %d platform_driver_register() fail", __LINE__);
		return ret;
	}

	return 0;
}

static void __exit ldm4_drv_exit(void)
{
	PRINT();

	platform_driver_unregister(&ldm4_drv);
}

module_init(ldm4_drv_init);
module_exit(ldm4_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("ldm4 driver");
