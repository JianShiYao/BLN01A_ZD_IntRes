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
#include "IntRes-AB.h"

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
    
    CanIf_Init(CAR_CAN_CHANNEL, CANIF_BAUDRATE_250K );
    accept.AccCode1 = 0x00000000;
    mask.AccMask1 =   0xFFFFFFFF;

    accept.AccCode2 = 0x00000000;
    mask.AccMask2   = 0xFFFFFFFF;           
    CanIf_SetAcceptanceMaskCode(CAR_CAN_CHANNEL, &accept, &mask);    

    // project engineer must initial these msg
    // if not use Msg set id 0
    sCarCan_Msg[0].Msg.id = 0x18C0EFF4;//BMS_Msg1
    sCarCan_Msg[0].Msg.length = 8;
    sCarCan_Msg[0].Period = TM_MS(100);
    sCarCan_Msg[0].SendCtrl.DelayTime= 0;
    
    sCarCan_Msg[1].Msg.id = 0x18C0EEF4;//BMS_Msg2
    sCarCan_Msg[1].Msg.length = 8;
    sCarCan_Msg[1].Period = TM_MS(100);
    sCarCan_Msg[1].SendCtrl.DelayTime= 0;
    
    sCarCan_Msg[2].Msg.id = 0x10C000F4;//BMS_Msg3
    sCarCan_Msg[2].Msg.length = 8;
    sCarCan_Msg[2].Period = TM_MS(100);
    sCarCan_Msg[2].SendCtrl.DelayTime= 0;
   
    sCarCan_Msg[3].Msg.id = 0x14C000F4;//BMS_Msg4
    sCarCan_Msg[3].Msg.length = 8;
    sCarCan_Msg[3].Period = TM_MS(100);
    sCarCan_Msg[3].SendCtrl.DelayTime= 0;
     
    sCarCan_Msg[4].Msg.id = 0x18C000F4;//BMS_Msg5
    sCarCan_Msg[4].Msg.length = 8;
    sCarCan_Msg[4].Period = TM_MS(100);
    sCarCan_Msg[4].SendCtrl.DelayTime= 0;
    
    sCarCan_Msg[5].Msg.id = 0x1CC000F4;//BMS_Msg6
    sCarCan_Msg[5].Msg.length = 8;
    sCarCan_Msg[5].Period = TM_MS(100);
    sCarCan_Msg[5].SendCtrl.DelayTime= 0;
        /*
    sCarCan_Msg[6].Msg.id = 0x1CC007F4;//BMS_Msg7
    sCarCan_Msg[6].Msg.length = 8;
    sCarCan_Msg[6].Period = TM_MS(100);
    sCarCan_Msg[6].SendCtrl.DelayTime= 0;
    
    sCarCan_Msg[7].Msg.id = 0x1CC008F4;//BMS_Msg8
    sCarCan_Msg[7].Msg.length = 8;
    sCarCan_Msg[7].Period = TM_MS(100);
    sCarCan_Msg[7].SendCtrl.DelayTime= 0;
        */
    sCarCan_Msg[8].Msg.id = 0x18FF00F4;//BMS_Error
    sCarCan_Msg[8].Msg.length = 8;
    sCarCan_Msg[8].Period = TM_MS(100);
    sCarCan_Msg[8].SendCtrl.DelayTime= 0;
    
    sCarCan_Msg[9].Msg.id = 0x04C000F4;//BMS_Temp1
    sCarCan_Msg[9].Msg.length = 8;
    sCarCan_Msg[9].Period = TM_MS(1000);
    sCarCan_Msg[9].SendCtrl.DelayTime= 0;
    /*
    sCarCan_Msg[10].Msg.id = 0x08C000F4;//BMS_Temp2
    sCarCan_Msg[10].Msg.length = 8;
    sCarCan_Msg[10].Period = TM_MS(1000);
    sCarCan_Msg[10].SendCtrl.DelayTime= 0;
    */
    sCarCan_Msg[11].Msg.id = 0x18FF64F4;//BMS_Version
    sCarCan_Msg[11].Msg.length = 8;
    sCarCan_Msg[11].Period = TM_MS(2000);
    sCarCan_Msg[11].SendCtrl.DelayTime= 0;
    /*
    i=0;
    if(1 == Chg_GetAcLinkSt & 1 == Chg_GetChargerSt)
    {
       i=1000;
    }
    else if(0 == Chg_GetAcLinkSt | 0 == Chg_GetChargerSt)
    {
       i=void;
    }
    sCarCan_Msg[12].Msg.id = 0x1806E5F4;//BMS_Charger
    sCarCan_Msg[12].Msg.length = 8;
    sCarCan_Msg[12].Period = TM_MS(i);//stop trs when CC signal is losted
    sCarCan_Msg[12].SendCtrl.DelayTime= 0;
    */
    sCarCan_Msg[12].Msg.id = 0x1806E5F4;//BMS_Charger
    sCarCan_Msg[12].Msg.length = 8;
    sCarCan_Msg[12].Period = TM_MS(1000);//stop trs when CC signal is losted
    sCarCan_Msg[12].SendCtrl.DelayTime= 0;
    
    sCarCan_Msg[13].Msg.id = 0x18FF01F4;//BMS_Power
    sCarCan_Msg[13].Msg.length = 8;
    sCarCan_Msg[13].Period = TM_MS(100);
    sCarCan_Msg[13].SendCtrl.DelayTime= 0;
    
    sCarCan_Msg[14].Msg.id = 0x18FF02F4;//BMS_ChargerPower
    sCarCan_Msg[14].Msg.length = 8;
    sCarCan_Msg[14].Period = TM_MS(200);
    sCarCan_Msg[14].SendCtrl.DelayTime= 0;

    sCarCan_Msg[15].Msg.id = 0x18FF03F4;//Pack_InRes
    sCarCan_Msg[15].Msg.length = 8;
    sCarCan_Msg[15].Period = TM_MS(100);
    sCarCan_Msg[15].SendCtrl.DelayTime= 0;

    sCarCan_Msg[16].Msg.id = 0x18FF04F4;//InRes_1_4
    sCarCan_Msg[16].Msg.length = 8;
    sCarCan_Msg[16].Period = TM_MS(100);
    sCarCan_Msg[16].SendCtrl.DelayTime= 0;
            
    sCarCan_Msg[17].Msg.id = 0x18FF05F4;//InRes_5_8
    sCarCan_Msg[17].Msg.length = 8;
    sCarCan_Msg[17].Period = TM_MS(100);
    sCarCan_Msg[17].SendCtrl.DelayTime= 0;

    sCarCan_Msg[18].Msg.id = 0x18FF06F4;//InRes_9_12
    sCarCan_Msg[18].Msg.length = 8;
    sCarCan_Msg[18].Period = TM_MS(100);
    sCarCan_Msg[18].SendCtrl.DelayTime= 0;    
    
    sCarCan_Msg[19].Msg.id = 0x18FF07F4;//InRes_13_16
    sCarCan_Msg[19].Msg.length = 8;
    sCarCan_Msg[19].Period = TM_MS(100);
    sCarCan_Msg[19].SendCtrl.DelayTime= 0; 
        
    sCarCan_Msg[20].Msg.id = 0x18FF08F4;//InRes_17_20
    sCarCan_Msg[20].Msg.length = 8;
    sCarCan_Msg[20].Period = TM_MS(100);
    sCarCan_Msg[20].SendCtrl.DelayTime= 0;     
    
    // initial other variable
    
    (void)CanIf_SetCanMode(CAR_CAN_CHANNEL,LISTEN_MODE);
}

// call by 10 ms task
void CarCan_MainLoadData(void)
{
    
    uWord wtmp,wtmp1,k;
    uByte btmp,btmp0,btmp1,btmp2,i,j;
    uByte flag_status0,flag_status1,flag_status2,flag_status3,flag_status4,flag_status5,flag_status6,flag_status7;

    sErr_ByteNType bat_byn;
    sErr_ByteNType hd_byn;
    sErr_ByteNType batsys_byn;
        
        //Msg0
        wtmp = Bat_GetSumV(INT_SUMV);
        wtmp /= 10;
        sCarCan_Msg[0].Msg.data[0] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[0].Msg.data[1] = GET_HIGH_BYTE(wtmp);

        wtmp = Bat_GetCurrent(INSCUR);
        if(wtmp >=30000)
        {
           wtmp-=26500;
        }
        else
        {
           wtmp=33500-wtmp;
        } 
        //wtmp = 4000;
        sCarCan_Msg[0].Msg.data[2] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[0].Msg.data[3] = GET_HIGH_BYTE(wtmp);
             
        btmp = 0;
        if(1 == Chg_GetAcLinkSt()) 
        {
           btmp |= 0x09;
        }
        if(0 != Chg_GetCpDutyCycle())
        {
           btmp |= 0x02; 
        }
        
        if(1 == BatSys_GetNegRlySt())  //include switch S2 st=10
        {  
           btmp |= 0x04;
        }
               
        if(1 == Chg_GetAcLinkSt())
        {
           btmp |= 0x10;
        }
        if(1 == Bat_GetMainBalanceSt())
        {
           btmp |= 0x20;
        }
        if(1 == BatSys_GetFanSt())
        {
           btmp |= 0x40;//last byte set to 0
        }               
        sCarCan_Msg[0].Msg.data[4] = btmp;
        
        wtmp = 0;
        wtmp = Bat_GetSOC();
        wtmp /=10;       
        sCarCan_Msg[0].Msg.data[5] = wtmp;

        btmp=btmp0=0;
        
        if(Bat_GetCurrent(INSCUR)>30000)
        {
            btmp |= 0x01;
        }
        else if(0 == Chg_GetChargerSt())
        {
            btmp |= 0x03; 
        }
        else
        {
            btmp |= 0x00; 
        }
 
        btmp0=(Err_GetErrLevel(ERR_BAT)|Err_GetErrLevel(ERR_BATSYS)|Err_GetErrLevel(ERR_HW));
        if(1 == btmp0)
        {
            btmp |= 0x04;  
        }
        if(2 == btmp0)
        {
            btmp |= 0x08;  
        }        
        if(3 == btmp0)
        {
            btmp |= 0x10;  
        }    
        //power feedback enable
        if(900 < Bat_GetSOC())
        {
            btmp |=0x20;
        }
        //battery alarm           
        if(Err_GetErrLevel(ERR_BAT) >=1)
        {
            btmp |=0x40;
        }
        sCarCan_Msg[0].Msg.data[6] = btmp;
        //down power level1
        if((1 == btmp0)|(3 == btmp0))
        {
            btmp |=0x80;  
        }
        sCarCan_Msg[0].Msg.data[6] = btmp;
           
        //down power level2
        btmp=0;
        if((2 == btmp0)|(3 == btmp0))
        {
            btmp |= 0x01;  
        }        
        //iso ultra low
        if(1 == BatSys_GetIsoSt())
        {
            btmp |=0x80;
        }
        sCarCan_Msg[0].Msg.data[7]=btmp;
              
        //Msg1
        wtmp = 0; 
        wtmp = Bat_GetMaxV();  
        sCarCan_Msg[1].Msg.data[0] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[1].Msg.data[1] = GET_HIGH_BYTE(wtmp);
        wtmp = Bat_GetMaxVTotalNo();
        sCarCan_Msg[1].Msg.data[2] = wtmp;
        wtmp = Bat_GetMinV();
        sCarCan_Msg[1].Msg.data[3] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[1].Msg.data[4] = GET_HIGH_BYTE(wtmp);           
        wtmp = Bat_GetMinVTotalNo();
        sCarCan_Msg[1].Msg.data[5] = wtmp;
        wtmp = Bat_GetMaxT();
        sCarCan_Msg[1].Msg.data[6] = wtmp;        
        wtmp = Bat_GetMaxTTotalNo();
        sCarCan_Msg[1].Msg.data[7] = GET_LOW_BYTE(wtmp);             
        /*  
        //Msg2-5 Voltge for 1# to 21# with for-loop 
        for(j = 0;j<4;j++)
        {
           wtmp=wtmp1=0;
           wtmp = Bat_GetCellV(0,1+7*j)/10;
           sCarCan_Msg[2+j].Msg.data[0] = GET_LOW_BYTE(wtmp);
           wtmp1= Bat_GetCellV(0,2+7*j)/10;
           sCarCan_Msg[2+j].Msg.data[1] = GET_LOW_BYTE(wtmp1)<<1|GET_HIGH_BYTE(wtmp);    
           for(i = 2; i < 7; i++)
           { 
             wtmp=wtmp1=0;
             wtmp = Bat_GetCellV(0,i+1+7*j)/10;
             wtmp1= Bat_GetCellV(0,i+7*j)/10;    
             sCarCan_Msg[2+j].Msg.data[i]=GET_LOW_BYTE(wtmp)<<i|GET_HIGH_BYTE(wtmp1)<<(i-1)|GET_LOW_BYTE(wtmp1)>>(9-i);
           }
           wtmp = 0;
           wtmp = Bat_GetCellV(0,7+7*j)/10; 
           sCarCan_Msg[2+j].Msg.data[7] = GET_HIGH_BYTE(wtmp)<<6|GET_LOW_BYTE(wtmp)>>2;
        }
        */
        
        //Msg2 
        wtmp = wtmp1 = 0;
        wtmp = Bat_GetCellV(0,1)/10;
        sCarCan_Msg[2].Msg.data[0]= GET_LOW_BYTE(wtmp);        
        wtmp1= Bat_GetCellV(0,2)/10; 
        sCarCan_Msg[2].Msg.data[1]= GET_LOW_BYTE(wtmp1)<<1|GET_HIGH_BYTE(wtmp);       
        wtmp = Bat_GetCellV(0,3)/10;
        sCarCan_Msg[2].Msg.data[2]= GET_LOW_BYTE(wtmp)<<2|GET_HIGH_BYTE(wtmp1)<<1|GET_HIGH_BYTE(wtmp1)>>7;        
        wtmp1= Bat_GetCellV(0,4)/10;
        sCarCan_Msg[2].Msg.data[3]= GET_LOW_BYTE(wtmp1)<<3|GET_HIGH_BYTE(wtmp)<<2|GET_HIGH_BYTE(wtmp)>>6;        
        wtmp = Bat_GetCellV(0,5)/10;
        sCarCan_Msg[2].Msg.data[4]= GET_LOW_BYTE(wtmp)<<4|GET_HIGH_BYTE(wtmp1)<<3|GET_HIGH_BYTE(wtmp1)>5;        
        wtmp1= Bat_GetCellV(0,6)/10;
        sCarCan_Msg[2].Msg.data[5]= GET_LOW_BYTE(wtmp1)<<5|GET_HIGH_BYTE(wtmp)<<4|GET_HIGH_BYTE(wtmp1)>>4;        
        wtmp = Bat_GetCellV(0,7)/10;
        sCarCan_Msg[2].Msg.data[6]= GET_LOW_BYTE(wtmp)<<6|GET_HIGH_BYTE(wtmp1)<<5|GET_HIGH_BYTE(wtmp1)>>3;
        sCarCan_Msg[2].Msg.data[7]= GET_HIGH_BYTE(wtmp)<<6|GET_HIGH_BYTE(wtmp)>>2;  
        //Msg3
        wtmp = wtmp1 = 0;
        wtmp = Bat_GetCellV(0,8)/10;
        sCarCan_Msg[3].Msg.data[0]= GET_LOW_BYTE(wtmp);       
        wtmp1= Bat_GetCellV(0,9)/10; 
        sCarCan_Msg[3].Msg.data[1]= GET_LOW_BYTE(wtmp1)<<1|GET_HIGH_BYTE(wtmp);       
        wtmp = Bat_GetCellV(0,10)/10;
        sCarCan_Msg[3].Msg.data[2]= GET_LOW_BYTE(wtmp)<<2|GET_HIGH_BYTE(wtmp1)<<1|GET_HIGH_BYTE(wtmp1)>>7;       
        wtmp1= Bat_GetCellV(0,11)/10;
        sCarCan_Msg[3].Msg.data[3]= GET_LOW_BYTE(wtmp1)<<3|GET_HIGH_BYTE(wtmp)<<2|GET_HIGH_BYTE(wtmp)>>6;        
        wtmp = Bat_GetCellV(0,12)/10;
        sCarCan_Msg[3].Msg.data[4]= GET_LOW_BYTE(wtmp)<<4|GET_HIGH_BYTE(wtmp1)<<3|GET_HIGH_BYTE(wtmp1)>5;
        wtmp1= Bat_GetCellV(0,13)/10;
        sCarCan_Msg[3].Msg.data[5]= GET_LOW_BYTE(wtmp1)<<5|GET_HIGH_BYTE(wtmp)<<4|GET_HIGH_BYTE(wtmp1)>>4;
        wtmp = Bat_GetCellV(0,14)/10;
        sCarCan_Msg[3].Msg.data[6]= GET_LOW_BYTE(wtmp)<<6|GET_HIGH_BYTE(wtmp1)<<5|GET_HIGH_BYTE(wtmp1)>>3;
        sCarCan_Msg[3].Msg.data[7]= GET_HIGH_BYTE(wtmp)<<6|GET_HIGH_BYTE(wtmp)>>2;  
        
        //Msg4
        wtmp = wtmp1 = 0;
        wtmp = Bat_GetCellV(0,15)/10;
        sCarCan_Msg[4].Msg.data[0]= GET_LOW_BYTE(wtmp);
        wtmp1= Bat_GetCellV(0,16)/10; 
        sCarCan_Msg[4].Msg.data[1]= GET_LOW_BYTE(wtmp1)<<1|GET_HIGH_BYTE(wtmp);
        wtmp = Bat_GetCellV(0,17)/10;
        sCarCan_Msg[4].Msg.data[2]= GET_LOW_BYTE(wtmp)<<2|GET_HIGH_BYTE(wtmp1)<<1|GET_HIGH_BYTE(wtmp1)>>7;
        wtmp1= Bat_GetCellV(0,18)/10;
        sCarCan_Msg[4].Msg.data[3]= GET_LOW_BYTE(wtmp1)<<3|GET_HIGH_BYTE(wtmp)<<2|GET_HIGH_BYTE(wtmp)>>6;
        wtmp = Bat_GetCellV(0,19)/10;
        sCarCan_Msg[4].Msg.data[4]= GET_LOW_BYTE(wtmp)<<4|GET_HIGH_BYTE(wtmp1)<<3|GET_HIGH_BYTE(wtmp1)>5;
        wtmp1= Bat_GetCellV(0,20)/10;
        sCarCan_Msg[4].Msg.data[5]= GET_LOW_BYTE(wtmp1)<<5|GET_HIGH_BYTE(wtmp)<<4|GET_HIGH_BYTE(wtmp1)>>4;
        wtmp = Bat_GetCellV(0,20)/10;
        sCarCan_Msg[4].Msg.data[6]= GET_LOW_BYTE(wtmp)<<6|GET_HIGH_BYTE(wtmp1)<<5|GET_HIGH_BYTE(wtmp1)>>3;
        sCarCan_Msg[4].Msg.data[7]= GET_HIGH_BYTE(wtmp)<<6|GET_HIGH_BYTE(wtmp)>>2;  
        //Msg5
        wtmp = wtmp1 = 0;
        wtmp = Bat_GetCellV(0,20)/10;
        sCarCan_Msg[5].Msg.data[0]= GET_LOW_BYTE(wtmp); 
        sCarCan_Msg[5].Msg.data[1]= GET_HIGH_BYTE(wtmp);       
        
                                                             
        
        //Msg8 BMSerror 
        flag_status0 =flag_status1 =flag_status2 =flag_status3 =0;
        flag_status4 =flag_status5 =flag_status6 =flag_status7 =0;
        
        bat_byn    = Err_GetBatAllErrLevel();
        hd_byn     = Err_GetHwAllErrLevel();
        batsys_byn = Err_GetBatSysAllErrLevel(1);
        
        /*
        if(0x30 == (bat_byn.By[0] & 0x30)&(1 == Chg_GetChgSt))
        {
           flag_status0 |= 0x01;  
        }
        else if(0x30 == (bat_byn.By[0] & 0x30)&(0 == Chg_GetChgSt)&(3000 > Bat_GetCurrent(INSCUR)))
             {
                 flag_status0 |= 0x02;  
             }
             else if(0x30 == (bat_byn.By[0] & 0x30))
                  {
                      flag_status0 |= 0x04;
                  }
        if((0x03 == (bat_byn.By[0] & 0x03))&(1 == Chg_GetChgSt))
        {
           flag_status0 |= 0x08;  
        }
        else if((0x03 == (bat_byn.By[0] & 0x03))&(0 == Chg_GetChgSt)&(3000 > Bat_GetCurrent(INSCUR)))
             {
                 flag_status0 |= 0x10;  
             }
             else if(0x03 == (bat_byn.By[0] & 0x03))
                  {
                      flag_status0 |= 0x20;
                  }
        */          
        if((3 == Err_GetBatErrLevel(ERR_BAT_CELLV_HIGH))&(1 == Chg_GetChgSt()))
        {
           flag_status0 |= 0x01;  
        }
        else if((3 == Err_GetBatErrLevel(ERR_BAT_CELLV_HIGH))&(0 == Chg_GetChgSt)&(3000 > Bat_GetCurrent(INSCUR)))
             {
                 flag_status0 |= 0x02;  
             }
             else if(3 == Err_GetBatErrLevel(ERR_BAT_CELLV_HIGH))
                  {
                      flag_status0 |= 0x04;
                  }
        if((3 == Err_GetBatErrLevel(ERR_BAT_SUMV_HIGH))&(1 == Chg_GetChgSt()))
        {
           flag_status0 |= 0x08;  
        }
        else if((3 == Err_GetBatErrLevel(ERR_BAT_SUMV_HIGH))&(0 == Chg_GetChgSt)&(3000 > Bat_GetCurrent(INSCUR)))
             {
                 flag_status0 |= 0x10;  
             }
             else if(3 == Err_GetBatErrLevel(ERR_BAT_SUMV_HIGH))
                  {
                      flag_status0 |= 0x20;
                  }        
        if(1 == Err_GetBatErrLevel(ERR_BAT_CELLV_LOW))
        {
           flag_status0 |= 0x40; 
        }
        if(2 == Err_GetBatErrLevel(ERR_BAT_CELLV_LOW))
        {
           flag_status0 |= 0x80; 
        }
        //byte2
        if(3 == Err_GetBatErrLevel(ERR_BAT_CELLV_LOW))
        {
           flag_status1 |= 0x01; 
        }    
       
        if(1 == Err_GetBatErrLevel(ERR_BAT_SUMV_LOW))
        {
           flag_status1 |= 0x02; 
        }
        if(2 == Err_GetBatErrLevel(ERR_BAT_SUMV_LOW))
        {
           flag_status1 |= 0x04;
        }
        if(3 == Err_GetBatErrLevel(ERR_BAT_SUMV_LOW))
        {
           flag_status1 |= 0x08;
        }
        if((Err_GetBatErrLevel(ERR_BAT_CELLV_LOW)>=1)&(1 == Chg_GetChgSt()))
        {
           flag_status1 |= 0x40;
        }
        //byte3 
        if((Err_GetBatErrLevel(ERR_BAT_SUMV_LOW)>=1)&(1 == Chg_GetChgSt()))
        {
           flag_status2 |= 0x02;
        } 
        if(1 == Err_GetBatErrLevel(ERR_BAT_DELTV_ALLPACK))
        {
           flag_status2 |= 0x04;
        }                       
        if(2 == Err_GetBatErrLevel(ERR_BAT_DELTV_ALLPACK))
        {
           flag_status2 |= 0x08;
        }
        if(3 == Err_GetBatErrLevel(ERR_BAT_DELTV_ALLPACK))
        {
           flag_status2 |= 0x10;
        }        
        if(1 == Err_GetBatErrLevel(ERR_BAT_SOC_LOW))
        {
           flag_status2 |= 0x20;
        }                       
        if(2 == Err_GetBatErrLevel(ERR_BAT_SOC_LOW))
        {
           flag_status2 |= 0x40;
        }
        if(3 == Err_GetBatErrLevel(ERR_BAT_SOC_LOW))
        {
           flag_status2 |= 0x80;
        }         
        //byte4
        if(1 == Err_GetBatErrLevel(ERR_BAT_CUR_HIGH_DCH))
        {
           flag_status3 |= 0x01;
        }                       
        if(2 == Err_GetBatErrLevel(ERR_BAT_CUR_HIGH_DCH))
        {
           flag_status3 |= 0x02;
        }
        if(3 == Err_GetBatErrLevel(ERR_BAT_CUR_HIGH_DCH))
        {
           flag_status3 |= 0x04;
        } 
        if(3 == Err_GetBatErrLevel(ERR_BAT_CUR_HIGH_CHG))
        {
           flag_status3 |= 0x10;
        }  
        if(3 == Err_GetBatErrLevel(ERR_BAT_CUR_HIGH_FDBCK))
        {
           flag_status3 |= 0x40;
        } 
        //byte5
        if(1 == Err_GetBatErrLevel(ERR_BAT_T_HIGH))
        {
           flag_status4 |= 0x01;
        }                       
        if(2 == Err_GetBatErrLevel(ERR_BAT_T_HIGH))
        {
           flag_status4 |= 0x02;
        }
        if(3 == Err_GetBatErrLevel(ERR_BAT_T_HIGH))
        {
           flag_status4 |= 0x04;
        }               
        if(Err_GetBatSysErrLevel(ERR_BATSYS_T_HIGH_HEATER) >= 1)
        {
           flag_status4 |= 0x20;
        }
        if(1 == Err_GetBatErrLevel(ERR_BAT_T_LOW))
        {
           flag_status4 |= 0x40;
        }                       
        if(2 == Err_GetBatErrLevel(ERR_BAT_T_LOW))
        {
           flag_status4 |= 0x80;
        }
        //byte6
        if(3 == Err_GetBatErrLevel(ERR_BAT_T_LOW))
        {
           flag_status5 |= 0x01;
        }
        if(1 == Err_GetBatErrLevel(ERR_BAT_DELTT_ALLPACK))
        {
           flag_status5 |= 0x04;
        }                       
        if(2 == Err_GetBatErrLevel(ERR_BAT_DELTT_ALLPACK))
        {
           flag_status5 |= 0x08;
        }
        if(3 == Err_GetBatErrLevel(ERR_BAT_DELTT_ALLPACK))
        {
           flag_status5 |= 0x10;
        }         
        if(1 == Err_GetBatErrLevel(ERR_BATSYS_ISO_NEG))
        {
           flag_status5 |= 0x80;
        } 
        //byte7       
        if(2 == Err_GetBatSysErrLevel(ERR_BATSYS_ISO_NEG))
        {
           flag_status6 |= 0x01;
        }    
        if(0!=Err_GetErrLevel(ERR_BAT)|Err_GetErrLevel(ERR_BATSYS)|Err_GetErrLevel(ERR_HW)|Err_GetErrLevel(ERR_ALL))
        {
           flag_status6 |= 0x10;
        }        
        if(0 != Err_GetHwErrLevel(ERR_HW_CAN0))
        {
           flag_status6 |= 0x10;
        }
        //byte8
    
        
        //Msg9 
        for(i = 0; i<8;i++)
        {
           wtmp = 0;
           wtmp = Bat_GetTemper(0,i+1);
           sCarCan_Msg[9].Msg.data[i]=wtmp;
        }
        /*
        //Msg10 
        for(i = 0; i<4;i++)
        {
           sCarCan_Msg[10].Msg.data[i]=Bat_GetTemper(0,7);
        }
        btmp=0;
        sCarCan_Msg[10].Msg.data[7]=btmp;
        */
        //Msg11
        //Hardware serial number_Primary and secondary //1.2 ASCII
        btmp=0;
        btmp= 0x31;
        sCarCan_Msg[11].Msg.data[0]=btmp;
        btmp=0;
        btmp= 0x32;
        sCarCan_Msg[11].Msg.data[1]=btmp;
        //Hardware serial number_Primary and secondary //1.0 ASCII
        btmp=0;
        btmp = 0x31;
        sCarCan_Msg[11].Msg.data[2]=btmp;
        btmp=0;
        btmp = 0x30;
        sCarCan_Msg[11].Msg.data[3]=btmp;
        //Pack Manufacture  0_BNET 1_Geely
        btmp=0;
        btmp = 0x01;
        sCarCan_Msg[11].Msg.data[4]=btmp;
        //BMS Manufacture   0_BNET 1_Geely
        btmp=0;
        sCarCan_Msg[11].Msg.data[5]=btmp;
        //Cell Manufacture  0_Sammung 1_Geely
        btmp=0;
        btmp = 0x01;
        sCarCan_Msg[11].Msg.data[6]=btmp;
        //Cell type 0_LFP 1_NCM
        btmp=0;
        btmp = 0x01;
        sCarCan_Msg[11].Msg.data[7]=btmp;

        //Msg12
        wtmp=0;
        wtmp=Chg_GetPermitMaxSumV();
        sCarCan_Msg[12].Msg.data[0] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[12].Msg.data[1] = GET_HIGH_BYTE(wtmp);                
        wtmp=0;
        wtmp=Chg_GetPermitMaxCurrent();
        sCarCan_Msg[12].Msg.data[2] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[12].Msg.data[3] = GET_HIGH_BYTE(wtmp);         
               
        btmp=0;
        if(0 == Chg_GetAcLinkSt())
        {
           btmp = 0x01;
        }
        sCarCan_Msg[12].Msg.data[4] = btmp;
        
        btmp=0;
        if(0 != BatSys_GetHeaterSt())
        {
           btmp=0x02; 
        }
        if(0 != BatSys_GetFanSt())
        {
           btmp=0x04;
        }
        sCarCan_Msg[12].Msg.data[5] = btmp; 
        
        wtmp=0;
        wtmp=Bat_GetChgTimes();
        sCarCan_Msg[12].Msg.data[6] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[12].Msg.data[7] = wtmp>>8;
        
        //Msg13
        wtmp=0;
        wtmp=Bat_GetMaxPulseDchPower();
        sCarCan_Msg[13].Msg.data[0] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[13].Msg.data[1] = GET_HIGH_BYTE(wtmp); 
        wtmp=0;
        wtmp=Bat_GetMaxPermitDchPower();
        sCarCan_Msg[13].Msg.data[2] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[13].Msg.data[3] = GET_HIGH_BYTE(wtmp);                
        wtmp=0;
        wtmp=Bat_GetMaxPermitDchPower();
        sCarCan_Msg[13].Msg.data[4] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[13].Msg.data[5] = GET_HIGH_BYTE(wtmp);                 
        wtmp=0;
        wtmp=Bat_GetMaxPermitDchCur();
        sCarCan_Msg[13].Msg.data[6] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[13].Msg.data[7] = GET_HIGH_BYTE(wtmp);
        
        //Msg14
        wtmp=0;
        wtmp=Bat_GetMaxPulseFeedbackPower();
        sCarCan_Msg[14].Msg.data[0] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[14].Msg.data[1] = GET_HIGH_BYTE(wtmp); 
        wtmp=0;
        wtmp=Bat_GetMaxPermitFeedbackPower();
        sCarCan_Msg[14].Msg.data[2] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[14].Msg.data[3] = GET_HIGH_BYTE(wtmp);                
        wtmp=0;
        wtmp=Bat_GetMaxPermitDchPower();
        sCarCan_Msg[14].Msg.data[4] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[14].Msg.data[5] = GET_HIGH_BYTE(wtmp);                 
        wtmp=0;
        wtmp=Chg_GetPermitMaxCurrent();
        wtmp += 350;
        sCarCan_Msg[14].Msg.data[6] = GET_LOW_BYTE(wtmp);
        sCarCan_Msg[14].Msg.data[7] = GET_HIGH_BYTE(wtmp);
        /*
        wtmp=0;
        for(i=0;i<12;i++)
        {
           wtmp +=0x0101;
           Bat_UpdateCellR(0, i + 1, wtmp);
        }
        Bat_UpdateTotalIntRes(wtmp);
        */
        
        //Msg15
        wtmp=0;
        wtmp=Bat_GetTotalIntRes();
        sCarCan_Msg[15].Msg.data[6] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[15].Msg.data[7] = GET_LOW_BYTE(wtmp);
        
        //Msg16
        wtmp=0;
        wtmp=Bat_GetCellR(0, 1);
        sCarCan_Msg[16].Msg.data[0] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[16].Msg.data[1] = GET_LOW_BYTE(wtmp);                
        wtmp=0;
        wtmp=Bat_GetCellR(0, 2);
        sCarCan_Msg[16].Msg.data[2] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[16].Msg.data[3] = GET_LOW_BYTE(wtmp);         
        wtmp=0;
        wtmp=Bat_GetCellR(0, 3);
        sCarCan_Msg[16].Msg.data[4] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[16].Msg.data[5] = GET_LOW_BYTE(wtmp); 
        wtmp=0;
        wtmp=Bat_GetCellR(0, 4);
        sCarCan_Msg[16].Msg.data[6] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[16].Msg.data[7] = GET_LOW_BYTE(wtmp);    

        //Msg17
        wtmp=0;
        wtmp=Bat_GetCellR(0, 5);
        sCarCan_Msg[17].Msg.data[0] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[17].Msg.data[1] = GET_LOW_BYTE(wtmp);                
        wtmp=0;
        wtmp=Bat_GetCellR(0, 6);
        sCarCan_Msg[17].Msg.data[2] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[17].Msg.data[3] = GET_LOW_BYTE(wtmp);         
        wtmp=0;
        wtmp=Bat_GetCellR(0, 7);
        sCarCan_Msg[17].Msg.data[4] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[17].Msg.data[5] = GET_LOW_BYTE(wtmp); 
        wtmp=0;
        wtmp=Bat_GetCellR(0, 8);
        sCarCan_Msg[17].Msg.data[6] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[17].Msg.data[7] = GET_LOW_BYTE(wtmp); 
        
        //Msg18
        wtmp=0;
        wtmp=Bat_GetCellR(0, 9);
        sCarCan_Msg[18].Msg.data[0] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[18].Msg.data[1] = GET_LOW_BYTE(wtmp);                
        wtmp=0;
        wtmp=Bat_GetCellR(0, 10);
        sCarCan_Msg[18].Msg.data[2] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[18].Msg.data[3] = GET_LOW_BYTE(wtmp);         
        wtmp=0;
        wtmp=Bat_GetCellR(0, 11);
        sCarCan_Msg[18].Msg.data[4] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[18].Msg.data[5] = GET_LOW_BYTE(wtmp); 
        wtmp=0;
        wtmp=Bat_GetCellR(0, 12);
        sCarCan_Msg[18].Msg.data[6] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[18].Msg.data[7] = GET_LOW_BYTE(wtmp); 
        
        //Msg18
        wtmp=0;
        wtmp=Bat_GetCellR(0, 13);
        sCarCan_Msg[19].Msg.data[0] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[19].Msg.data[1] = GET_LOW_BYTE(wtmp);                
        wtmp=0;
        wtmp=Bat_GetCellR(0, 14);
        sCarCan_Msg[19].Msg.data[2] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[19].Msg.data[3] = GET_LOW_BYTE(wtmp);         
        wtmp=0;
        wtmp=Bat_GetCellR(0, 15);
        sCarCan_Msg[19].Msg.data[4] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[19].Msg.data[5] = GET_LOW_BYTE(wtmp); 
        wtmp=0;
        wtmp=Bat_GetCellR(0, 16);
        sCarCan_Msg[19].Msg.data[6] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[19].Msg.data[7] = GET_LOW_BYTE(wtmp); 
        
        //Msg18
        wtmp=0;
        wtmp=Bat_GetCellR(0, 17);
        sCarCan_Msg[20].Msg.data[0] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[20].Msg.data[1] = GET_LOW_BYTE(wtmp);                
        wtmp=0;
        wtmp=Bat_GetCellR(0, 18);
        sCarCan_Msg[20].Msg.data[2] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[20].Msg.data[3] = GET_LOW_BYTE(wtmp);         
        wtmp=0;
        wtmp=Bat_GetCellR(0, 19);
        sCarCan_Msg[20].Msg.data[4] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[20].Msg.data[5] = GET_LOW_BYTE(wtmp); 
        wtmp=0;
        wtmp=Bat_GetCellR(0, 20);
        sCarCan_Msg[20].Msg.data[6] = GET_HIGH_BYTE(wtmp);
        sCarCan_Msg[20].Msg.data[7] = GET_LOW_BYTE(wtmp);                             
        /* 
        //Msg16-18 Each CellIntRes with 2 Bytes,High Byte First 
        wtmp=0;
        for(i=0;i<3;i++)
        {
            for(j=1;j<5;j++)
            {
                wtmp=Bat_GetCellR(0,4i+1);
                sCarCan_Msg[16+i].Msg.data[0] = GET_HIGH_BYTE(wtmp);
                sCarCan_Msg[16+i].Msg.data[1] = GET_LOW_BYTE(wtmp);       
                wtmp=Bat_GetCellR(0,4i+2);
                sCarCan_Msg[16+i].Msg.data[2] = GET_HIGH_BYTE(wtmp);
                sCarCan_Msg[16+i].Msg.data[3] = GET_LOW_BYTE(wtmp);  
                wtmp=Bat_GetCellR(0,4i+3);
                sCarCan_Msg[16+i].Msg.data[4] = GET_HIGH_BYTE(wtmp);
                sCarCan_Msg[16+i].Msg.data[5] = GET_LOW_BYTE(wtmp); 
                wtmp=Bat_GetCellR(0,4i+4);
                sCarCan_Msg[16+i].Msg.data[6] = GET_HIGH_BYTE(wtmp);
                sCarCan_Msg[16+i].Msg.data[7] = GET_LOW_BYTE(wtmp);                                    
        }
        
        //Msg16-18 Each CellIntRes with 2 Bytes,High Byte First 
        wtmp=0;
        for(i=0;i<3;i++)
        {
            for(j=1;j<5;j++)
            {
                k=4i+j;
                wtmp=Bat_GetCellR(0,k);
                sCarCan_Msg[16+i].Msg.data[2j-2] = GET_HIGH_BYTE(wtmp);
                sCarCan_Msg[16+i].Msg.data[2j-1] = GET_LOW_BYTE(wtmp);
            }
        }
        */
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