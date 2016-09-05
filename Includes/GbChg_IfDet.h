



#ifndef GBCHG_IFDET_H
#define GBCHG_IFDET_H

#include "GeneralTypeDef.h"
#include "AiIf_Type.h"
#include "Version_Type.h"

// Module Version Define
#define MODULE_GBCHGDET_ID           28
#define MODULE_GBCHGDET_NAME         "GBCHGDET"
#define GBCHGDET_SW_MAJOR_VERSION    1      // size is uByte,max number is 255
#define GBCHGDET_SW_MINOR_VERSION    1      // size is uWord,max number is 65535
#define GBCHGDET_SW_REVISION_VERSION 0      // size is uWord,max number is 65535
#define GBCHGDET_DEVELOP_STATUS      "" // status include "beta" "rc" ""

#define GAIN_VOLT 110


                     
extern void GbChgDet_Ai(eAiIf_ChannelIdNumType Ch, uWord VoltGain, uWord *VoltPtr);
extern void GbChgDet_DutyCalc(uByte *DutyPtr);
extern ModuleID_Type GbChgDet_GetVesionModuleVer(sVersion_CodeType * VerPtr);
                                       
extern void ChgIfDet_Init(void);

extern void ChgIfDet_MainCountCbk(void);

extern void ChgIfDet_MainCbk(void); 



#endif  /*GBCHG_IFDET_H */