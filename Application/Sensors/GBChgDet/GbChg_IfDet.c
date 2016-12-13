#include "GbChg_IfDet.h"
#include "AiIf.h"
#include "IocIf.h"
#include "ChargeSt.h"
#include "SchIf.h"
#include "BmsSysSt.h"
#include "SenSorDi.h"


const sVersion_CodeType GbChgDet_VerDef =
{
    MODULE_GBCHGDET_NAME,
    GBCHGDET_SW_MAJOR_VERSION,
    GBCHGDET_SW_MINOR_VERSION,
    GBCHGDET_SW_REVISION_VERSION,
    0,
    0,
    GBCHGDET_DEVELOP_STATUS
};

/* Version Get Interface of Version Module */
ModuleID_Type GbChgDet_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
    *VerPtr = GbChgDet_VerDef;
    return MODULE_GBCHGDET_ID;
}

typedef struct 
{
  uWord Cnt;
}sChgIf_TmCntType;
sChgIf_TmCntType ChgIf_TmCnt;

#define HZ_1K         1000
#define PERSENT_20    (HZ_1K * 20 / 100)
#define FILTER_PERIOD_CNT 100

typedef enum
{
    GBCHGDET_ERR_OK,
    GBCHGDET_AI_UNNORMAT,
    GBCHGDET_DUTY_UNNORMAT
} GbChgDet_ReturnType;

typedef struct
{
    uByte Duty;
    uWord Period;
    uByte FilterCnt;
}GbChgDet_CpType;

GbChgDet_CpType GbChgDet_Cp; 


uWord Gb_ADConver(eAiIf_ChannelIdNumType Ch)
{
    uWord  rslt = 0;
    uWord  result[6];
    uWord  max,min;
    uLWord temp_result;
    uByte i;

    max = 0;
    min = 0xffff;

    for(i = 0; i < 6; i++)
    {
        (void)AiIf_MeasureChannel((uByte)Ch, &result[i]);

        rslt += result[i];

        if(max < result[i])
        {
            max = result[i];
        }
        if(min > result[i])
        {
            min = result[i];
        }
    }


    rslt = rslt - max - min;
    rslt >>= 2;  // ad value;

    temp_result = (uLWord)(rslt);
    temp_result *= ADC_VOLT_CRITERION;
    rslt = (uWord)(temp_result / CPU_ADC_ACCURACY);  /* 0.001V */

    return rslt;
}



void GbChgDet_Ai(eAiIf_ChannelIdNumType Ch, uWord VoltGain, uWord *VoltPtr)
{

    uLWord llwtmp;
    uWord lwd_volt;
    uWord offset;
    uByte gain;
    (void)VoltGain;

    llwtmp = (uLWord)Gb_ADConver(Ch);


    llwtmp *= 111;
    llwtmp /= 1000; 

    lwd_volt = (uWord)(llwtmp); // 0.1V unit

    *VoltPtr = lwd_volt;

}




void GbChgDet_DutyCalc(uByte *DutyPtr)
{

    if(ERR_OK == IocIf_GetIocValue(IOCIF_AC_CP_NO, &GbChgDet_Cp.Period, &GbChgDet_Cp.Duty))
    {
        if((GbChgDet_Cp.Period < (HZ_1K + PERSENT_20)) && (GbChgDet_Cp.Period > (HZ_1K - PERSENT_20)))
        {
            GbChgDet_Cp.FilterCnt = 0;
        }
        else
        {
            GbChgDet_Cp.FilterCnt++;
        }
    }
    else
    {
        GbChgDet_Cp.FilterCnt++;
    }
    
    if(GbChgDet_Cp.FilterCnt >= FILTER_PERIOD_CNT)
    {
        GbChgDet_Cp.FilterCnt = FILTER_PERIOD_CNT;
        GbChgDet_Cp.Duty = 0;
        GbChgDet_Cp.Period = 0;
    }
    
    *DutyPtr = GbChgDet_Cp.Duty;

    Chg_UpdateCpPeriod(GbChgDet_Cp.Period);
 


}

void ChgIfDet_Init(void) 
{
   uByte i;
   uByte *pByte;
   
   pByte = (uByte*)&ChgIf_TmCnt;
   for(i = 0; i < sizeof(ChgIf_TmCnt); i++) 
   {
       *(pByte++) = 0;
   }
   
}

void ChgIfDet_MainCountCbk(void)
{
    (ChgIf_TmCnt.Cnt < 255) ? (ChgIf_TmCnt.Cnt++) : (ChgIf_TmCnt.Cnt = 255);
}

void ChgIfDet_MainCbk() 
{
   uWord Volt;
   uByte duty;
   if(ChgIf_TmCnt.Cnt >= TM_MS(50)) 
   {
      ChgIf_TmCnt.Cnt = 0;
      GbChgDet_Ai(AIIF_CPUAI_DC_P2_NO, 0, &Volt);
      Chg_UpdateCc2Volt(Volt);
      GbChgDet_Ai(AIIF_CPUAI_AC_P3_NO, 0, &Volt);
      Chg_UpdateCCVolt(Volt);
      GbChgDet_DutyCalc(&duty);
      Chg_UpdateCpDutyCycle(duty);
     
      GbChgDet_Ai(AIIF_VOLT_ON, 0, &Volt); 
      BmsSys_UpdateK15Volt(Volt + 3);
      /*if( BmsSys_GetK15Volt() > 50)
      {
         BmsSys_UpdateK15St(1);
      }*/
      
      GbChgDet_Ai(AIIF_SUPPLY_VOLT, 0, &Volt); 
      BmsSys_UpdateK30Volt((Volt + 3));
      if(1 ==  Sensor_GetDiSt(CPU_DI2_ID))
      {        
         BmsSys_UpdateOnBDChgVolt(Volt + 3);
         BmsSys_UpdateOffBDChgVolt(Volt + 3);
      }
      else
      {

         BmsSys_UpdateOnBDChgVolt(0);
         BmsSys_UpdateOffBDChgVolt(0);
      }
     
   }
}

