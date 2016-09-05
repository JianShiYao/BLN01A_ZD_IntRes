// EcuConf.c
#include "EcuConf.h"

uByte Ecu_GetEcuSA(void)
{
// ecu is bcu
#if ((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D))
    return 0;
#endif

// ecu is  bmu or bmu_r
#if ((ECU_CATEGORY == M_BMU) || (ECU_CATEGORY == M_BMU_R))
#ifdef CURRENT_BMU_NO
    return CURRENT_BMU_NO;
#else
    // Need Sa from EE
#endif
#endif

}

unsigned char gby_AssertErrorCnt = 0;

/* Version Get Interface */
const sVersion_CodeType EcuConf_VerDef =
{
  MODULE_ECUCONF_NAME,
  ECUCONF_SW_MAJOR_VERSION,
  ECUCONF_SW_MINOR_VERSION,
  ECUCONF_SW_REVISION_VERSION,
  0,
  0,
  ECUCONF_DEVELOP_STATUS
};

ModuleID_Type EcuConf_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{
  if(VerPtr == NULL)
  {
    return NULL_MODULE_ID;
  }
  *VerPtr = EcuConf_VerDef;
  return MODULE_ECUCONF_ID;   
}
