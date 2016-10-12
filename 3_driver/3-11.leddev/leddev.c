/*************************************************
*文件名  ：leddev.c                
*创建者  ：FD                    
*创建时间：2015.08.19            
*程序说明：该程序为一个内核模块，地址使用的是TQ2440的
          电路图地址，模块通过LED_ON和LED_OFF来操控
         开发板上的LED的亮灭状态
**************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include "leddev.h"

#define pGPBCON 0x56000010
#define pGPBDAT 0x56000014

struct cdev ldev;
dev_t devno;
unsigned int *led_config;
unsigned int *led_data;

int led_open(struct inode *node, struct file *filp)
{
    led_config = ioremap(pGPBCON,4);
    led_data = ioremap(pGPBDAT,4);
    writel(0x15400, led_config);
    return 0;
}

long led_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
        case LED_ON:
            writel(0x61f, led_data);
            return 0;
        case LED_OFF:
            writel(0x7ff, led_data);
            return 0;
        default:
            return -EINVAL;
    }
}

int led_close(struct inode *node, struct file *filp)
{
    return 0;
}

const struct file_operations led_fops = 
{
    .open = led_open,
    .release = led_close,
    .unlocked_ioctl = led_ioctl,
};

static int led_init(void)
{
    cdev_init(&ldev, &led_fops);
    alloc_chrdev_region(&devno, 0, 1, "leddev");
    cdev_add(&ldev, devno, 1);
    return 0;
}

static void led_exit(void)
{
    cdev_del(&ldev);
    unregister_chrdev_region(devno, 1);
}

MODULE_LICENSE("GPL");
module_init(led_init);
module_exit(led_exit);