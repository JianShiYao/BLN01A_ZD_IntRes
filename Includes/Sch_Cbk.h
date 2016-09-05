// Sch_Cbk.h
#ifndef SCH_CBK_H
#define SCH_CBK_H

#include "Ecu.h"


void Sch_CounterCallback(void);
void Sch_TimerCallback(void); 
void Sch_MainCallback(void);

void Sch_MainInit(void);

#ifdef __DEBUG_TASK
void Debug_MainTask(void);
void Debug_TimerTask(void);
#endif
  
#endif /* SCH_CBK_H */  