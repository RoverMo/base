#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/cdev.h>

#include "ldm2.h"

#define PRINT()		printk("%s() : %d\n", __FUNCTION__, __LINE__)

#define BY_ALLOC_CHRDEV_REGION

#ifdef BY_REGISTER_CHRDEV
#define LDM2_MAJOR	245
#endif

#ifdef BY_REGISTER_CHRDEV_REGION
#define LDM2_MAJOR	245
#define MIJOR_CNT	2
static dev_t dev_id;
static struct cdev ldm2_cdev;
#endif

#ifdef BY_ALLOC_CHRDEV_REGION
#define MIJOR_CNT	2
static dev_t dev_id;
static struct cdev ldm2_cdev;
#endif

static char kbuf[BUF_SIZE];

static int ldm2_open(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static ssize_t ldm2_read(struct file *pfile, char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_to_user(ubuf, kbuf, n);
	printk("%s\n", kbuf);

	return strlen(kbuf);
}

static ssize_t ldm2_write(struct file *pfile, const char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_from_user(kbuf, ubuf, n);
	printk("%s\n", ubuf);

	return n;
}

static long ldm2_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
	int i, n;

	PRINT();

	switch (cmd) {
	case LDM2_CMD_1:
		n = strlen((void *)arg);
		copy_from_user(kbuf, (void *)arg, n);
		for (i = 0; i < n; i++) {
			if (kbuf[i] > 'a' && kbuf[i] < 'z') {
				kbuf[i] -= 'a' - 'A';
			}
		}
		copy_to_user((void *)arg, kbuf, n);
		break;

	case LDM2_CMD_2:
		break;

	case LDM2_CMD_3:
		break;

	default:
		printk("Unknown cmd: %u\n", cmd);
		return -EINVAL;
	}

	return 0;
}

static int ldm2_close(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static const struct file_operations ldm2_fops = {
	.owner   = THIS_MODULE,
	.open    = ldm2_open,
	.read    = ldm2_read,
	.write   = ldm2_write,
	.unlocked_ioctl = ldm2_ioctl,
	.release = ldm2_close,
};

static int __init ldm2_init(void)
{
	int ret;

#ifdef BY_REGISTER_CHRDEV
	ret = register_chrdev(LDM2_MAJOR, "ldm2", &ldm2_fops);
	if (ret < 0) {
		printk(KERN_ERR "register_chrdev():failed ");
		return ret;
	}
#endif

#ifdef BY_REGISTER_CHRDEV_REGION
	dev_id = MKDEV(LDM2_MAJOR, 0);
	ret = register_chrdev_region(dev_id, MIJOR_CNT, "ldm2");
	if (ret < 0)
	{
		printk("%s\n", "alloc_chrdev_region() fail");
		return ret;
	}
	cdev_init(&ldm2_cdev, &ldm2_fops);
	cdev_add(&ldm2_cdev, dev_id, MIJOR_CNT);
#endif

#ifdef BY_ALLOC_CHRDEV_REGION
	ret = alloc_chrdev_region(&dev_id, 0, MIJOR_CNT, "ldm2");
	if (ret < 0)
	{
		printk("%s\n", "alloc_chrdev_region() fail");
		return ret;
	}
	printk("major = %d\n", MAJOR(dev_id));
	cdev_init(&ldm2_cdev, &ldm2_fops);
	cdev_add(&ldm2_cdev, dev_id, MIJOR_CNT);
#endif

	PRINT();

	return 0;
}

static void __exit ldm2_exit(void)
{

#ifdef BY_REGISTER_CHRDEV
	unregister_chrdev(LDM2_MAJOR, "ldm2");
#else
	unregister_chrdev_region(dev_id, MIJOR_CNT);
#endif

	PRINT();
}

module_init(ldm2_init);
module_exit(ldm2_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover mo <myzmzz@126.com>");
MODULE_DESCRIPTION("A linux character device module, register via register_chrdev().");
