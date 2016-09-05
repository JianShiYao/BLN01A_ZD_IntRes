// AppDo.h
#ifndef APPDO_H
#define APPDO_H

#include "GeneralTypeDef.h"
#include "Ecu.h"
#include "Version_Type.h" 

#define DO_HIGH_LEVEL_CMD TRUE
#define DO_LOW_LEVEL_CMD  FALSE

typedef enum
{
  DO_STATUS_LOW,
  DO_STATUS_HIGH,
  DO_STATUS_ERR,
  DO_STATUS_RSV,
}eActor_DoStatusType;
 

#define CPU_DO1_ID 0
#if ((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D))
#define CPU_DO2_ID 1
#endif


/*
 * Module Version Define 
 */
#define MODULE_APPDO_ID               27 
#define MODULE_APPDO_NAME             "DO"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define APPDO_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define APPDO_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define APPDO_SW_REVISION_VERSION      0   //  size is uWord,max number is 65535                                               
#define APPDO_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  
                                          
/* Version Module Get Interface */
ModuleID_Type AppDo_GetVesionModuleVer(sVersion_CodeType * VerPtr);

extern GeneralReturnType Actor_DoInit(void);
extern GeneralReturnType Actor_CtrlDo(uByte Do_id, bool Do_cmd);
extern eActor_DoStatusType Actor_GetDoSt(uByte Do_id);

#endif