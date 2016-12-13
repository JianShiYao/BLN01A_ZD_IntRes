// Sch_Cbk.c
#include "Sch_Include.h"

#ifdef __DEBUG_TASK
void Debug_InitTask(void);
#endif

/*
 *************************** Product Code Begin ************************************
 */
extern volatile bool Timer_EnEvent;           /* Enable/Disable events */
void Sch_CounterCallback(void)
{    
    // place timer count in here
    Wdgm_CountCbk();  
    EE_MainCountCbk();
    Err_Count();
    Bat_CountCbk();     
    IntCan_CountCbk();
//    SupplyPowDet_CountCbk();
    LvM_CountCbk();
    BalM_MainCountCbk();
    ThM_MainCountCbk();    
    ChgIfDet_MainCountCbk();
    
#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R)) 
    CurDet_Count();
    SumvDet_MainCountCbk();  
    ChgCan_CountCbk(); 
    SOC_MainCountCbk();  
#endif 
    
#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C)) 
    IsoDet_MainCountCbk();
    DataStore_MainCountCbk(); 
    CarCan_CountCbk();
    ChgM_MainCountCbk();
    SOF_MainCountCbk();
    HvM_MainCountCbk();
    SOH_MainCountCbk();
    IntRes_MainCountCbk();
    Prj_MainCounterCbk();
#endif  

#if((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R) || (ECU_CATEGORY == M_BMU))  
    CellvDetDet_MainCountCbk();
    TemperDet_CountCbk();
#endif
}

void Sch_TimerCallback(void)
{
    // place timer tasks in here
    // call cycle : 5ms 
    IntCan_MainSendMsg();    
#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))      
   ChgCan_MainSendMsg();
#endif
   
#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C))   
    CarCan_MainSendMsg();
#endif 
    
   Actor_RelayMain();  
}

void Sch_MainInit(void)
{
    // place product initial in here   
   #ifndef __DEBUG_DISABLE_PRODUCT_TASK 
    
    /* Basic Module Initialation */
#if(ECU_CATEGORY == M_BCU_D)   
    Prj_PreMainInit();
#endif    
    LvM_Init();
    Wdgm_Init(); 
    Err_Init();         
    EE_Init(); 
    SysConf_Init();
//    SupplyPowDet_Init();
    Actor_RelayInit(); 
    Bat_StatusInit();   
    Bms_SysStInit();
    BatSys_StInit();
    IntCan_Init(); 
           
    BalM_Init();
    ThM_Init();
    
#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))      
    CurDet_Init();
    SumvDet_Init();
    ChgInfo_Init();
    ChgCan_Init();
    ChgM_Init();
    SOC_Init();
#endif 

#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C))
    IsoDet_Init();
    ClockIf_Init();
    CarCan_Init();       
    DataStore_Init();
    SOF_Init();
    SOH_Init();
    IntRes_Init();
    IocIf_Init();
#endif 

#if((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R) || (ECU_CATEGORY == M_BMU))  
   CellvDetDet_Init();
   TemperDet_Init();
#endif

    RumMode_Init();
    
#if(ECU_CATEGORY == M_BCU_D)   
    Prj_PosMainInit();
#endif  
    ChgIfDet_Init();
    Sch_Init();  
   
   #endif /* End of  product task initial, DON't PLACE Product code below */  
   /* NOTE: HERE NO CODE!!! */
   
   /* Use for debug, do not touch */ 
   #ifdef __DEBUG_TASK
   Debug_InitTask();
   #endif     
}

void Sch_MainCallback(void)
{
    /* Add Other task here */ 
       
    EE_MainCbk();
    Err_Main();


    if(0 == IntCan_GetTestModeSt())
    {
        CellvDet_MainCbk();
        TemperDet_MainTemperDet(); 
        Bat_Main();           
    }
    
    IntCan_MainProcess();
    IntCan_MainReceiveMsg();
    LvM_ProcMain();
//    SupplyPowDet_ProcMain();
    BalM_MainCbk();
    ThM_MainCbk();
    
    #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))      
    if(0 == IntCan_GetTestModeSt())
    {
        SumvDet_MainCbk();
        CurDet_Main();
      
    }
    ChgM_MainCbk();
    ChgCan_MainLoadData();
    ChgCan_MainReceiveMsg();
    SOC_MainCbk();
    #endif 


    ChgIfDet_MainCbk(); 
    
    #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C))  
    DataStore_MainCbk(); 
    if(0 == IntCan_GetTestModeSt())
    { 
        IsoDet_MainCbk(); 
    }
    CarCan_ProMain();
    CarCan_MainReceiveMsg();
    SOF_MainCbk();
    HvM_MainCbk();
    SOH_MainCbk();
    IntRes_MainCbk();
    
    Prj_MainProCbk();
    #endif
    
     
    /* Wdg Task */
    Wdgm_MainTrig();       
}

/* Version Get Interface */
const sVersion_CodeType DataLayer_VerDef =
{
  MODULE_DATALAYER_NAME,
  DATALAYER_SW_MAJOR_VERSION,
  DATALAYER_SW_MINOR_VERSION,
  DATALAYER_SW_REVISION_VERSION,
  0,
  0,
  DATALAYER_DEVELOP_STATUS
};

ModuleID_Type DataLayer_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
  *VerPtr = DataLayer_VerDef;
  return MODULE_DATALAYER_ID;   
}
/*
 *************************** Product Code End ************************************
 */
 

 
 
 