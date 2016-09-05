// HvM.c

#include "HvM-B.h"
#include "ErrorAlarm.h"
#include "AppRelay.h"
#include "BatterySt.h"
#include "ChargeSt.h"
#include "BmsSysSt.h"
#include "BatterySysSt.h"
#include "SensorDi.h"
#include "SchIf.h"
//#include "LvM.h"
#include "DataStore.h"
#include "ChgM-B.h"
#include "AiIf.h"

#ifdef USE_HVM_B

const sVersion_CodeType HvM_VerDef =
{
    MODULE_HVM_NAME,
    HVM_SW_MAJOR_VERSION,
    HVM_SW_MINOR_VERSION,
    HVM_SW_REVISION_VERSION,
    0,
    0,
    HVM_DEVELOP_STATUS
};

/* Version Get Interface of Version Module  */
ModuleID_Type HvM_B_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{      
    *VerPtr = HvM_VerDef;
    return MODULE_HVM_ID;   
}

typedef struct
{
    uByte StartPreChg;
    uByte HvPowerOnEnd;
    uByte FirstBoot;
    uByte ReadMinVolt;
    uByte ReadSumVolt;
    uByte ForbidPowerOn;
    uByte PreFirstEnd;
    uByte NegRelaySt;
    uByte PosRelaySt;
    uByte PreRelaySt;

} sHvM_FlagType;

typedef struct
{
    uWord   StartPre ;
    uWord   EndPre;
    uWord   ReadSumVolt;
    uWord   ReadMinVolt;
    uWord   OpenRelay;
    uWord   WaitVcuCmd;
    uWord   Step;
    uWord   fault;
    uWord   TriggerOff;
    uWord   NegRelayFilter;
} sHvM_CntType;

typedef struct
{
    uByte   Step;
    uByte   BcuCmd;
    uByte   NegNeedChk;
    uByte   PosNeedChk;
    uWord   BcuSumvOutBak;

} sHvM_CtrlHvType;

typedef struct
{
    uByte   IsoErr;
    uWord   SumvOut;
    uWord   SumvIn;
    uWord   Current;
} sHvM_BatInf;

typedef struct
{
    byte cnt;
    uWord CurCnt;
    uWord CurOpenCnt;
} sHvM_TmCntType;

uByte PowerUpFlag;
//#define CHECK_PRE

#define PWR_ON_INIT       0
#define N_CHK    	        1
#define N_ON							2
#define P_CHK			        3
#define WAIT_PWR_ON				4
#define PWR_ON						5
#define PWR_ON_P_CHK  		6
#define WAIT_PWR_OFF			7
#define PWR_OFF_FST_VCU		8
#define PWR_OFF_FST_BCU		9
#define PWR_OFF_SND				10
#define PWR_OFF_END				11


#define MAX_PRE_CUR   20
#define SUMV_20V      200
#define SUMV_50V      500
#define SUMV_100V     1000
#define SUMV_150V     1500
#define SUMV_10V      100
#define CUR_1A        10
#define CUR_10A       100

#define VCU_CTL_PWR_ON     1
#define VCU_CTL_PWR_OFF    0xA5
#define BCU_CTL_P_OFF      1
#define BCU_CTL_N_OFF      2
#define BCU_WAIT_CTL_P_OFF 3
#define HVM_FLAG_OK   1
#define HVM_FLAG_FAIL 0
#define HVM_FLAG_ENABLE   1
#define HVM_FLAG_DISABLE  0
#define HVM_HIGH	1
#define HVM_LOW  0
#define HVM_TRIGST_OFF 0
#define HVM_TRIGST_ON  1

#define HVM_CNT_30MS  6
#define HVM_CNT_50MS  10
#define HVM_CNT_100MS 20
#define HVM_CNT_120MS 24
#define HVM_CNT_150MS 30
#define HVM_CNT_200MS 40
#define HVM_CNT_500MS 100
#define HVM_CNT_600MS 120
#define HVM_CNT_1S    200
#define HVM_CNT_2S    400
#define HVM_CNT_3S    600
#define HVM_CNT_10S   2000
#define HVM_CNT_20S   4000
#define HVM_CNT_2MIN  24000

#define RLY_STA_OPEN     0x00
#define RLY_STA_CLOSE	   0x01
#define RLY_STA_PASTE	   0x02
#define RLY_STA_INVALID	 0x04

#define PRE_CHG_OVERTIME  0x01
#define PRE_CHG_LOAD_OPEN  0x02
#define PRE_CHG_LOAD_SHORT 0x04
#define PRE_CHG_CIRCURT_OPEN 0x08

#define HVM_KEY_ON   2
#define HVM_KEY_ACC  1
#define HVM_KEY_OFF  0

sHvM_FlagType    HvM_Flag;
sHvM_CntType     HvM_Cnt;
sHvM_CtrlHvType  HvM_CtrlHv;
sHvM_ErrType     HvM_Err;
sHvM_BatInf      HvM_BatInf;
sActor_CtrlRelayCmdType HvM_CtrlRelayCmd;
sHvM_TmCntType HvM_TmCnt;
sHvM_VcuInfoType HvM_VcuInfo;

static void HvM_ModuleInit(void);



void HvM_ModuleCountCbk(void)
{
    (HvM_TmCnt.cnt < 255) ? (HvM_TmCnt.cnt++) : (HvM_TmCnt.cnt = 255);
}

void  HvM_ModuleInit(void) 
{
    HvM_TmCnt.cnt = 0;

}

void HvM_ModuleCbk(void) 
{
    uByte return_rslt;
    
    HvM_CtrlRelayCmd.CmdType = IMMED_RELAY_CMD;
    
    if(HvM_TmCnt.cnt >= TM_MS(10))
    { 
       HvM_TmCnt.cnt = 0;
       
       
       
       
    }
}


#endif // #ifdef USE_HVM_B

