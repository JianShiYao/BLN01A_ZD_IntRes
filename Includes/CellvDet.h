// CellvDet.h
#ifndef CELLVDET_H
#define CELLVDET_H

#include "GeneralTypeDef.h"
#include "Version_Type.h"
#include "CellvIf.h"

// Module Version Define
#define MODULE_CELLVDET_ID           33
#define MODULE_CELLVDET_NAME         "CELLVDET"
#define CELLVDET_SW_MAJOR_VERSION    1      // size is uByte,max number is 255
#define CELLVDET_SW_MINOR_VERSION    0      // size is uWord,max number is 65535
#define CELLVDET_SW_REVISION_VERSION 0      // size is uWord,max number is 65535
#define CELLVDET_DEVELOP_STATUS      "rc" // status include "beta" "rc" ""

/* define hardware error detail */
#define CELLVDET_HDERR_INIT      0x0001
#define CELLVDET_HDERR_COM       0x0002
#define CELLVDET_HDERR_UPDATE    0x0004
#define CELLVDET_HDERR_NOCALIB   0x0008
#define CELLVDET_HDERR_NEGVOLT   0x0010
#define CELLVDET_HDERR_OPENWIRE  0x0020
#define CELLVDET_HDERR_ADCONVERT 0x0040

#define CELLVDET_MAX_WORD  0xFFFE


#define VOLT_RD_CNT   20           /* cell voltage read filter counter */
#define ERR_READCELLV_CNT 5       /* cell voltage read error counter */
#define BALANCE_CHECK_FAULT_VOLT 18000 /* 1.8V */

extern void CellvDetDet_Init(void);
extern void CellvDetDet_MainCountCbk(void);
extern void CellvDet_MainCbk(void);
extern ModuleID_Type CellvDet_GetVesionModuleVer(sVersion_CodeType * VerPtr);
extern void CellvDet_BackupVolt(eCellvIf_DeviceIdType DeviceId, uByte Row);
extern void CellvDet_ClearBackupVolt(void);

#endif