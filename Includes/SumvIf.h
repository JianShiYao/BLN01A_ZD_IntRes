 // SumvIf.h
#ifndef SUMVIF_H
#define SUMVIF_H
#include "EcuConf.h"

#if ((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D))
#include "GeneralTypeDef.h"
#include "SumvIf_Type.h"

#define SUMV_CVNT_ANI1 0
#define SUMV_CVNT_ANI2 1

typedef enum 
{
   SUMV_INNER_ID,
   SUMV_EXTER_ID,
   SUMV_BACKUP_ID,      
}eSumv_IdNoType;


typedef enum
{
    SUMVIF_ERR_OK,
    SUMVIF_ERR_IICACK = ERR_APP_SENSOR_SUMVDET_BASE,
    SUMVIF_ERR_WRCONFIG,
    SUMVIF_ERR_RDREGISTER,
    SUMVIF_ERR_STARTCONVERT,
    SUMVIF_ERR_OUTRANGE,
    SUMVIF_ERR_ADCONVERT,
    SUMVIF_ERR_POWERVOLT,
    SUMVIF_ERROR_IDNO,
    SUMVIF_ERROR_PTR_NULL,
    SUMVIF_ERR_NEG,
} eSumvIf_ErrCodeType;

extern GeneralReturnType SumvIf_Init(eSumv_IdNoType Sumv_IdNo);
extern GeneralReturnType SumvIf_StartConvert(eSumv_IdNoType Sumv_IdNo, uByte Chn);
extern GeneralReturnType SumvIf_RdAd(eSumv_IdNoType Sumv_IdNo, uWord* p_ad);
//static GeneralReturnType SumvIf_CheckState(eSumv_IdNoType Sumv_IdNo);
extern GeneralReturnType SumvIf_CheckPower(eSumv_IdNoType Sumv_IdNo, uWord* p_refv_ad, uWord* p_volt);
#endif
#endif 