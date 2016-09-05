// ChgCan.h
#ifndef CHGCAN_H
#define CHGCAN_H

#include "CanIf_Type.h"
//#include "CanIf.h"
//#include "Ecu.h"
#include "GeneralTypeDef.h"
#include "Version_Type.h"
// Module Version Define
#define MODULE_CHGCAN_ID           18
#define MODULE_CHGCAN_NAME         "CHGCAN"  // platform name include "EV02" "EV03" "EV04" "EV05"
#define CHGCAN_SW_MAJOR_VERSION    1      // size is uByte,max number is 255
#define CHGCAN_SW_MINOR_VERSION    1      // size is uWord,max number is 65535
#define CHGCAN_SW_REVISION_VERSION 0      // size is uWord,max number is 65535
#define CHGCAN_DEVELOP_STATUS      "" // status include "beta" "rc" ""
extern ModuleID_Type ChgCan_GetVesionModuleVer(sVersion_CodeType * VerPtr);
  
#define MAX_CHG_CAN_SEND_BUF 1

typedef struct
{
    uWord TimeCnt;
    uByte FirstSendFlag;
    uByte DelayTime; 
    uByte Flg;
}sChgCan_CtrlType;



typedef struct
{
    sCanIf_MsgType Msg;
    uWord Period;
    sChgCan_CtrlType SendCtrl; 
    
}sChgCan_MsgType;


#ifdef CHG_CAN_EN
extern void ChgCan_Init(void);
extern void ChgCan_MainReceiveMsg(void);
extern void ChgCan_MainSendMsg(void);
extern void ChgCan_CountCbk(void);
extern void ChgCan_MainLoadData(void);

extern uByte ChgCan_GetLife(void);
extern void ChgCan_UpdateLife(uByte life);

#endif



#endif /* CARCAN_H *//