#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#define BUF_SIZE 32

#define PRINT() printk("%s() : %d\n", __func__, __LINE__)

static char	kbuf[BUF_SIZE];
static int	major;
static struct class		*ldm2_cls;
static struct device	*ldm2_dev;

static int ldm2_open(struct inode *pinode, struct file *pfile)
{
	PRINT();

	return 0;
}

static ssize_t ldm2_read(struct file *pfile, char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_to_user(ubuf, kbuf, n);

	return 0;
}

static ssize_t ldm2_write(struct file *pfile, const char __user *ubuf, size_t n, loff_t *offset)
{
	PRINT();

	copy_from_user(kbuf, ubuf, n);

	return 0;
}

static long ldm2_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
	char ch = 'A';

	PRINT();

	// copy_to_user((void *)arg, &ch, sizeof(ch));
	printk("cmd = %d", cmd);

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

	PRINT();

	major = register_chrdev(0, "ldm2", &ldm2_fops);
	if (major < 0) {
		printk(KERN_ERR "register_chrdev():failed ");
		return major;
	}

	printk("major = %d\n", major);

	ldm2_cls = class_create(THIS_MODULE, "ldm2");
	if (NULL == ldm2_cls) {
		ret = -1;
		goto class_create_err;
	}

	ldm2_dev = device_create(ldm2_cls, NULL, MKDEV(major, 0), NULL, "%s", "ldm2");
	if (NULL == ldm2_dev) {
		ret = -1;
		goto device_create_err;
	}

	return 0;

device_create_err:
	class_destroy(ldm2_cls);
class_create_err:
	unregister_chrdev(major, "ldm2");

	return ret;
}

static void __exit ldm2_exit(void)
{
	device_destroy(ldm2_cls, MKDEV(major, 0));

	class_destroy(ldm2_cls);

	unregister_chrdev(major, "ldm2");

	PRINT();
}

module_init(ldm2_init);
module_exit(ldm2_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rover mo <rover.mo@maxwit.com>");
MODULE_DESCRIPTION("A linux character device module, register via register_chrdev().");
