#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FD");
MODULE_DESCRIPTION("test");
MODULE_VERSION("V0.1");

extern add(int a, int b);

int a;
char *p;

module_param(a, int ,S_IRUGO | S_IWUSR);
module_param(p, charp ,S_IRUGO | S_IWUSR);

static int hello_init()
{
    a=add(3, 4);
    printk(KERN_WARNING"Hello world!\n");
    printk("a = %d, p = %s\n", a, p);
    return 0;
}

static void hello_exit()
{
    printk(KERN_WARNING"Hello exit!\n");
}

module_init(hello_init);
module_exit(hello_exit);