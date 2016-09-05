// ThM.c
#include "ThM.h"

#ifdef USE_THM_A
#include"ThM-A.h"
#endif

#ifdef USE_THM_AB
#include"ThM-AB.h"
#endif

/* Version Get Interface of Version Module  */
ModuleID_Type Thm_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{      
    ModuleID_Type module_id;
    
#ifdef USE_THM_A
    module_id = ThM_A_GetVesionModuleVer(VerPtr);
#endif
    
#ifdef USE_THM_AB
    module_id = ThM_AB_GetVesionModuleVer(VerPtr);
#endif

    return module_id;   
}

/* module initial */
void ThM_Init(void)
{
    ThM_ModuleInit();
}

/* module count call back */
void ThM_MainCountCbk(void)
{
  //  ThM_ModuleCountCbk();
}

/* main call back */
void ThM_MainCbk(void)
{
  //  ThM_ModuleCbk();
}

