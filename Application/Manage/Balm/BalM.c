// BalM.c
#include "BalM.h"


/* define for get cell soc from charge end volt - soc */
const sBalM_Soc2VoltType Soc_ChgEndVolt[BALM_MAX_SOC_POINT] =
{
    {900, 3375}, {910, 3376}, {920, 3378}, {930, 3379}, {940, 3381},
    {950, 3384}, {960, 3387}, {970, 3391}, {980, 3402}, {990, 3423}, {1000, 3643}
};

/* define for get cell soc from ocv-soc array */
const sBalM_Soc2VoltType BalM_SocToOcv[BALM_MAX_T_POINT][BALM_MAX_SOCOCV_POINT] =
// [temperature][point] // soc-ocv curve data @ T = 25'C
{
    {   
        {   0, 2692}, { 50, 3123}, {100, 3202}, {150, 3218},
        { 200, 3240}, {250, 3256}, {300, 3272}, {350, 3286},
        { 400, 3289}, {450, 3290}, {500, 3291}, {550, 3293},
        { 600, 3296}, {650, 3314}, {700, 3331}, {750, 3331},
        { 800, 3333}, {850, 3334}, {900, 3336}, {950, 3338},
        {1000, 3449}       
    }
};


/* define for macro and config */
const sBalM_MacroType BalM_Macro =
{
    BALM_MAX_T_POINT,
    BALM_MAX_SOCOCV_POINT,
    BALM_MAX_SOC_POINT,
};

const sBalM_ConfigParaType BalM_ConfigPara =
{
    MAX_V_CALC_BAL_THD,
    MIN_V_CALC_BAL_THD,
    OCV_CALC_BAL_THD,
    MIN_V_START_BAL_THD,
    MIN_V_STOP_BAL_THD,
    
    VOLT_HIGH_BAL_L2,
    VOLT_HIGH_BAL_L1,
    VOLT_LOW_BAL_L1,
    VOLT_LOW_BAL_L2,
    BAL_MIN_VOLT_L1,
    BAL_MIN_VOLT_L2,
    BAL_DELTA_VOLT,
    
    BALM_OCV_LINEAR_RANGE_H1,
    BALM_OCV_LINEAR_RANGE_L1,
    BALM_OCV_LINEAR_RANGE_H2,
    BALM_OCV_LINEAR_RANGE_L2,
    
    BAL_OCV_STANDBY_TIME,
    BAL_CUR,
    BALM_MODE,
};

/* Version Get Interface of Version Module  */
ModuleID_Type BalM_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{      
    ModuleID_Type module_id;
    
#ifdef USE_BALM_A
    module_id = BalM_A_GetVesionModuleVer(VerPtr);
#endif
    
#ifdef USE_BALM_B
    module_id = BalM_B_GetVesionModuleVer(VerPtr);
#endif

#ifdef USE_BALM_C
    module_id = BalM_C_GetVesionModuleVer(VerPtr);
#endif

#ifdef USE_BALM_D
    module_id = BalM_D_GetVesionModuleVer(VerPtr);
#endif

#ifdef USE_BALM_E
    module_id = BalM_E_GetVesionModuleVer(VerPtr);
#endif

#ifdef USE_BALM_F
    module_id = BalM_F_GetVesionModuleVer(VerPtr);
#endif

#ifdef USE_BALM_G
    module_id = BalM_G_GetVesionModuleVer(VerPtr);
#endif

    return module_id;   
}


/* module initial */
void BalM_Init(void)
{
    BalM_ModuleInit();
}

/* module count call back */
void BalM_MainCountCbk(void)
{
    BalM_ModuleCountCbk();
}

/* main call back */
void BalM_MainCbk(void)
{
    BalM_ModuleCbk();
}


