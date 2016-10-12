/*************************************************
*文件名  ：leddev.h                
*创建者  ：FD                    
*创建时间：2015.08.19            
*程序说明：该头文件定义了leddev.c中的ioctl函数中使用
          到的相关幻数。
**************************************************/
#define LED_MAGIC 'L'
#define LED_ON _IO(LED_MAGIC,0)
#define LED_OFF _IO(LED_MAGIC,1)