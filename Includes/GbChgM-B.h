#ifndef GBCHGM_B_H
#define GBCHGM_B_H

#include "GeneralTypeDef.h"
#include "CanIf_Type.h"
#include "ChgM-B.h"


#define CNT_MASK   0x00FF0000
//#define __DEBUG_GB_CHG_TEST

#define GB_RELAY_ON  1
#define GB_RELAY_OFF 0
#define GB_FLAG_OK 1
#define GB_FLAG_FAIL 0
#define GB_FLAG_ENABLE  1
#define GB_FLAG_DISABLE 0

#define CHG_CAN_ERR    0x00000040
#define CHG_BAT_NOT_MATCH 0x00000800
#define CHG_HD_ERR     0x00100000
#define CHG_RLY_ERR    0x00000200
#define CHG_BAT_FULL   0x00000400
#define CHG_ISO_ERR    0x00080000
#define CHG_CELLV_HIGH 0x00040000
#define CHG_CELLV_LOW  0x00020000
#define CHG_SUMV_HIGH  0x00010000
#define CHG_SUMV_LOW   0x00008000
#define CHG_TEMP_HIGH  0x00004000
#define CHG_TEMP_LOW   0x00002000
#define CHG_CUR_HIGH   0x00001000

#define LINK_FAIL_300MS     30    /* count for detect ac link fail, 300ms */


/* other */
#define CHG_RX_BMS      0xAA
#define CHG_NOT_RX_BMS  0x00

#define CHG_READY      0xAA
#define CHG_NOT_READY  0x00
#define BMS_READY      0xAA
#define BMS_NOT_READY  0x00

#define CHG_MODE_CV    0x01
#define CHG_MODE_CC    0x02

/* GB charge end reason */
#define  REACH_SOC     0x01
#define  REACH_SUMV    0x04
#define  REACH_CELLV   0x10
#define  ISO_ERR       0x01
#define  CON_OVER_T    0x04
#define  BMS_OVER_T    0x10
#define  CHG_CON_ERR   0x40
#define  BAT_OVER_T    0x01
#define  OTHER_ERR     0x04
#define  OVER_CUR      0x01
#define  OVER_VOLT     0x04


/* Charge step */
#define ChgStep0    0
#define ChgStep1    1
#define ChgStep2    2
#define ChgStep3    3
#define ChgStep4    4
#define ChgStep5    5
#define ChgStep6    6
#define ChgStep7    7
#define ChgStep8    8
#define ChgStep9    9
#define ChgStep10   10
#define ChgStep11   11
#define ChgStep12   12


#define CNT_DET_LINK    20   //200ms, for detect

#define CHG_S_ON  1
#define CHG_S_OFF 0

typedef struct
{

    uByte Brm : 1; 					 //bms recognise
    uByte Bcp : 1; 					 //battery charge data
    uByte Bro : 1;				   //battery Ready to charge
    uByte Bcl : 1; 					 //battery charge requirement
    uByte Bcs : 1; 					 //battery charge status
    uByte Bsm : 1;					 //bms send battery status
    uByte Bmv : 1; 					 //battery voltage
    uByte Bmt : 1;					 //battery temperature
    uByte Bsp : 1;					 //battery reserved
    uByte Bst : 1; 					 //bms stop charge
    uByte Bsd : 1;				   //bms statistics data message
    uByte Bem : 1; 					 //bms error message
    uByte Bhm : 1;
    uByte rsv : 3;

} sGbChgM_FLG;

typedef struct
{
    uByte ChgStep;
    uByte ChgStepBak;
    uByte HandShakeErr;
    uByte ConfigErr;
    uByte ChargingErr;
    uByte ChargeEndErr;
    uByte ChgEndReason1;
    uByte ChgEndReason2;
    uByte ChgEndReason3;
    uByte ChgEndReason4;
    sGbChgM_FLG Flg;
} sGbChgM_CtrlType;

extern uByte gby_byte_num_brm;
extern uByte gby_msg_num_brm;

extern uByte GbChgM_GetFlgBro(void);
extern uByte GbChgM_GetFlgBcl(void);
extern uByte GbChgM_GetFlgBsm(void);
extern uByte GbChgM_GetFlgBst(void);
extern uByte GbChgM_GetFlgBsd(void);
extern uByte GbChgM_GetFlgBem(void);
extern uByte GbChgM_GetFlgBrm(void);
extern uByte GbChgM_GetFlgBcp(void);
extern uByte GbChgM_GetFlgBcs(void);
extern uByte GbChgM_GetFlgBmv(void);
extern uByte GbChgM_GetFlgBmt(void);
extern uByte GbChgM_GetFlgBsp(void);
extern uByte GbChgM_GetFlgBhm(void);

extern uByte GbChgM_GetChgEndReason1(void);
extern uByte GbChgM_GetChgEndReason2(void);
extern uByte GbChgM_GetChgEndReason3(void);
extern uByte GbChgM_GetChgEndReason4(void);

extern uByte GbChgM_GetChgHandShakeErr(void);
extern uByte GbChgM_GetChgConfigErr(void);
extern uByte GbChgM_GetChargingErr(void);
extern uByte GbChgM_GetChargeEndErr(void);

extern void GbChgM_UpdateAcPmtChgCur(uWord cur);
extern uWord GbChgM_GetAcPmtChgCur(void);
extern uByte GbChgM_GetStep(void);

extern void GbChgM_LinkModeJudge(void);
extern void GbChgM_EndReasonDeal(void);
extern void GbChgM_ChgCtrl(void);
extern void GbChgM_StopReasonJudge(void);
extern uWord GbChgM_ACPmtCurCalc(void);

extern void GbChgM_ModuleInit(void);
extern void GbChgM_ModuleCountCbk(void);

#endif /* GBCHGM_B_H  */