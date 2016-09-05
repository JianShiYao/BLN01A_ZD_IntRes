#include "CanIf_Type.h"
#include "CanIf.h"
#include "Ecu.h"
#include "BatterySt.h"
#include "BatterySysSt.h"
#include "ChargeSt.h"
#include "BmsSysSt.h"
#include "IntCan.h"
#include "SysConf.h"
#include "ErrorAlarm.h"
#include "SchIf.h"
#include "EcuDebug.h"
#include "AppDo.h"
#include "DoIf.h"
#include "SensorDi.h"
#include "BalM.h"
//#include "SensorAi.h"
#include "DataStore.h"
//#include "LvM.h"
#include "Project.h"
#include "IntCan.h"
#include "SysConf.h"



typedef struct
{
    uByte ProCnt;
} sPrj_ProType;

sPrj_ProType Prj_Pro;

uByte gby_ReadyFlag; //
uWord gwd_RecvBmuMsgFlag;
uWord gwd_RecvBmuMsgFlagMask;




void Prj_WrDefaultCfg(void)
{
    uByte value_array[30];
    uByte i;

    // initial to 0
    for(i = 0; i < 30; i++) 
    {
        value_array[i] = 0; 
    }

    *((uWord *)&value_array[0]) = 24; // cellv number
    (void)SysConf_UpdataParaToRam(SYSCONF_BMU0_CELLNUM,value_array); 
       
    *((uWord *)&value_array[0]) = 1;  // start cell NO.
    (void)SysConf_UpdataParaToRam(SYSCONF_BMU0_START_CELLNO,value_array);

    *((uWord *)&value_array[0]) = 7; // temperature number
     (void)SysConf_UpdataParaToRam(SYSCONF_BMU0_TEMPERNUM,value_array); 

   
    *((uWord *)&value_array[0]) = 1;  // start temperature NO. ,
    (void)SysConf_UpdataParaToRam(SYSCONF_BMU0_START_TEMPERNO,value_array); 

    for(i = 0; i < 10; i++) 
    {
        value_array[i] = 0;     //fuse pos
    }
    *((uByte *)&value_array[0]) = 0;  
    *((uByte *)&value_array[1]) = 0; 
    (void)SysConf_UpdataParaToRam(SYSCONF_BMU0_FUSE_POS,value_array);

    
    for(i = 0; i < 20; i++) 
    {
        value_array[i] = 0;     
    }
    *((uByte *)&value_array[0]) = 12;  
    *((uByte *)&value_array[1]) = 12; 
    (void)SysConf_UpdataParaToRam(SYSCONF_CELLNUM_PER_CHIP,value_array);
    
    for(i = 0; i < 20; i++) 
    {
        value_array[i] = 0;     
    }
    *((uByte *)&value_array[0]) = 0xDD;  
    *((uByte *)&value_array[1]) = 0xDD; 
    (void)SysConf_UpdataParaToRam(SYSCONF_NO_USE_CELLNUM_PER_CHIP,value_array);
        
}


void Prj_WrChgPara(void) 
{
    uByte value_array[14];
    uByte i;
    
    //charge control para
    for(i = 0; i < 14; i++) 
    {
        value_array[i] = 0; 
    }
    *((uWord *)&value_array[0]) = 4150; // PermitMaxCellV
    *((uWord *)&value_array[2]) = 585;//580; // PermitMaxSumV
    *((uWord *)&value_array[4]) = 2000; // PermitMaxCurrent
    
    *((uByte *)&value_array[6]) = 30;   // PermitMinT
    *((uWord *)&value_array[7]) = 20;   // PermitMinCurrent
    *((uWord *)&value_array[9]) = 20;   // DownCurrentStep
    
    *((uWord *)&value_array[11]) = 2000;  // PermitMinCellV
    *((uByte *)&value_array[13]) = 100;   // PermitMaxT    
    (void)SysConf_UpdataParaToRam(SYSTEMST_CHG_CTRL_PARA,value_array);
}

void Prj_WrHeatPara(void) 
{
    uByte value_array[7];
    uByte i;
    
    //heat control para
    for(i = 0; i < 7; i++) 
    {
        value_array[i] = 0; 
    }
    *((uByte *)&value_array[0]) = 100; // fan_on_temper
    *((uByte *)&value_array[1]) = 100; // fan_off_temper
    *((uByte *)&value_array[2]) = 100; // fan_on_dt    
    *((uByte *)&value_array[3]) = 100; // fan_off_dt
    *((uByte *)&value_array[4]) = 100; // heat_on_temper
    *((uByte *)&value_array[5]) = 100; // heat_off_temper    
    *((uByte *)&value_array[6]) = 100; // heat_off_dt  
    (void)SysConf_UpdataParaToRam(THM_HEAT_MANAGE_PARA,value_array);  
}


void Prj_WrDefaultErrorThrhd(void)
{
    uByte value_array[30];
    uByte i;

    // initial to 0
    for(i = 0; i < 30; i++) 
    {
        value_array[i] = 0; 
    } 
   


    *((uWord *)&value_array[0]) = 581; // SumVHigh
    *((uWord *)&value_array[2]) = 462; // SumVLow
    *((uByte *)&value_array[4]) = 90; //50,//THigh
    *((uByte *)&value_array[5]) = 30; //-10, TLow
    *((uByte *)&value_array[6]) = 10; // DeltTAllPack
    *((uWord *)&value_array[7]) = 300; // DeltVSinglPack    
    *((uWord *)&value_array[9]) = 300; // DeltVAllPack
    *((uWord *)&value_array[11]) = 4150; // CellVHigh
    *((uWord *)&value_array[13]) = 3300; // CellVLow    
    *((uWord *)&value_array[15]) = 600; //60A,CurHighChg
    *((uWord *)&value_array[17]) = 1800;//180A; //CurHighDch
    *((uByte *)&value_array[19]) = 10;// DeltTSinglPack    
    *((uWord *)&value_array[20]) = 1100; // SocHigh
    *((uWord *)&value_array[22]) = 20; // 0% ,SocLow
    *((uByte *)&value_array[24]) = 0xFF; //IntResHighCell
    *((uByte *)&value_array[25]) = 90;//THighPole
    *((uWord *)&value_array[26]) = 0;// SohLow
     
    (void)SysConf_UpdataParaToRam(ERRORALARM_THRHD_LVV1,value_array); 


    *((uWord *)&value_array[0]) = 588; // SumVHigh
    *((uWord *)&value_array[2]) = 400; // SumVLow
    *((uByte *)&value_array[4]) = 95; //55,THigh
    *((uByte *)&value_array[5]) = 23; //-17, TLow
    *((uByte *)&value_array[6]) = 15; // DeltTAllPack
    *((uWord *)&value_array[7]) = 500; // DeltVSinglPack    
    *((uWord *)&value_array[9]) = 500; // DeltVAllPack
    *((uWord *)&value_array[11]) = 4250; // CellVHigh
    *((uWord *)&value_array[13]) =  2500; // CellVLow    
    *((uWord *)&value_array[15]) = 700; // 70A, CurHighChg
    *((uWord *)&value_array[17]) = 2000;//200A//CurHighDch
    *((uByte *)&value_array[19]) = 15;// DeltTSinglPack    
    *((uWord *)&value_array[20]) = 1100; // SocHigh
    *((uWord *)&value_array[22]) = 10; // 0% ,SocLow
    *((uByte *)&value_array[24]) = 0xFF;//IntResHighCell
    *((uByte *)&value_array[25]) = 95; //THighPole
    *((uWord *)&value_array[26]) = 0;// SohLow
     
    (void)SysConf_UpdataParaToRam(ERRORALARM_THRHD_LVV2,value_array); 


    *((uWord *)&value_array[0]) = 650; // SumVHigh
    *((uWord *)&value_array[2]) = 350; // SumVLow
    *((uByte *)&value_array[4]) = 100; //60,//THigh
    *((uByte *)&value_array[5]) = 15; //-25, TLow
    *((uByte *)&value_array[6]) = 20; // DeltTAllPack
    *((uWord *)&value_array[7]) = 600; // DeltVSinglPack    
    *((uWord *)&value_array[9]) = 600; // DeltVAllPack
    *((uWord *)&value_array[11]) = 4500; // CellVHigh
    *((uWord *)&value_array[13]) = 2300; // CellVLow    
    *((uWord *)&value_array[15]) = 800; //80A, CurHighChg
    *((uWord *)&value_array[17]) = 2200;//220A,CurHighDch
    *((uByte *)&value_array[19]) = 20;// DeltTSinglPack    
    *((uWord *)&value_array[20]) = 1100; // SocHigh
    *((uWord *)&value_array[22]) = 0; // 0% ,SocLow
    *((uByte *)&value_array[24]) = 0xFF;////IntResHighCell
    *((uByte *)&value_array[25]) = 100;// //THighPole
    *((uWord *)&value_array[26]) = 0; // SohLow
     
    (void)SysConf_UpdataParaToRam(ERRORALARM_THRHD_LVV3,value_array); 
   
}


// intitial
void Prj_PreMainInit(void)
{
    gby_ReadyFlag = DEFAULT_READY;
}

// check have hardware error
void Prj_PosMainInit(void)
{
    sErr_ByteNType err_byte;
    uByte i;
    uByte btmp;
    uWord wtmp;

    err_byte = Err_GetHwAllErrLevel();
    for(i = 0; i < 8; i++)
    {
        if(err_byte.By[i])
        {
            break;
        }
    }

    // no hardware error
    if(8 == i)
    {
        gby_ReadyFlag |= HARDWARE_READY;
    }


    btmp = Bat_GetBmuNum();
    for(i = 0; i < btmp; i++)
    {
        wtmp = 1;
        wtmp <<= (btmp - 1);
        gwd_RecvBmuMsgFlagMask |= wtmp;
    }
}

// check had receive all bmu first frame
void Prj_UpdateRecvFirFrame(uByte bmu_no)
{
    uWord wtmp = 1;

    wtmp <<= (bmu_no - 1);
    gwd_RecvBmuMsgFlag |= wtmp;

}

// check all bmu frame
void Prj_CheckAllBmuFrame(void)
{
    if((gwd_RecvBmuMsgFlag & gwd_RecvBmuMsgFlagMask) == gwd_RecvBmuMsgFlagMask)
    {
        gby_ReadyFlag |= ALL_BMU_READY;
    }
}

// check Current and sumv init
void Prj_CheckCur(void)
{
    if(Bat_GetCurrent(INSCUR) != 0)
    {
        gby_ReadyFlag |= CUR_READY;
        gby_ReadyFlag |= SUMV_READY;
    }
}

// check all max and min temper had receive
void Prj_CheckMaxMinT(void)
{
    if((Bat_GetMaxT() > 0) && (Bat_GetMinT() > 0))
    {
        gby_ReadyFlag |= MAXMIN_TEMPER_READY;
    }
}

// check all max and min cellv had receive
void Prj_CheckMaxMinV(void)
{
    if((Bat_GetMaxV() > 0) && (Bat_GetMinV() > 0))
    {
        gby_ReadyFlag |= MAXMIN_CELLV_READY;
    }
}




// engener add code here
void Prj_MainPro(void)
{

}


void Prj_MainCounterCbk(void)
{
    (Prj_Pro.ProCnt < 255) ? (Prj_Pro.ProCnt++) : (Prj_Pro.ProCnt = 255);
}

void Prj_MainProCbk(void)
{
    // for engener use for project
    if(Prj_Pro.ProCnt >= TM_MS(100))
    {
        Prj_MainPro();
        Prj_Pro.ProCnt  = 0;
    }

    // these for init flag
    if((gby_ReadyFlag & CUR_READY) != CUR_READY)
    {
        Prj_CheckCur();
    }

    // All Bmu
    if((gby_ReadyFlag & ALL_BMU_READY) != ALL_BMU_READY)
    {
        Prj_CheckAllBmuFrame();
    }

    // MaxMinT
    if((gby_ReadyFlag & MAXMIN_TEMPER_READY) != MAXMIN_TEMPER_READY)
    {
        Prj_CheckMaxMinT();
    }

    // MaxMinV
    if((gby_ReadyFlag & MAXMIN_CELLV_READY) != MAXMIN_CELLV_READY)
    {
        Prj_CheckMaxMinV();
    }

   
}

uByte Prj_GetReadyFlag(void)
{
    return gby_ReadyFlag;
}
