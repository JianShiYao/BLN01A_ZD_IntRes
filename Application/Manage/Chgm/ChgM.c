// ChgM.c

#include "ChgM.h"

#ifdef USE_CHGM_B
#include"ChgM-B.h"
#include"GbChgM-B.h"
#endif

/* table for charge manage */
const sChg_CurTableType  DcChg_TemperCurTable[T_SEC] =
{
    {40,  0}, {55,  20}, {60, 50}, {85, 50},    /* Temper: unit: 1'C, Offset -40; Current: unit: 0.01C */
    {90, 50}, {100, 20}, {110, 0}, {250, 0}
};

const sChg_CurTableType AcChg_TemperCurTable[T_SEC] =
{
    {40,  0}, {55,  100}, {60, 100}, {85, 100},  /* Temper: unit: 1'C, Offset -40; Current: unit: 0.1A */
    {90, 100}, {100, 0}, {110, 0}, {250, 0}
};



/* Version Get Interface of Version Module  */
ModuleID_Type ChgM_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
    ModuleID_Type module_id;

#ifdef USE_CHGM_B
    module_id = ChgM_B_GetVesionModuleVer(VerPtr);
#endif

    return module_id;
}

/* Module initial */
void ChgM_Init(void)
{
    /* ChgM module initial */
    ChgM_ModuleInit();
}

/* Module count call back */
void ChgM_MainCountCbk(void)
{
    /* Count every 5ms */
    ChgM_ModuleCountCbk();

}

/* Main call back */
void ChgM_MainCbk(void)
{
    ChgM_ModuleCbk();
}
