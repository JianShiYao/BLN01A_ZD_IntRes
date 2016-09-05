// ThM-AB.h
#ifndef THM_AB_H
#define THM_AB_H

#include "GeneralTypeDef.h"
#include "Ecu.h"
#include "Version_Type.h" 
#include "ThM_Macro.h" 

/*
 * Module Version Define 
 */
#define MODULE_THM_ID               19
#define MODULE_THM_NAME             "THM-AB"  //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define THM_SW_MAJOR_VERSION        1      //  size is uByte,max number is 255                                            
#define THM_SW_MINOR_VERSION        1      //  size is uWord,max number is 65535                                           
#define THM_SW_REVISION_VERSION     0      //  size is uWord,max number is 65535                                               
#define THM_DEVELOP_STATUS          ""       /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */

extern void ThM_ModuleInit(void);
extern void ThM_ModuleCountCbk(void);
extern void ThM_ModuleCbk(void);
extern void ThM_TestFan(uByte fan_on_off, uWord fan_speed_ctrl);
extern ModuleID_Type ThM_AB_GetVesionModuleVer(sVersion_CodeType * VerPtr);

#endif /* THM_AB_H */