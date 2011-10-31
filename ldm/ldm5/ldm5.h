#pragma once

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define	PRINT()	printk("%s():%d\n", __func__, __LINE__)

struct ldm5_device;

struct ldm5_fops {
	int (*open)(struct ldm5_device *ldm5_dev);
	ssize_t (*read)(struct ldm5_device *ldm5_dev);
	ssize_t (*write)(struct ldm5_device *ldm5_dev);
	int (*close)(struct ldm5_device *ldm5_dev);
};

struct ldm5_device {
	dev_t dev_id;
	struct device *dev;
	struct ldm5_fops fops;
	void *prv_data;
};

int register_ldm5_dev(struct ldm5_device *ldm5_dev);
int unregister_ldm5_dev(struct ldm5_device *ldm5_dev);
