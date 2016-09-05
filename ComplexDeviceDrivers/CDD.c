// CDD.c
#include "CDD.h" 

/* Version Get Interface */
const sVersion_CodeType Cdd_VerDef =
{
  MODULE_CDD_NAME,
  CDD_SW_MAJOR_VERSION,
  CDD_SW_MINOR_VERSION,
  CDD_SW_REVISION_VERSION,
    0,
    0,
  CDD_DEVELOP_STATUS
};

ModuleID_Type Cdd_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
  *VerPtr = Cdd_VerDef;
  return MODULE_CDD_ID;   
}