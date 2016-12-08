
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
 
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

static int major = 0;
static struct class *leds_class = NULL;

static int led_gpios[] = {
	EXYNOS4212_GPM4(0),
	EXYNOS4212_GPM4(1),
	EXYNOS4212_GPM4(2),
	EXYNOS4212_GPM4(3),
};


static int leds_open(struct inode *inode, struct file *file)
{
	/* Configure led pin to output */
	int i;

	for (i = 0; i < 4; i++)
		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
	
	return 0;
}

/* app : ioctl(fd, cmd, arg) */
static long leds_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	/* Setup the leds gpio pins according to the parameters */
	/* cmd : 0 - off, 1 - on */
	/* arg : 0-3 which led */

	if ( (cmd != 0) && (cmd != 1) )
		return -EINVAL;

	if ( arg > 4 )
		return -EINVAL;
	
	gpio_set_value(led_gpios[arg], !cmd);
	
	return 0;
}

static struct file_operations leds_ops = {
	.owner				= THIS_MODULE,
	.open				= leds_open,
	.unlocked_ioctl		= leds_ioctl,
};

static int leds_init(void)
{
	printk(KERN_INFO "@@@@@@@@@@@@@@@@@ YOUNG leds_init @@@@@@@@@@@@@@@@@\n");
	printk(KERN_INFO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	major = register_chrdev(0, "young_leds", &leds_ops);

	/* create device nodes */
	leds_class = class_create(THIS_MODULE, "young_leds");
	device_create(leds_class, NULL, MKDEV(major, 0), NULL, "young_leds");	// /dev/young_leds
	
	return 0;
}
module_init(leds_init);

static void leds_exit(void)
{
	printk(KERN_INFO "@@@@@@@@@@@@@@@@@ YOUNG leds_exit @@@@@@@@@@@@@@@@@\n");
	printk(KERN_INFO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	device_destroy(leds_class, MKDEV(major, 0));
	class_destroy(leds_class);
	unregister_chrdev(major, "young_leds");
}
module_exit(leds_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Young");

