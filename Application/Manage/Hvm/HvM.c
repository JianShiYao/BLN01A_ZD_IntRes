// HvM.c
#include "HvM.h"
#include "AppRelay.h"

/* Version Get Interface of Version Module  */
ModuleID_Type HvM_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{      
    ModuleID_Type module_id;
    
#ifdef USE_HVM_A
    module_id = HvM_A_GetVesionModuleVer(VerPtr);
#endif
    
#ifdef USE_HVM_B
    module_id = HvM_B_GetVesionModuleVer(VerPtr);
#endif

    return module_id;   
}

/* module initial */
void HvM_Init(void)
{
    
}

/* module count call back */
void HvM_MainCountCbk(void)
{
    HvM_ModuleCountCbk();
}

/* main call back */
void HvM_MainCbk(void)
{
    HvM_ModuleCbk();
}


/* charge relay control 
void ChgM_RelayCtrl(void)
{
#ifdef ECU_M_ENABLE_GBCHGIF
    if(((CHGM_FLAG_ENABLE == ChgM_Ctrl.Data.ChgEnable) && (CHGM_FLAG_OK == Chg_GetDcLinkSt()) && (GbChgM_GetStep() >= ChgStep3) && (GbChgM_GetStep() <= ChgStep5))
       || ( (CHGM_FLAG_ENABLE == ChgM_Ctrl.Data.ChgEnable) && (CHGM_FLAG_OK == ChgM_Ctrl.Flag.ChgRx) && (CHGM_FLAG_OK == Chg_GetAcLinkSt()) ) )    
    {
        /* Enable to close relay 
        ChgM_Ctrl.Cnt.ChgRlyOff = 0;
        ChgM_Ctrl.Flag.ChgRlyCtrl = RELAY_ON;
    }
    else
    {
        /* Enable to open relay 
        if(ChgM_Ctrl.Cnt.ChgRlyOff >= CHGM_CNT_RLY_OFF)
        {
            ChgM_Ctrl.Cnt.ChgRlyOff = CHGM_CNT_RLY_OFF;
            ChgM_Ctrl.Flag.ChgRlyCtrl = RELAY_OFF;
        }

        else
        {
            ChgM_Ctrl.Cnt.ChgRlyOff++;
        }
    }
#else
    if( (CHGM_FLAG_OK == ChgM_Ctrl.Flag.ChgRx) && (CHGM_FLAG_ENABLE == ChgM_Ctrl.Data.ChgEnable) )  /* need more condition */
/*    {
        /* Enable to close relay 
        ChgM_Ctrl.Cnt.ChgRlyOff = 0;
        if(ChgM_Ctrl.Cnt.ChgRlyOn >= CHGM_CNT_RLY_ON) // 1S
        {
            ChgM_Ctrl.Cnt.ChgRlyOn = CHGM_CNT_RLY_ON;
            ChgM_Ctrl.Flag.ChgRlyCtrl = RELAY_ON;
        }
        else
        {
            ChgM_Ctrl.Cnt.ChgRlyOn++;
        }
    }
    else
    {
        /* Enable to open relay 
        ChgM_Ctrl.Cnt.ChgRlyOn = 0;
        if(ChgM_Ctrl.Cnt.ChgRlyOff >= CHGM_CNT_RLY_OFF) // 1S
        {
            ChgM_Ctrl.Cnt.ChgRlyOff = CHGM_CNT_RLY_OFF;
            ChgM_Ctrl.Flag.ChgRlyCtrl = RELAY_OFF;
        }
        else
        {
            ChgM_Ctrl.Cnt.ChgRlyOff++;
        }
    }
#endif /* end of charge relay control */

