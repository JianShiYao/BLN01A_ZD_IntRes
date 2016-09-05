// SchIf.c

#include "Timer.h"
#include "SchIf.h"

void Sch_Init(void)
{
   Timer_EnableEvent();
   (void)Timer_Enable();
   __EI();
}


/* Version Get Interface */
const sVersion_CodeType Sch_VerDef =
{
  MODULE_SCH_NAME,
  SCH_SW_MAJOR_VERSION,
  SCH_SW_MINOR_VERSION,
  SCH_SW_REVISION_VERSION,
  0,
  0,
  SCH_DEVELOP_STATUS
};

ModuleID_Type Sch_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
  *VerPtr = Sch_VerDef;
  return MODULE_SCH_ID;   
}