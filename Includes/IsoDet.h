#ifndef ISODET_H
#define ISODET_H

#include "Version_Type.h"

// Module Version Define
#define MODULE_ISODET_ID           34
#define MODULE_ISODET_NAME         "ISODET"
#define ISODET_SW_MAJOR_VERSION    1      // size is uByte,max number is 255
#define ISODET_SW_MINOR_VERSION    1      // size is uWord,max number is 65535
#define ISODET_SW_REVISION_VERSION 0      // size is uWord,max number is 65535
#define ISODET_DEVELOP_STATUS      "" // status include "beta" "rc" ""


extern void IsoDet_Init(void);
extern void IsoDet_MainCountCbk(void);
extern void IsoDet_MainCbk(void);
extern ModuleID_Type IsoDet_GetVesionModuleVer(sVersion_CodeType * VerPtr);

#endif