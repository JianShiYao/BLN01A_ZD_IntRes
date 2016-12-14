// CarCan.h
#ifndef CARCAN_H
#define CARCAN_H

#include "CanIf_Type.h"
#include "CanIf.h"
#include "Ecu.h"

#include "Version_Type.h"
/*
 * Module Version Define 
 */
#define MODULE_CARCAN_ID               21 
#define MODULE_CARCAN_NAME             "CARCAN"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define CARCAN_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define CARCAN_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define CARCAN_SW_REVISION_VERSION      1   //  size is uWord,max number is 65535                                               
#define CARCAN_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  
/* Version Module Get Interface */
ModuleID_Type CarCan_GetVesionModuleVer(sVersion_CodeType * VerPtr); 

#define MAX_CAR_CAN_SEND_BUF 21

typedef enum
{
    BMSRUNMODE_BMS_INIT,      // 0
    BMSRUNMODE_SYS_WAIT,      // 1
    BMSRUNMODE_SYS_PRE_DCH,   // 2
    BMSRUNMODE_SYS_DCH,       // 3
    BMSRUNMODE_SYS_PRE_CHG,   // 4
    BMSRUNMODE_SLOW_CHG,      // 5
    BMSRUNMODE_FAST_CHG,      // 6          
    BMSRUNMODE_FAULT,         // 7
}eBmsRunMode_ModeType;

typedef struct
{
    uWord TimeCnt;
    uByte FirstSendFlag;
    uByte DelayTime; 
}sCarCanCtrlType;

typedef struct
{
    sCanIf_MsgType Msg;
    uWord Period;
    sCarCanCtrlType SendCtrl; 
}sCarCanMsgType;


#ifdef CAR_CAN_EN
//extern void CarCan_ProcMsg(sCanIf_MsgType msg); 
extern void CarCan_Init(void);
//extern void CarCan_MainLoadData(void);
extern void CarCan_MainReceiveMsg(void);
extern void CarCan_MainSendMsg(void);
extern void CarCan_CountCbk(void);
extern void CarCan_ProMain(void);
#endif                            


#endif /* CARCAN_H */