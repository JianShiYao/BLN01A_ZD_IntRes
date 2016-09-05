#ifndef CURRENTDET_H
#define CURRENTDET_H

#include "GeneralTypeDef.h"

#include "Version_Type.h"


// Module Version Define
#define MODULE_CURDET_ID           31
#define MODULE_CURDET_NAME         "CURDET"
#define CURDET_SW_MAJOR_VERSION    1      // size is uByte,max number is 255
#define CURDET_SW_MINOR_VERSION    1      // size is uWord,max number is 65535
#define CURDET_SW_REVISION_VERSION 0      // size is uWord,max number is 65535
#define CURDET_DEVELOP_STATUS      "" // status include "beta" "rc" ""


/* define return error */
// For CurrentDet 0x4160~0x417F
#define ERR_CURDET_CHGORDCH_FLAG_WRONG   ERR_APP_SENSOR_CURRENTDET_BASE
#define ERR_CURDET_PARA_STORE_TO_EE     (ERR_CURDET_CHGORDCH_FLAG_WRONG + 1)
#define ERR_CURVDET_HDERR_NOCALIB       (ERR_CURDET_CHGORDCH_FLAG_WRONG + 2)

/* define hardware error detail */
#define CURDET_HDERR_INIT      0x0001
#define CURDET_HDERR_PARAMETER_UNNORMAL       0x0002
#define CURDET_HDERR_NOT_UPDATE    0x0004
#define CURDET_HDERR_NOT_CALIB   0x0008
#define CURDET_HDERR_MEASURE_LINE_OPEN   0x0010
#define CURDET_HDERR_ZERO_DRIFT   0x0020
#define CURDET_HDERR_SENSOR_REVERSE 0x0040  // just for LEM
#define CURDET_HDERR_RD_INSCUR_FAILED  0x0080 // new,need add in protocol
#define CURDET_HDERR_RD_AVGCUR_FAILED  0x0100 // new,need add in protocol

extern void CurDet_Init(void);
extern void CurDet_Count(void);
extern void CurDet_Main(void);

/* interface for calibration */
extern GeneralReturnType CurDet_UpdateGainAndOffset(uWord Gain, uLWord Offset);
extern GeneralReturnType CurDet_ClbCurCurChnOffset(uLWord * OffsetPtr);
extern GeneralReturnType CurDet_ClbCurCurChnGain(uLWord * GainPtr);
extern GeneralReturnType CurDet_ClbCurVolChnOffset(uLWord * OffsetPtr);
extern GeneralReturnType CurDet_ClbCurVolChnGain(uLWord * GainPtr);
extern GeneralReturnType CurDet_UpdateAhCalcThrhd(uByte ChgOrDch, uLWord Thrhd);
extern ModuleID_Type CurDet_GetVesionModuleVer(sVersion_CodeType * VerPtr);
extern void CurDet_UpdateAHCalEn(uByte flag);
#endif  /* CURRENTDET_H */