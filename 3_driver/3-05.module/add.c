#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FD");
MODULE_DESCRIPTION("test");
MODULE_VERSION("V0.1");

int add(int a, int b)
{
    return a+b;
}

static int hello_init()
{

    return 0;
}

static void hello_exit()
{

}

EXPORT_SYMBOL(add);

module_init(hello_init);
module_exit(hello_exit);