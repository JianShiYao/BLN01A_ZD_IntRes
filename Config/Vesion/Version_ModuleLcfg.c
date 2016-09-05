// Version_ModuleLcfg.c
#include "Version_ModuleLcfg.h"

// include module head file here
#include "Sch_Include.h"
#include "Bsw.h"
#include "Cdd.h"
#include "DataAnalysis.h"
#include "BalM.h"
#include "AppDo.h"
//#include "SensorAi.h"
#include "SensorDi.h"
#include "RunModem.h"
//#include "IntRes.h"
#if (ECU_CATEGORY == M_BMU)
#include "BmuMcal_Version.h"
#endif
#if (ECU_CATEGORY == M_BCU_D)
#include "BcudMcal_Version.h"
#endif
#if ( (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BMU_R))
#include "GbChg_IfDet.h"
#endif
#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )

#include "ThM.h"
#endif


// need add module get version interface
const sVersion_GetModuleVerOperationType GetModuleVerOperation[VERSION_MODULE_NUMBER] =
{
  /* 0 Not Define */NULL,
  /* 1 */Version_GetVesionModuleVer,
  /* 2 */NULL,// For EV03, keep NULL
  /* 3 */
         #if (ECU_CATEGORY == M_BMU) 
         Version_GetVesionBmuMcalModuleVer,
         #else
         NULL,
         #endif
  /* 4 */
         #if (ECU_CATEGORY == M_BMU_R) 
         
         #else
         NULL,
         #endif
  /* 5 */ 
        #if (ECU_CATEGORY == M_BCU_C) 
         
         #else
         NULL,
         #endif
  /* 6 */
         #if (ECU_CATEGORY == M_BCU_D) 
         Version_GetVesionBcudMcalModuleVer,
         #else
         NULL,
         #endif
  /* 7 */Sch_GetVesionModuleVer,
  /* 8 */Bsw_GetVesionModuleVer,
  /* 9 */Cdd_GetVesionModuleVer,
  
  /* 10 */DataLayer_GetVesionModuleVer,    
  /* 11 */DataAnalysis_GetVesionModuleVer,    
  /* 12 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))
          NULL,
          #else
          NULL,
          #endif 
  /* 13 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )
          NULL,
          #else
          NULL,
          #endif
  /* 14 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )
          Sof_GetVesionModuleVer,
          #else
          NULL,
          #endif
  /* 15 */NULL,//IntRes_GetVesionModuleVer,
  /* 16 */IntCan_GetVesionModuleVer,
  /* 17 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )
          CarCan_GetVesionModuleVer,
          #else
          NULL,
          #endif
  /* 18 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )
          ChgCan_GetVesionModuleVer,
          #else
          NULL,
          #endif
  /* 19 */
//          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )
          Thm_GetVesionModuleVer,
//          #else
 //         NULL,
//          #endif
  
  /* 20 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))
          ChgM_GetVesionModuleVer,
          #else
          NULL,
          #endif    
  /* 21 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )
          HvM_GetVesionModuleVer,
          #else
          NULL,
          #endif    
  /* 22 *///LvM_GetVesionModuleVer,
  /* 23 */BalM_GetVesionModuleVer,
  /* 24 */NULL,
  /* 25 */RunModem_GetVesionModuleVer,
  /* 26 */AppRelay_GetVesionModuleVer,
  /* 27 *///AppDo_GetVesionModuleVer,
  /* 28 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))
          GbChgDet_GetVesionModuleVer,
          #else
          NULL,
          #endif
  /* 29 *///SupplyPowDet_GetVesionModuleVer,
  
  /* 30 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))
          SumvDet_GetVesionModuleVer,
          #else
          NULL,
          #endif    
  /* 31 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R))
          CurDet_GetVesionModuleVer,
          #else
          NULL,
          #endif    
  /* 32 */
          #if((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU) || (ECU_CATEGORY == M_BMU_R))
          TemperDet_GetVesionModuleVer,
          #else
          NULL,
          #endif
  /* 33 */
          #if((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU) || (ECU_CATEGORY == M_BMU_R))
          CellvDet_GetVesionModuleVer,
          #else
          NULL,
          #endif
  /* 34 */
          #if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) )
          IsoDet_GetVesionModuleVer,
          #else
          NULL,
          #endif 
  /* 35 *///SensorAi_GetVesionModuleVer,           
  /* 36 */SensorDi_GetVesionModuleVer,
  /* 37 */SysConf_GetVesionModuleVer,
  /* 38 */EcuConf_GetVesionModuleVer,   
};