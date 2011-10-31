#include "ldm5.h"
#include <linux/fs.h>
#include <linux/device.h>

#define BUF_SIZE	32
#define DEV_CNT		8

static int	major;
static struct class			*ldm5_cls;
static struct ldm5_device	*ldm5_devs[DEV_CNT];

static int ldm5_core_open(struct inode *pinode, struct file *pfile)
{
	struct ldm5_device *ldm5_dev;

	PRINT();

	ldm5_dev = ldm5_devs[MINOR(pinode->i_rdev)];
	pfile->private_data = ldm5_dev;

	if (NULL == (ldm5_dev->fops).open) {
		return -1;
	}

	return (ldm5_dev->fops).open(ldm5_dev);
}

static ssize_t ldm5_core_read(struct file *pfile, char __user *ubuf, size_t n, loff_t *offset)
{
	struct ldm5_device *ldm5_dev;

	PRINT();

	ldm5_dev = (struct ldm5_device *)pfile->private_data;
	if (NULL == (ldm5_dev->fops).read) {
		return -1;
	}

	return (ldm5_dev->fops).read(ldm5_dev);
}

static ssize_t ldm5_core_write(struct file *pfile, const char __user *ubuf, size_t n, loff_t *offset)
{
	struct ldm5_device *ldm5_dev;

	PRINT();

	ldm5_dev = (struct ldm5_device *)pfile->private_data;
	if (NULL != (ldm5_dev->fops).write) {
		(ldm5_dev->fops).write(ldm5_dev);
	}

	return 0;
}

static int ldm5_core_close(struct inode *pinode, struct file *pfile)
{
	struct ldm5_device *ldm5_dev;

	PRINT();

	ldm5_dev = (struct ldm5_device *)pfile->private_data;
	if (NULL != (ldm5_dev->fops).close) {
		(ldm5_dev->fops).close(ldm5_dev);
	}

	return 0;
}

static const struct file_operations ldm5_fops = {
	.owner	= THIS_MODULE,
	.open	= ldm5_core_open,
	.read	= ldm5_core_read,
	.write	= ldm5_core_write,
	.release= ldm5_core_close,
};

int register_ldm5_dev(struct ldm5_device *ldm5_dev)
{
	int i;

	PRINT();

	for (i = 0; i < DEV_CNT; i++) {
		if (NULL == ldm5_devs[i]) {
			break;
		}
	}

	if (i >= DEV_CNT) {
		printk("%s\n", "Can't get minor");
		return -1;
	}

	ldm5_dev->dev_id = MKDEV(major, i);

	ldm5_dev->dev = device_create(ldm5_cls, NULL, ldm5_dev->dev_id, NULL, "%s_%d", "ldm5", i);
	if (NULL == ldm5_dev->dev) {
		return -1;
	}

	ldm5_devs[i] = ldm5_dev;

	return 0;
}

EXPORT_SYMBOL(register_ldm5_dev);

int unregister_ldm5_dev(struct ldm5_device *ldm5_dev)
{
	PRINT();

	ldm5_devs[MINOR(ldm5_dev->dev_id)] = NULL;
	device_destroy(ldm5_cls, ldm5_dev->dev_id);

	return 0;
}

EXPORT_SYMBOL(unregister_ldm5_dev);

static int __init ldm5_core_init(void)
{
	PRINT();

	major = register_chrdev(0, "ldm5", &ldm5_fops);
	if (major < 0) {
		printk("Line %d register_chrdev() fail\n", __LINE__);
		return major;
	}

	ldm5_cls = class_create(THIS_MODULE, "ldm5");
	if (NULL == ldm5_cls) {
		printk("Line %d class_create() fail\n", __LINE__);
		return -1;
	}

	return 0;
}

static void __exit ldm5_core_exit(void)
{
	PRINT();

	unregister_chrdev(major, "ldm5");
	class_destroy(ldm5_cls);
}

module_init(ldm5_core_init);
module_exit(ldm5_core_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover Mo<rover.mo@maxwit.com>");
MODULE_DESCRIPTION("ldm5 core");
