// Sch_Timer.c

#include "Sch_Type.h"
#include "Sch_Cbk.h"
#include "GeneralTypeDef.h"



#define MAX_NUM_TM_TASK 10
const sTaskType TimerTaskStack[MAX_NUM_TM_TASK] = 
  {
#ifndef __DEBUG_DISABLE_PRODUCT_TASK       
      {
        TIMER_TASK_CLASS,
        Sch_CounterCallback,
      }, 
      {
        TIMER_TASK_CLASS,
        Sch_TimerCallback,
      },
#endif
#ifdef __DEBUG_TASK
      {
        TIMER_TASK_CLASS,
        Debug_TimerTask,
      },
#endif 

/* if disable product task ,need define NULL task to prevent compile error */
#ifdef __DEBUG_DISABLE_PRODUCT_TASK        
     {
       TIMER_TASK_CLASS,
       NULL
     }
#endif     
      
  };
   
void Timer_Task(void)
  {
     unsigned int i;
     for(i = 0; i < MAX_NUM_TM_TASK; i++)
      {
        if( (TIMER_TASK_CLASS == TimerTaskStack[i].TaskClass)
           && (NULL != TimerTaskStack[i].TaskPtr))
          {
            (*TimerTaskStack[i].TaskPtr)();
          }else
            {
              break;
            }
      }
  }