/* ChgCan.c */
#include "CanIf_Type.h"
#include "CanIf.h"
#include "Ecu.h"
#include "ChgCan.h"
#include "SchIf.h"
#include "BmsSysSt.h"
#include "BatterySt.h"
#include "BatterySysSt.h"
#include "GbChgCan.h"
//#include "GbChgM-B.h"
#include "ChargeSt.h"




 

#ifdef CHG_CAN_EN

typedef struct
{
    uByte TaskPeriod;
    uByte Life;
}sChgCan_ComType;

sChgCan_ComType  ChgCan_Com;

sChgCan_MsgType ChgCan_Msg[MAX_CHG_CAN_SEND_BUF];    



uByte ChgCan_GetLife(void)
{
    return ChgCan_Com.Life;
}
void ChgCan_UpdateLife(uByte life)
{
    ChgCan_Com.Life = life;
}



void ChgCan_Init(void)
{
    uWord i;
    uByte *ptr;
    sCanIf_AcceptanceCodeType accept;
    sCanIf_AcceptanceMaskType mask;
        
   /* sChgCan_CtrlType *CtrPtr; */
 
    ptr = (uByte*)(ChgCan_Msg);
    for(i = 0; i < sizeof(ChgCan_Msg); i++)
    {
        *(ptr++) = 0;
    }
    
    ptr = (uByte *)(&ChgCan_Com);
    for(i = 0; i < sizeof(ChgCan_Com); i++)
    {
        *(ptr++) = 0;
    }
    
    CanIf_Init(CHG_CAN_CHANNEL, CANIF_BAUDRATE_250K);

    accept.AccCode1 = 0x00000000;
    mask.AccMask1 =   0xFFFFFFFF;

    accept.AccCode2 = 0x00000000;
    mask.AccMask2   = 0xFFFFFFFF;           
    CanIf_SetAcceptanceMaskCode(CHG_CAN_CHANNEL, &accept, &mask);
 
 
#ifdef ECU_M_ENABLE_GBCHGIF
    
     GbChgCan_Init();
 
 #else
     
    // project engineer must initial these msg 
    // if not use Msg set id 0      
    ChgCan_Msg[0].Msg.id = 0x1806E5F4;
    ChgCan_Msg[0].Msg.length = 5;
    ChgCan_Msg[0].Period = TM_MS(1000);
    ChgCan_Msg[0].SendCtrl.DelayTime= 0;
    
  /*  ChgCan_Msg[1].Msg.id = 0x18F20010;
    ChgCan_Msg[1].Msg.length = 8;
    ChgCan_Msg[1].Period = TM_MS(200);
    ChgCan_Msg[1].SendCtrl.DelayTime= 0;
    
    ChgCan_Msg[2].Msg.id = 0x18F30010;
    ChgCan_Msg[2].Msg.length = 8;
    ChgCan_Msg[2].Period = TM_MS(300);
    ChgCan_Msg[2].SendCtrl.DelayTime= 0;

    ChgCan_Msg[3].Msg.id = 0;
    ChgCan_Msg[3].Msg.length = 8;
    ChgCan_Msg[3].Period = TM_MS(400);
    ChgCan_Msg[3].SendCtrl.DelayTime= 0; 
    
    ChgCan_Msg[4].Msg.id = 0;
    ChgCan_Msg[4].Msg.length = 8;
    ChgCan_Msg[4].Period = TM_500MS;
    ChgCan_Msg[4].SendCtrl.DelayTime= 0;
    
    ChgCan_Msg[5].Msg.id = 0;
    ChgCan_Msg[5].Msg.length = 8;
    ChgCan_Msg[5].Period = TM_500MS;
    ChgCan_Msg[5].SendCtrl.DelayTime= 0;
    
    ChgCan_Msg[6].Msg.id = 0;
    ChgCan_Msg[6].Msg.length = 8;
    ChgCan_Msg[6].Period = TM_500MS;
    ChgCan_Msg[6].SendCtrl.DelayTime= 0;
    
    ChgCan_Msg[7].Msg.id = 0;
    ChgCan_Msg[7].Msg.length = 8;
    ChgCan_Msg[7].Period = TM_500MS;
    ChgCan_Msg[7].SendCtrl.DelayTime= 0;
    
    ChgCan_Msg[8].Msg.id = 0;
    ChgCan_Msg[8].Msg.length = 8;
    ChgCan_Msg[8].Period = TM_500MS;
    ChgCan_Msg[8].SendCtrl.DelayTime= 0;
    
    ChgCan_Msg[9].Msg.id = 0;
    ChgCan_Msg[9].Msg.length = 8;
    ChgCan_Msg[9].Period = TM_500MS;
    ChgCan_Msg[9].SendCtrl.DelayTime= 0;   */

#endif                                     
    /* initial other variable */  
          
}

/* call by 10 ms task */
void ChgCan_MainLoadData(void)
{
#ifdef ECU_M_ENABLE_GBCHGIF      
        
#else 
    uWord wtmp;
#endif    
    if(ChgCan_Com.TaskPeriod >= TM_MS(10))
    {
        ChgCan_Com.TaskPeriod = 0;
        SaveStatusReg();
        
        /* call BatterySt interface reach the battery data  */
       
#ifdef ECU_M_ENABLE_GBCHGIF      
         GbChgCan_LoadData();
#else       
        wtmp = Chg_GetPermitMaxSumV(); 
    
        ChgCan_Msg[0].Msg.data[0] = (uByte)(wtmp >> 8);
        ChgCan_Msg[0].Msg.data[1] = (uByte)wtmp;
       
        wtmp = Chg_GetPermitChgCurOn(); 
    
        ChgCan_Msg[0].Msg.data[2] = (uByte)(wtmp >> 8);
        ChgCan_Msg[0].Msg.data[3] = (uByte)wtmp;
        
        wtmp = Chg_GetPermitChgOnSt();
        ChgCan_Msg[0].Msg.data[4] = (uByte)(wtmp);
        
#endif
        RestoreStatusReg();
    }
}

 
void ChgCan_ProcMsg(sCanIf_MsgType msg)
{
   uByte data[8];
   uByte rslt = 0;
   uByte life; 
   sCanIf_MsgType MsgTest;
   
    MsgTest.id = 0x04ff56f4;
    MsgTest.length = 8;

    MsgTest.data[0] = 0xFF;
    MsgTest.data[1] = 0xFF;
    MsgTest.data[2] = 0xFF;
    MsgTest.data[3] = 0xFF;
    MsgTest.data[4] = 0xFF;
    MsgTest.data[5] = 0xFF;
    MsgTest.data[6] = 0xFF;
    MsgTest.data[7] = 0xFF;
 
    if(msg.id == 0x04fff456) 
    {
        (void)CanIf_RequestSend(CHG_CAN_CHANNEL,  &MsgTest, rslt);   
    }
   
   
   
   life = ChgCan_GetLife(); 
   life++;
    
#ifdef ECU_M_ENABLE_GBCHGIF    
    
     GbChg_RxDataFromCharger(msg);
#else   
#endif 
    ChgCan_UpdateLife(life);  
        
}

/* call by 5MS main task  */
void ChgCan_MainSendMsg(void) 
{
 #ifndef ECU_M_ENABLE_GBCHGIF 
    uByte i;
    uWord rslt = 0;
 #endif
 
 #ifdef ECU_M_ENABLE_GBCHGIF   

    GbChgCan_TxData();
    GbChgCan_TpcmProc();
#else

    for(i = 0; i < MAX_CHG_CAN_SEND_BUF; i++)                                
    {
        if(0 != ChgCan_Msg[i].Msg.id)
        {
            ChgCan_Msg[i].SendCtrl.TimeCnt++;
                 
            if(1 == ChgCan_Msg[i].SendCtrl.FirstSendFlag)
            {    
                if(ChgCan_Msg[i].SendCtrl.TimeCnt >= ChgCan_Msg[i].Period) 
                {
                    ChgCan_Msg[i].SendCtrl.TimeCnt = 0;
                    (void)CanIf_RequestSend(CHG_CAN_CHANNEL, &ChgCan_Msg[i].Msg, rslt);        
                }
                
            }
            else
            {
                if(ChgCan_Msg[i].SendCtrl.TimeCnt >= ChgCan_Msg[i].SendCtrl.DelayTime) 
                {
                    ChgCan_Msg[i].SendCtrl.FirstSendFlag = 1;
                    ChgCan_Msg[i].SendCtrl.TimeCnt = 0;
                    (void)CanIf_RequestSend(CHG_CAN_CHANNEL, &ChgCan_Msg[i].Msg, rslt);                        
                }
            }
           

        }
    }

#endif 
 
}


/* call by main task */
void ChgCan_MainReceiveMsg(void)
{   
    GeneralReturnType  rslt;      
    uByte buf_length;
    sCanIf_MsgType msg;
    
    /* have data ? */
    buf_length = CanIf_GetRxBufferLength(CHG_CAN_CHANNEL);
    if(buf_length)
    {
          rslt = CanIf_RxIndication(CHG_CAN_CHANNEL,&msg);
          if(!rslt)
          {
              ChgCan_ProcMsg(msg);
          }
    }
}

void ChgCan_CountCbk(void)
{
    GbChg_CountCbk();
    (ChgCan_Com.TaskPeriod < 255) ? (ChgCan_Com.TaskPeriod++) : (ChgCan_Com.TaskPeriod = 255);
}


#endif


const sVersion_CodeType ChgCan_VerDef =
{
    MODULE_CHGCAN_NAME,
    CHGCAN_SW_MAJOR_VERSION,
    CHGCAN_SW_MINOR_VERSION,
    CHGCAN_SW_REVISION_VERSION,
    0,
    0,
    CHGCAN_DEVELOP_STATUS
};

/* Version Get Interface of Version Module */
ModuleID_Type ChgCan_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
    *VerPtr = ChgCan_VerDef;
    return MODULE_CHGCAN_ID;
}
