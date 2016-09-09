#include <malloc.h>
int g_init_a = 1;                //全局，初始化的：data段
int g_uinit;                         //全局，未初始化：data段
static int s_g_init = 1;     //静态，全局，初始化：data段
static int s_g_uninit;       //静态，全局，未初始化：data段
const int const_a = 1;     //全局，静态：text段
int main(int argc, char ** argv)
{
    int g_init_a = 1;                        //局部，初始化：stack
    int g_uninit;                              //局部，未初始化：stack
    static int s_g_init_a = 1;        //静态，局部，初始化：data
    static int s_g_uninit;               //静态，局部，未初始化：data
    const int const_a =1;             //局部，初始化，常量：stack
    int * malloc_p_a;                     //局部，未初始化：stack
    malloc_p_a = malloc(sizeof(int));   //malloc分配的：heap
    while(1);
    return 0;
}
