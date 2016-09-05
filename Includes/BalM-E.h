// BalM_E.h
#ifndef BALM_E_H
#define BALM_E_H

#include "GeneralTypeDef.h"
#include "Version_Type.h" 
#include "BalM_Macro.h"

/*
 * Module Version Define
 */
#define MODULE_BALM_ID               23
#define MODULE_BALM_NAME             "BALM-E"  //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define BALM_SW_MAJOR_VERSION        1      //  size is uByte,max number is 255                                            
#define BALM_SW_MINOR_VERSION        1      //  size is uWord,max number is 65535                                           
#define BALM_SW_REVISION_VERSION     0      //  size is uWord,max number is 65535                                               
#define BALM_DEVELOP_STATUS          "" /* status include "beta" "rc" ""                                 
                                             *  "beta" ---- beta
                                             *  "rc"   ---- Release Candidate
                                             *  ""  or the blank or '\0' represent Release,display blank in monitor
                                             */



extern void BalM_ModuleInit(void);
extern void BalM_ModuleCountCbk(void);
extern void BalM_ModuleCbk(void);
extern void BalM_UpdateDataFromCan(uByte bmu_no, uByte cmd, uByte *p_data, uByte len);
extern ModuleID_Type BalM_E_GetVesionModuleVer(sVersion_CodeType * VerPtr);

#endif /* BALM_E_H */