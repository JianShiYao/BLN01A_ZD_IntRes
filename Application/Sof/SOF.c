// SOF.c
#include "SOF.h"

#ifdef USE_SOF_A
#include "SOF-A.h"
#endif

#ifdef USE_SOF_B
#include "SOF-B.h"
#endif

/***************************** volt modify Array ********************************/
const sSOF_VoltLmtType VoltLowArray[SOF_MAX_VOLT_POINT] = 
{
    {3000, 50}, {3020, 60}, {3040, 70}, {3060, 80},
};

const sSOF_VoltLmtType VoltHighArray[SOF_MAX_VOLT_POINT] = 
{
    {3600, 50}, {3580, 60}, {3560, 70}, {3540, 80},
};
/**************************** end volt modify Array *******************************/

/*
 * temperatrue point
 * unit is 1 degree
 */
const sByte DchTemperArray[SOF_MAX_T_POINT] = {-35,-30,-20,-10,-1,0,10,14,15,20,34,35,40,44,50};
const sByte FbTemperArray[SOF_MAX_T_POINT] = {-35,-30,-20,-10,-1,0,10,14,15,20,34,35,40,44,50};
/*
 * soc point
 * unit is 0.1%
 */
const uWord SocArray[SOF_MAX_SOC_POINT] = {0,50,100,200,300,400,500,600,700,800,900,1000};


/********************************* CURRENT Array ********************************/
/*
 * max last current of discharge
 * unit is A
 */
const uWord CnstDisCurArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{
// -35 -30,-20,-10,-1 0,  10,  14,  15,  20,  34,   35,  40,  44,  50

    {0,0, 0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,   0  }, // current in 0% soc
    {0,0, 30, 30, 30, 30, 30,  30,  30,  30,  30,   30,  30,  30,  30 }, // current in 5% soc
    {0,0, 30, 30, 100,100,100, 100, 100, 100, 100,  100, 100, 100, 100}, // current in 10% soc
    {0,0, 30, 100,200,200,200, 200, 200, 200, 200,  200, 200, 200, 200}, // current in 20% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 30% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 40% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 50% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 60% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 70% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 80% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 90% soc
    {0,30,100,200,350,350,350, 350, 350, 350, 350,  350, 350, 350, 350}, // current in 100% soc
};

/*
 * max last current of charge
 * unit is A
 */
const uWord CnstFeedbackCurArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{
//  -35 -30,-20,-10 ,-1  0  , 10 ,14, 15,  20,  34   35, 40 ,  44    ,50
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 0% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 5% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 10% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 20% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 30% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 40% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 50% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 60% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 70% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  40,  40,  40, 40,   40,   0}, // current in 80% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  20,  20,  20, 20,   20,   0}, // current in 90% soc
    {0,  0,  0,  0,  0,  10,  10, 10, 10,  20,  20,  20, 20,   20,   0}, // current in 100% soc

};

/*
 * max pulse current of discharge
 * unit is A
 */
const uWord PulseDisCurArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{
//  -35,-30,-20,-10 ,-1  0    10 , 14, 15, 20, 34, 35, 40,  44 ,50
    {0,  0,  0,  0,  0,  0,   0,   0,  0,  0,  0,  0,  0,   0,  0}, // current in 0% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100, 100,0}, // current in 5% soc
    {0,  0,  0,  0,  0,  150, 150, 150,350,350,350,200,200, 200,0}, // current in 10% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 20% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 30% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 40% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 50% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 60% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 70% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 80% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 90% soc
    {0,  0,  0,  0,  0,  150, 150, 150,300,300,300,200,200, 200,0}, // current in 100% soc
/*
    {0}, // current in 0% soc
    {0}, // current in 5% soc
    {0}, // current in 10% soc
    {0}, // current in 20% soc
    {0}, // current in 30% soc
    {0}, // current in 40% soc
    {0}, // current in 50% soc
    {0}, // current in 60% soc
    {0}, // current in 70% soc
    {0}, // current in 80% soc
    {0}, // current in 90% soc
    {0}, // current in 100% soc
*/
};

/*
 * max pulse current of charge
 * unit is A
 */
const uWord PulseFeedbackCurArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{
//  -35,-30,-20,-10 ,-1  0  , 10 , 14, 15, 20, 34, 35, 40 ,44 ,50
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 0%  soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 5%  soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 10% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 20% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 30% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 40% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 50% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 60% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 70% soc
    {0,  0,  0,  0,  0,  100, 100, 100,100,100,100,100,100,100,0}, // current in 80% soc
    {0,  0,  0,  0,  0,  50,  50,  50, 50, 50, 50, 50, 50, 50, 0}, // current in 90% soc
    {0,  0,  0,  0,  0,  30,  30,  30, 30, 30, 30, 30, 30, 30, 0}, // current in 100% soc
};
/****************************** End CURRENT Array ********************************/



/********************************* POWER Array ********************************/
/*
 * max last power of discharge
 * unit is W
 */
const uWord CnstDisPowArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{
//  -35,-30,-20,-10,-1 0  ,    10 ,    14,    15,    20,    34,    35,    40  ,  44  ,  50
    {0, 0, 0,  0,  0,  0,      0,      0,     0,     0,     0,     0,     0,     0,     0}, // power in 0%  soc
    {0, 0, 0,  0,  0,  3000,   3000,   3000,  5000,  5000,  5000,  4000,  4000,  4000,  0}, // power in 5%  soc
    {0, 0, 0,  0,  0,  5000,   5000,   5000,  8400,  8400,  8400,  6000,  6000,  6000,  0}, // power in 10% soc
    {0, 0, 0,  0,  0,  8000,   8000,   8000,  13500, 13500, 13500, 10000, 10000, 10000, 0}, // power in 20% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 30% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 40% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 50% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 60% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 70% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 80% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 90% soc
    {0, 0, 0,  0,  0,  10000,  10000,  10000, 16800, 16800, 16800, 12000, 12000, 12000, 0}, // power in 100% soc
};

/*
 * max last max power of charge
 * unit is W
 */
const uWord CnstFeedbackPowArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{
//  -35,-30,-20,-10,-1  0  ,  10 ,   14,   15,   20,   34,   35,   40 ,  44 ,  50
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 0%  soc
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 5%  soc
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 10% soc    
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 20% soc
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 30% soc
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 40% soc
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 50% soc
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 60% soc 
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 70% soc
    {0 , 0, 0,  0, 0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 80% soc          
    {0 , 0, 0,  0, 0,  3000,  3000,  3000, 4000, 4000, 4000, 4000, 3000, 3000, 0}, // power in 90% soc
    {0 , 0, 0,  0, 0,  3000,  3000,  3000, 4000, 4000, 4000, 4000, 3000, 3000, 0}, // power in 100% soc
    
};

/*
 * max pulse power of discharge
 * unit is W
 */
const uWord PulseDisPowArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{                                                                                     
//  -35,-30,-20,-10 ,-1,0  ,  10 ,   14,    15,    20,    34,    35,    40  ,  44  ,  50
    {0, 0,  0,  0,  0, 0,     0 ,    0,     0,     0,     0,     0,     0,     0,     0}, // power in 0%  soc
    {0, 0,  0,  0,  0, 5000,  5000,  5000,  7300,  7300,  7300,  5000,  5000,  5000,  0}, // power in 5%  soc
    {0, 0,  0,  0,  0, 7000,  7000,  7000,  10000, 10000, 10000, 7000,  7000,  7000,  0}, // power in 10% soc
    {0, 0,  0,  0,  0, 12000, 12000, 12000, 15000, 15000, 15000, 12000, 12000, 12000, 0}, // power in 20% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 30% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 40% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 50% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 60% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 70% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 80% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 90% soc
    {0, 0,  0,  0,  0, 15000, 15000, 15000, 21900, 21900, 21900, 16000, 16000, 16000, 0}, // power in 100% soc
};

/*
 * max pulse power of charge
 * unit is W
 */
const uWord PulseFeedbackPowArray[SOF_MAX_SOC_POINT][SOF_MAX_T_POINT] =
{
//  -35,-30,-20,-10 ,-1  0  ,  10 ,  14,  15,  20,  34,  35,  40  ,44  ,50
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 0%  soc
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 5%  soc
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 10% soc    
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 20% soc
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 30% soc
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 40% soc
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 50% soc
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 60% soc 
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 70% soc
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 7300, 7300, 7300, 7300, 4000, 4000, 0}, // power in 80% soc          
    {0, 0,  0,  0,  0,  3500,  3500,  3500, 4000, 4000, 4000, 4000, 3000, 3000, 0}, // power in 90% soc
    {0, 0,  0,  0,  0,  0 ,    0 ,    0 ,   0 ,   0 ,   0  ,  0 ,   0 ,   0 ,   0}, // power in 100% soc
};
/****************************** End POWER Array ********************************/


/* define struct for macro and config parameter */
const sSOF_MacroType SOF_Macro =
{
    SOF_MAX_SOC_POINT,
    SOF_MAX_T_POINT,
    SOF_MAX_VOLT_POINT,
    SOF_DCH_CUR_VOLT_MODIFY,
    SOF_DCH_CUR_ERR_MODIFY,
    SOF_FD_CUR_VOLT_MODIFY,
    SOF_FD_CUR_ERR_MODIFY,
    SOF_PLUSE_CUR_MODIFY,      
    SOF_CALC_MAX_POWER,
    SOF_USER_FUN,
};

const sSOF_ConfigParaType SOF_ConfigPara =
{
    SOF_MINV_SELF_CALC_CUR,
    
    /* use for smooth permit current or power */
    SOF_CONST_DCHCUR_SMOOTH_UNIT,
    SOF_CONST_FEEDBACKCUR_SMOOTH_UNIT,
    SOF_PULSE_DCHCUR_SMOOTH_UNIT,
    SOF_PULSE_FEEDBACKCUR_SMOOTH_UNIT,
    
    SOF_CONST_DCHPOW_SMOOTH_UNIT,
    SOF_CONST_FEEDBACKPOW_SMOOTH_UNIT,
    SOF_PULSE_DCHPOW_SMOOTH_UNIT,
    SOF_PULSE_FEEDBACKPOW_SMOOTH_UNIT,
    
    /* for discharge cur modify */
    SOF_MODIFY_CELLV_LOW_L1,
    SOF_MODIFY_CELLV_LOW_L2,  
    SOF_MODIFY_SUMV_LOW_L1,
    SOF_MODIFY_SUMV_LOW_L2,    
    SOF_MODIFY_DCHCUR_HIGH_L1,    
    SOF_MODIFY_DCHCUR_HIGH_L2, 
    
    /* for feedback cur modify */   
    SOF_MODIFY_CELLV_HIGH_L1,     
    SOF_MODIFY_CELLV_HIGH_L2,     
    SOF_MODIFY_SUMV_HIGH_L1,
    SOF_MODIFY_SUMV_HIGH_L2,
    SOF_MODIFY_FDCUR_HIGH_L1,
    SOF_MODIFY_FDCUR_HIGH_L2,
    
    /* for both discharge and feedback cur modify */
    SOF_MODIFY_DETVOLT_L1,     
    SOF_MODIFY_DETVOLT_L2,     
    SOF_MODIFY_DETTEMP_L1,  
    SOF_MODIFY_DETTEMP_L2,  
    SOF_MODIFY_INTCAN_ERR,        
};
/* end define struct for macro and config parameter */


#define SOF_CONST_DCHCUR       0
#define SOF_CONST_FEEDBACKCUR  1
#define SOF_PULSE_DCHCUR       2
#define SOF_PULSE_FEEDBACKCUR  3

#define SOF_CONST_DCHPOW       4
#define SOF_CONST_FEEDBACKPOW  5
#define SOF_PULSE_DCHPOW       6
#define SOF_PULSE_FEEDBACKPOW  7

/* Version Get Interface of Version Module  */
ModuleID_Type Sof_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{      
    ModuleID_Type module_id;
    
#ifdef USE_SOF_A
    module_id = SOF_A_GetVesionModuleVer(VerPtr);
#endif

#ifdef USE_SOF_B
    module_id = SOF_B_GetVesionModuleVer(VerPtr);
#endif

    return module_id;   
}

/* module initial */
void SOF_Init(void)
{
    SOF_ModuleInit();
    /*** !!! Here you can place your own code !!! ***/
     
    /*** !!! end of your own code !!! ***/
}

/* module count call back */
void SOF_MainCountCbk(void)
{
    SOF_ModuleCountCbk();
    /*** !!! Here you can place your own code !!! ***/
     
    /*** !!! end of your own code !!! ***/
}

/* main call back */
void SOF_MainCbk(void)
{
    /*** !!! Here you can place your own code !!! ***/
    /* for example */
    /*
        SOF_SetTargetUser(SOF_CONST_DCHCUR, 200); // const_dch_cur = 20A
        SOF_SetTargetUser(SOF_CONST_FEEDBACKCUR, 100); // const_feedback_cur = 10A
        SOF_ModifyUser(SOF_CONST_DCHCUR, 80); // const_dch_cur = 80% * const_dch_cur
        SOF_ModifyUser(SOF_CONST_FEEDBACKCUR, 50); // const_feedback_cur = 50% * const_feedback_cur
    */
    /* end example */
    
    
     
    /*** !!! end of your own code !!! ***/
    
    SOF_ModuleCbk();
}
