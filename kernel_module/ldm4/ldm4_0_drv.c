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

struct ldm4_info
{
	dev_t dev_id;
	struct class *cls;
	struct cdev chrdev;
	struct device *dev;
};

static int dev_cnt;
static int major[MAX_DEV_CNT];
static char kbuf[BUF_SIZE];
static struct ldm4_info ldm4_info[MAX_DEV_CNT];

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

	ret = alloc_chrdev_region(&ldm4_info[dev_cnt].dev_id, 0, MIJOR_CNT, "ldm4");
	if (ret < 0) {
		printk("Line %d alloc_chrdev_region() fail", __LINE__);
	}

	major[dev_cnt] = MAJOR(ldm4_info[dev_cnt].dev_id);

	cdev_init(&ldm4_info[dev_cnt].chrdev, &ldm4_fops);
	ret = cdev_add(&ldm4_info[dev_cnt].chrdev, ldm4_info[dev_cnt].dev_id, MIJOR_CNT);
	if (ret < 0) {
		goto cdev_add_err;
	}

	ldm4_info[dev_cnt].cls = class_create(THIS_MODULE, dev->name);
	if (IS_ERR(ldm4_info[dev_cnt].cls)) {
		goto class_create_err;
	}

	ldm4_info[dev_cnt].dev = device_create(ldm4_info[dev_cnt].cls, NULL, ldm4_info[dev_cnt].dev_id, NULL, "%s", dev->name);
	if (IS_ERR(ldm4_info[dev_cnt].dev)) {
		ret = PTR_ERR(ldm4_info[dev_cnt].dev);
		goto device_create_err;
	}

	dev_cnt++;

	return 0;

device_create_err:
	class_destroy(ldm4_info[dev_cnt].cls);
class_create_err:
	cdev_del(&ldm4_info[dev_cnt].chrdev);
cdev_add_err:
	unregister_chrdev_region(MKDEV(major[dev_cnt], 0), MIJOR_CNT);

	return ret;
}

static int __devexit ldm4_remove(struct platform_device *dev)
{
	int i;

	PRINT();

	for (i = 0; i < dev_cnt; i++)
	{
		device_destroy(ldm4_info[i].cls, ldm4_info[i].dev_id);

		class_destroy(ldm4_info[i].cls);

		cdev_del(&ldm4_info[i].chrdev);

		unregister_chrdev_region(MKDEV(major[i], 0), MIJOR_CNT);
	}

	return 0;
}

static const struct platform_device_id ldm4_ids[] = {
	{
		.name = "ldm4_dev_1",
	},
	{
		.name = "ldm4_dev_2",
	},
	{
		.name = "ldm4_dev_3",
	},
	{
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
