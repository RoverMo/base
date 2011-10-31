#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define MAX_SIZE	32
#define MIJOR_CNT	1
#define PRINT()		printk("%s() : %d\n", __func__, __LINE__)

struct ldm3_info
{
	dev_t dev_id;
	struct class	*cls;
	struct cdev		chrdev;
	struct device	*dev;
};

static int major;
static char kbuf[MAX_SIZE];
static struct ldm3_info ldm3_info;

static int ldm3_open(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static ssize_t ldm3_read(struct file *pfile, char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_to_user(ubuf, kbuf, n);

	return 0;
}

static ssize_t ldm3_write(struct file *pfile, const char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_from_user(kbuf, ubuf, n);

	return 0;
}

static int ldm3_close(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static const struct file_operations ldm3_fops = {
	.owner	= THIS_MODULE,
	.open	= ldm3_open,
	.read	= ldm3_read,
	.write	= ldm3_write,
	.release= ldm3_close,
};

static int __devinit ldm3_probe(struct platform_device *dev)
{
	int ret;

	PRINT();

	ret = alloc_chrdev_region(&ldm3_info.dev_id, 0, MIJOR_CNT, "ldm3");
	if (ret < 0) {
		printk("Line %d alloc_chrdev_region() fail\n", __LINE__);
		return ret;
	}
	major = MAJOR(ldm3_info.dev_id);

	cdev_init(&ldm3_info.chrdev, &ldm3_fops);
	ret = cdev_add(&ldm3_info.chrdev, ldm3_info.dev_id, MIJOR_CNT);
	if (ret < 0) {
		goto cdev_add_err;
	}

	ldm3_info.cls = class_create(THIS_MODULE, "ldm3");
	if (IS_ERR(ldm3_info.cls)) {
		goto class_create_err;
	}

	ldm3_info.dev = device_create(ldm3_info.cls, NULL, ldm3_info.dev_id, NULL, "%s", "ldm3");
	if (!ldm3_info.dev) {
		printk("Line %d device_create() faile", __LINE__);
		goto device_create_err;
	}

	return 0;

device_create_err:
	class_destroy(ldm3_info.cls);

class_create_err:
	cdev_del(&ldm3_info.chrdev);

cdev_add_err:
	unregister_chrdev_region(MKDEV(major, 0), MIJOR_CNT);

	return ret;
}

static int __devexit ldm3_remove(struct platform_device *dev)
{
	PRINT();

	device_destroy(ldm3_info.cls, ldm3_info.dev_id);

	class_destroy(ldm3_info.cls);

	cdev_del(&ldm3_info.chrdev);

	unregister_chrdev_region(MKDEV(major, 0), MIJOR_CNT);

	return 0;
}

static struct platform_driver ldm3_driver = {
	.probe	= ldm3_probe,
	.remove	= ldm3_remove,
	.driver = {
		.name = "ldm3",
		.owner = THIS_MODULE,
	},
};

static int __init ldm3_drv_init(void)
{
	int ret;

	PRINT();

	ret = platform_driver_register(&ldm3_driver);
	if (ret < 0)
	{
		printk("platform_driver_register() fail: %d\n", __LINE__);
	}

	return 0;
}

static void __exit ldm3_drv_exit(void)
{
	PRINT();

	platform_driver_unregister(&ldm3_driver);
}

module_init(ldm3_drv_init);
module_exit(ldm3_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("A platform driver");
