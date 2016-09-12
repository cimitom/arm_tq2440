/*****************************
*文件名  ：fpcp.c                
*创建者  ：Elvin                    
*创建时间：2015.04.22            
*程序说明：该程序利用C库函数
          实现用来复制一个文件 
*****************************/
#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *fp_s, *fp_t;
    int flag;
    char buf[512];
/****************************************
*函数名  ：fopen
*函数功能：打开或创建一个文件
*参数    ：path, mode    
*返回值  ：成功：返回文件指针， 失败：返回空指针
*****************************************/
    fp_s = fopen(argv[1],"r+" );
    fp_t = fopen(argv[2], "w+");

    while((flag = fread(buf, 1, 512,fp_s)) >0 )
        fwrite(buf, 1,flag,fp_t);

    fclose(fp_s);
    fclose(fp_t);

    return 0;
}
