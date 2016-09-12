/**************************************************************************************************
*   Source File
*
*   File Name               :   FN_FileName.c
*   Copyright               :   2016 ~ 2020 Elvin Corporation, All rights Reserved.
*   Module Name             :   Display
*
*   CPU                     :   X86
*   RTOS                    :   windows7 32bit
*
*   Create Date             :   2016/04/21
*   Author/Corporation      :   Elvin/ESYS Company
*
*   Abstract Description    :   some function about seqlist.
*
*------------------------Revision History------------------------------------------------
*   No     Version     Date          Revised By   Item          Description     
*   1      0.02        2016/04/21    Elvin        Seqlist       Just a test
**************************************************************************************************/

/**************************************************************************************************
*   Debug switch Section
**************************************************************************************************/
#define D_FILENAME_BASE

/**************************************************************************************************
*   Include File Section
**************************************************************************************************/
/*  Perhaps there are some file will be Included  */
/*  No file will be Included  */
#include "IncFile.h"

/**************************************************************************************************
*   Macro Define Section
**************************************************************************************************/
/*  Perhaps there are some Macro will be defined  */
/*  No Macro will be defined  */
#define MAX_TIMER_OUT

/**************************************************************************************************
*   Struct Define Section
**************************************************************************************************/
/*  Perhaps there are some Struct be defined  */
/*  No Struct will be defined  */
typedef struct Seqlist
{
    int capacity;
    int length;
}Seqlist_st, * Seqlist_pst;

/**************************************************************************************************
*   Prototype Declare Section
**************************************************************************************************/
Seqlist_pst SeqlistCreate(int capacity);

/**************************************************************************************************
*   Global Variable Declare Section
**************************************************************************************************/
/*  Perhaps there are some Global Variable be defined  */
/*  No Global Variable will be defined  */
extern unsigned int SeqlistNode;

/**************************************************************************************************
*   File Static Variable Declare Section
**************************************************************************************************/
/*  Perhaps there are some Static Variable be defined  */
/*  No Static Variable will be defined  */
static unsigned int SeqlistStatus;

/**************************************************************************************************
*   Function Declare Section
**************************************************************************************************/
Seqlist_pst SeqlistCreate(int capacity)
{
    Seqlist_pst slist = NULL;
    return slist;
}




