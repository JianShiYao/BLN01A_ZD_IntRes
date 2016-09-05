// CarCan.c
#include "CanIf_Type.h"
#include "CanIf.h"
#include "Ecu.h"
#include "CarCan.h"
#include "SchIf.h"
#include "BmsSysSt.h"
#include "BatterySt.h"
#include "BatterySysSt.h"
#include "ChargeSt.h"
#include "ErrorAlarm.h"
#include "HvM.h"

sCarCanMsgType sCarCan_Msg[MAX_CAR_CAN_SEND_BUF];
typedef struct
{
    uByte MsgLoadProCnt;
    uWord CanErrCnt;
}sCarCan_ProCntType;

#define CARCAN_TM_MS(cnt) (cnt / 10)

#define GET_HIGH_BYTE(val) ((uByte)(val >> 8))
#define GET_LOW_BYTE(val)   ((uByte)(val))
#define CarCan_FLAG_OK     1
#define CarCan_FLAG_FAIL   0




#define CARCAN_ERR_L1_MS CARCAN_TM_MS(2000)   // mS
#define CARCAN_ERR_L2_MS CARCAN_TM_MS(5000)   // mS

sCarCan_ProCntType CarCan_ProCnt;
static void CarCan_CheckStatus(void);

//#ifdef CAR_CAN_EN
void CarCan_Init(void)
{
    uWord i;
    uByte *ptr;

    sCanIf_AcceptanceCodeType accept;
    sCanIf_AcceptanceMaskType mask;


    ptr = (uByte*)sCarCan_Msg;
    for(i = 0; i < sizeof(sCarCan_Msg); i++)
    {
        *(ptr++) = 0;
    }
    
    CanIf_Init(CAR_CAN_CHANNEL, CANIF_BAUDRATE_500K );
    accept.AccCode1 = 0x00000000;
    mask.AccMask1 =   0xFFFFFFFF;

    accept.AccCode2 = 0x00000000;
    mask.AccMask2   = 0xFFFFFFFF;           
    CanIf_SetAcceptanceMaskCode(CAR_CAN_CHANNEL, &accept, &mask);    

    // project engineer must initial these msg
    // if not use Msg set id 0
    sCarCan_Msg[0].Msg.id = 0x450;//0x8A000000; //
    sCarCan_Msg[0].Msg.length = 8;
    sCarCan_Msg[0].Period = TM_MS(10);
    sCarCan_Msg[0].SendCtrl.DelayTime= 0;

    sCarCan_Msg[1].Msg.id = 0x451;//0x8A200000; //
    sCarCan_Msg[1].Msg.length = 8;
    sCarCan_Msg[1].Period = TM_MS(20);
    sCarCan_Msg[1].SendCtrl.DelayTime= 0;

    sCarCan_Msg[2].Msg.id = 0x452;//0x8A600000; //
    sCarCan_Msg[2].Msg.length = 8;
    sCarCan_Msg[2].Period = TM_MS(200);
    sCarCan_Msg[2].SendCtrl.DelayTime= 0;

    sCarCan_Msg[3].Msg.id = 0x453;//0x8A600000; //
    sCarCan_Msg[3].Msg.length = 8;
    sCarCan_Msg[3].Period = TM_MS(500);
    sCarCan_Msg[3].SendCtrl.DelayTime= 0;

    sCarCan_Msg[4].Msg.id = 0x454;//0x8A800000;  //
    sCarCan_Msg[4].Msg.length = 8;
    sCarCan_Msg[4].Period = TM_MS(1000);
    sCarCan_Msg[4].SendCtrl.DelayTime= 0;

    sCarCan_Msg[5].Msg.id = 0x650;//0xCA000000; //
    sCarCan_Msg[5].Msg.length = 8;
    sCarCan_Msg[5].Period = TM_MS(500);
    sCarCan_Msg[5].SendCtrl.DelayTime= 0;

    sCarCan_Msg[6].Msg.id = 0;
    sCarCan_Msg[6].Msg.length = 8;
    sCarCan_Msg[6].Period = TM_100MS;
    sCarCan_Msg[6].SendCtrl.DelayTime= 0;

    sCarCan_Msg[7].Msg.id = 0;
    sCarCan_Msg[7].Msg.length = 8;
    sCarCan_Msg[7].Period = TM_500MS;
    sCarCan_Msg[7].SendCtrl.DelayTime= 0;

    sCarCan_Msg[8].Msg.id = 0;
    sCarCan_Msg[8].Msg.length = 8;
    sCarCan_Msg[8].Period = TM_500MS;
    sCarCan_Msg[8].SendCtrl.DelayTime= 0;

    sCarCan_Msg[9].Msg.id = 0;
    sCarCan_Msg[9].Msg.length = 8;
    sCarCan_Msg[9].Period = TM_500MS;
    sCarCan_Msg[9].SendCtrl.DelayTime= 0;
    // initial other variable
    
    (void)CanIf_SetCanMode(CAR_CAN_CHANNEL,LISTEN_MODE);
}

// call by 10 ms task
void CarCan_MainLoadData(void)
{
    uWord wtmp;
    uByte btmp,btmp1,btmp2,i;

    sErr_ByteNType bat_byn;
    sErr_ByteNType hd_byn;
    sErr_ByteNType batsys_byn;
        // 0x450//
        sCarCan_Msg[0].Msg.data[0] = 0;

        wtmp = Bat_GetSOC();
        wtmp /= 4;
        sCarCan_Msg[0].Msg.data[0] = (uByte)wtmp;

        wtmp = Bat_GetMaxFeedBackCur();
        wtmp *= 10;
        sCarCan_Msg[0].Msg.data[2] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[0].Msg.data[3] = GET_LOW_BYTE(wtmp);

        wtmp = Bat_GetMaxPermitDchCur();
        wtmp *= 10;
        sCarCan_Msg[0].Msg.data[4] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[0].Msg.data[5] = GET_LOW_BYTE(wtmp);
        
        for(i = 0; i < 250; i++)
        {
            asm NOP;
        }


}


static void CarCan_ProcMsg(sCanIf_MsgType msg)
{
   uByte data[8];
   uByte rslt = 0; 
   sCanIf_MsgType MsgTest;
   
   sHvM_VcuInfoType VcuInfo;

    MsgTest.id = 0x00000002;
    MsgTest.length = 8;

    MsgTest.data[0] = 0xFF;
    MsgTest.data[1] = 0xFF;
    MsgTest.data[2] = 0xFF;
    MsgTest.data[3] = 0xFF;
    MsgTest.data[4] = 0xFF;
    MsgTest.data[5] = 0xFF;
    MsgTest.data[6] = 0xFF;
    MsgTest.data[7] = 0xFF;
 
    if(msg.id == 0x00000001) 
    {
        (void)CanIf_RequestSend(CAR_CAN_CHANNEL,  &MsgTest, rslt);   
    }
    
    
    if(0x212 == msg.id)
    {
        VcuInfo.Cmd = msg.data[0];
     //   HvM_UpdateVcuInfo(&VcuInfo);
        
        CarCan_ProCnt.CanErrCnt = 0;
    }
    if(0x6d0 == msg.id)
    {
    
    }

}


// call cycle 5mS by task
void CarCan_MainSendMsg(void)
{
    uByte i;
    uWord rslt = 0;

    for(i = 0; i < MAX_CAR_CAN_SEND_BUF; i++)
    {
        if(0 != sCarCan_Msg[i].Msg.id)
        {
            sCarCan_Msg[i].SendCtrl.TimeCnt++;
            if(1 == sCarCan_Msg[i].SendCtrl.FirstSendFlag)
            {
                if(sCarCan_Msg[i].SendCtrl.TimeCnt >= sCarCan_Msg[i].Period)
                {
                    sCarCan_Msg[i].SendCtrl.TimeCnt = 0;
                    (void)CanIf_RequestSend(CAR_CAN_CHANNEL, &sCarCan_Msg[i].Msg, rslt);
                }

            }
            else
            {
                if(sCarCan_Msg[i].SendCtrl.TimeCnt >= sCarCan_Msg[i].SendCtrl.DelayTime)
                {
                    sCarCan_Msg[i].SendCtrl.FirstSendFlag = 1;
                    sCarCan_Msg[i].SendCtrl.TimeCnt = 0;
                    (void)CanIf_RequestSend(CAR_CAN_CHANNEL, &sCarCan_Msg[i].Msg, rslt);
                }
            }
        }
    }

}

//call by main task
void CarCan_MainReceiveMsg(void)
{   
    GeneralReturnType  rslt;      
    uByte buf_length;
    sCanIf_MsgType msg;
    
    /* have data ? */
    buf_length = CanIf_GetRxBufferLength(CAR_CAN_CHANNEL);
    while(buf_length)
    {
         rslt = CanIf_RxIndication(CAR_CAN_CHANNEL,&msg);
         if(!rslt)
         {
             CarCan_ProcMsg(msg);
         } 
         buf_length--;       
    }

}
static void CarCan_CheckStatus(void)
{
    CarCan_ProCnt.CanErrCnt++;
    if(CarCan_ProCnt.CanErrCnt >= CARCAN_ERR_L2_MS)  // 500* 10ms
    {
        (void)Err_UpdateHwErrLevel(ERR_HW_CAN0, ERR_LEVEL_TWO);
        CarCan_ProCnt.CanErrCnt = 500;
    }
    else if(CarCan_ProCnt.CanErrCnt >= CARCAN_ERR_L1_MS)
    {
        (void)Err_UpdateHwErrLevel(ERR_HW_CAN0, ERR_LEVEL_ONE);
    }
}

void CarCan_CountCbk(void)
{
    (CarCan_ProCnt.MsgLoadProCnt < 255) ? (CarCan_ProCnt.MsgLoadProCnt++) : (CarCan_ProCnt.MsgLoadProCnt = 255);
 
}

void CarCan_ProMain(void)
{
    if(CarCan_ProCnt.MsgLoadProCnt >= TM_MS(10))
    {

        SaveStatusReg();
        CarCan_MainLoadData();   
 
        RestoreStatusReg();
        CarCan_ProCnt.MsgLoadProCnt = 0;
        
//        CarCan_CheckStatus();
    }

}

//#endif


/* Version Get Interface */
const sVersion_CodeType CarCan_VerDef =
{
  MODULE_CARCAN_NAME,
  CARCAN_SW_MAJOR_VERSION,
  CARCAN_SW_MINOR_VERSION,
  CARCAN_SW_REVISION_VERSION,
  0,
  0,
  CARCAN_DEVELOP_STATUS
};

ModuleID_Type CarCan_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
  *VerPtr = CarCan_VerDef;
  return MODULE_CARCAN_ID;   
}