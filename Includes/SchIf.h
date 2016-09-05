// SchIf.h
#ifndef SCHIF_H
#define SCHIF_H

#include "Sch_Type.h"
#include "Version_Type.h"

#define MIN_TIMER_MS 5 // 5ms

#define TM_5MS   (5/MIN_TIMER_MS)
#define TM_10MS  (10/MIN_TIMER_MS)
#define TM_100MS (100/MIN_TIMER_MS)
#define TM_500MS (500/MIN_TIMER_MS)
#define TM_MS(ms)  ((ms)/MIN_TIMER_MS) // ms must can be divided by 5

void Sch_Init(void);

/*
 * Module Version Define 
 */
#define MODULE_SCH_ID               7 
#define MODULE_SCH_NAME             "SCH"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define SCH_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define SCH_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define SCH_SW_REVISION_VERSION      0   //  size is uWord,max number is 65535                                               
#define SCH_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  
/* Version Module Get Interface */
ModuleID_Type Sch_GetVesionModuleVer(sVersion_CodeType * VerPtr);                                               

#endif                 