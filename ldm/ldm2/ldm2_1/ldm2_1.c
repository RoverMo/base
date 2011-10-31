#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define MIJOR_CNT	2
#define MAX_SIZE	32
#define PRINT()		printk("%s() : %d\n", __func__, __LINE__)

static int major;
static struct cdev ldm2_1_cdev;
static char kbuf[MAX_SIZE];

static int ldm2_1_open(struct inode *pinde, struct file *pfile)
{
	PRINT();

	return 0;
}

static ssize_t ldm2_1_read(struct file *pfile, char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_to_user(ubuf, kbuf, n);

	return 0;
}

static ssize_t ldm2_1_write(struct file *pfile, const char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_from_user(kbuf, ubuf, n);

	return 0;
}

static int ldm2_1_close(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static const struct file_operations ldm2_1_fops = {
	.owner	= THIS_MODULE,
	.open	= ldm2_1_open,
	.read	= ldm2_1_read,
	.write	= ldm2_1_write,
	.release= ldm2_1_close,
};

static int ldm2_1_init(void)
{
	int ret;
	dev_t dev_id;

	ret = alloc_chrdev_region(&dev_id, 0, MIJOR_CNT, "ldm2_1");
	if (ret < 0)
	{
		printk("%s\n", "alloc_chrdev_region() fail");
		return ret;
	}
	major = MAJOR(dev_id);
	cdev_init(&ldm2_1_cdev, &ldm2_1_fops);
	cdev_add(&ldm2_1_cdev, dev_id, MIJOR_CNT);

	return 0;
}

static void ldm2_1_exit(void)
{
	cdev_del(&ldm2_1_cdev);
	unregister_chrdev_region(MKDEV(major, 0), MIJOR_CNT);
}

module_init(ldm2_1_init);
module_exit(ldm2_1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover.Mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("A linux character device module, register via register_chrdev_region().");
