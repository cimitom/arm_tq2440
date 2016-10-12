/*************************************************
*文件名  ：memdev.c                
*创建者  ：FD                    
*创建时间：2015.08.016            
*程序说明：该程序为一个内核模块，模拟操作两组寄存器
           程序实现read，write对寄存器进行读写操作
**************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

struct cdev mdev;
dev_t devno;
int m_register0[5];
int m_register1[5];

int mem_open(struct inode *node, struct file *filp)
{
    int num = MINOR(node->i_rdev);
    if(0 == num)
        filp->private_data = m_register0;
    else
        filp->private_data = m_register1;
    return 0;
}

int mem_release(struct inode *node, struct file *filp)
{
    return 0;
}

loff_t mem_llseek(struct file *filp, loff_t offset, int whence)
{
    loff_t new_pos;
    switch (whence)
    {
        case SEEK_SET:
            new_pos = offset;
            break;
        case SEEK_CUR:
            new_pos = filp->f_pos + offset;
            break;
        case SEEK_END:
            new_pos = (sizeof(int)*5-1) + offset;
            break;
        default:
            return -EINVAL;
    }
    if((new_pos <0 ) || (new_pos > 5*sizeof(int)))
        return -EINVAL;

    filp->f_pos = new_pos;
    return new_pos;
}

ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned long count = size;
    int ret = 0;
    int *reg_val = filp->private_data;
    
    if (p >= 5*sizeof(int))
        return 0;
    if (count > 5*sizeof(int)-p)
        count = 5*sizeof(int)-p;
    if(copy_to_user(buf, reg_val + p,count))
    {
        ret = -EINVAL;
    }
    else
    {
        filp->f_pos += count;
        ret = count;
    }
    return ret;
}

ssize_t mem_write(struct file *filp, const char *buf, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned long count = size;
    int ret = 0;
    int *reg_val = filp->private_data;
    
    if (p >= 5*sizeof(int))
        return 0;
    if (count > 5*sizeof(int)-p)
        count = 5*sizeof(int)-p;
    if(copy_from_user(reg_val + p, buf, count))
    {
        ret = -EINVAL;
    }
    else
    {
        filp->f_pos += count;
        ret = count;
    }
    return ret;
}

/* 文件操作集 */
const struct file_operations mem_fops = 
{
    .llseek = mem_llseek,
    .open = mem_open,
    .release = mem_release,
    .read = mem_read,
    .write = mem_write,
};

/* 模块加载函数 */
static int memdev_init()
{
    /* 初始化cdev结构 */
    cdev_init(&mdev, &mem_fops);
    /* 自动分配字符设备号 */
    alloc_chrdev_region(&devno, 0, 2, "memdev");
    /* 注册cdev字符设备 */
    cdev_add(&mdev, devno, 2);
    return 0;
}
/* 模块卸载函数 */
static void memdev_exit()
{
    unregister_chrdev_region(devno, 2);
    cdev_del(&mdev);
}

MODULE_LICENSE("GPL");
module_init(memdev_init);
module_exit(memdev_exit);