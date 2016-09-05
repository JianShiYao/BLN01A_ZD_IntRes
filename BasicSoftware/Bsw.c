// Bsw.c
#include "Bsw.h"

/* Version Get Interface */
const sVersion_CodeType Bsw_VerDef =
{
  MODULE_BSW_NAME,
  BSW_SW_MAJOR_VERSION,
  BSW_SW_MINOR_VERSION,
  BSW_SW_REVISION_VERSION,
    0,
    0,
  BSW_DEVELOP_STATUS
};

ModuleID_Type Bsw_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
  *VerPtr = Bsw_VerDef;
  return MODULE_BSW_ID;   
}