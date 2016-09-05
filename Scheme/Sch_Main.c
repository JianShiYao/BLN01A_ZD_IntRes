// Sch_Main.c

#include "Sch_Type.h"
#include "Sch_Cbk.h"
#include "GeneralTypeDef.h"
#include "Ecu.h"

#define MAX_NUM_MAIN_TASK 10
const sTaskType MainTaskStack[MAX_NUM_MAIN_TASK] = 
  {
#ifndef __DEBUG_DISABLE_PRODUCT_TASK  
      {
        MAIN_TASK_CLASS,
        Sch_MainCallback,
      },
#endif      
#ifdef __DEBUG_TASK
     {  
       MAIN_TASK_CLASS,
       Debug_MainTask,
     }, 
#endif
/* if disable product task ,need define NULL task to prevent compile error */
#ifdef __DEBUG_DISABLE_PRODUCT_TASK   
     {  
       MAIN_TASK_CLASS,
       NULL, 
     }
#endif     
            
  };
   
void Main_Task(void)
  {
     unsigned int i;
     for(i = 0; i < MAX_NUM_MAIN_TASK; i++)
      {
        if( (MAIN_TASK_CLASS == MainTaskStack[i].TaskClass)
           && (NULL != MainTaskStack[i].TaskPtr))
          {
            (*MainTaskStack[i].TaskPtr)();
          }else
            {
              break;
            }
      }
  }