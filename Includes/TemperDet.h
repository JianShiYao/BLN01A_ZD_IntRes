#ifndef TEMPER_DET_H
#define TEMPER_DET_H

#include "GeneralTypeDef.h"
#include "Version_Type.h"

// Module Version Define
#define MODULE_TEMPERDET_ID           32
#define MODULE_TEMPERDET_NAME         "TEMPERDET"
#define TEMPERDET_SW_MAJOR_VERSION    1      // size is uByte,max number is 255
#define TEMPERDET_SW_MINOR_VERSION    1      // size is uWord,max number is 65535
#define TEMPERDET_SW_REVISION_VERSION 0      // size is uWord,max number is 65535
#define TEMPERDET_DEVELOP_STATUS      "" // status include "beta" "rc" ""                    

/* define hardware error detail */
#define  TEMPER_DET_NTC_OPEN_ERR   0x1000
#define  TEMPER_DET_NTC_SHORT_ERR  0x4000


typedef enum
{
    TEMPER_DET_NTC_OPEN = ERR_APP_SENSOR_TEMPERDET_BASE,  //0x4120
    TEMPER_DET_NTC_SHORT     
}eTEMPER_DET_ERR;

#define USE_DS18B20_NUM 0
extern void TemperDet_Init(void);
extern void TemperDet_MainTemperDet(void);
extern void TemperDet_CountCbk(void);
extern ModuleID_Type TemperDet_GetVesionModuleVer(sVersion_CodeType * VerPtr);

#endif