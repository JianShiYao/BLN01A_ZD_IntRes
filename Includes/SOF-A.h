// SOF.h
#ifndef SOF_A_H
#define SOF_A_H

#include "Version_Type.h" 
#include "SOF_Macro.h" 

/*
 * Module Version Define 
 */
#define MODULE_SOF_ID               14 
#define MODULE_SOF_NAME             "SOF-A"  //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define SOF_SW_MAJOR_VERSION        1      //  size is uByte,max number is 255                                            
#define SOF_SW_MINOR_VERSION        1      //  size is uWord,max number is 65535                                           
#define SOF_SW_REVISION_VERSION     0      //  size is uWord,max number is 65535                                               
#define SOF_DEVELOP_STATUS          "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */ 
extern void SOF_ModuleInit(void);
extern void SOF_ModuleCountCbk(void);
extern void SOF_ModuleCbk(void);
extern void SOF_ModifyUser(uByte type, uByte ratio);
extern void SOF_SetTargetUser(uByte type, uWord value);
extern ModuleID_Type SOF_A_GetVesionModuleVer(sVersion_CodeType * VerPtr);
 

#endif /* SOF_H */