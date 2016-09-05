#include "DataAnalysis.h"

const sVersion_CodeType DataAnalysis_VerDef =
{
    MODULE_DATAANALYSIS_NAME,
    DATAANALYSIS_SW_MAJOR_VERSION,
    DATAANALYSIS_SW_MINOR_VERSION,
    DATAANALYSIS_SW_REVISION_VERSION,
    0,
    0,
    DATAANALYSIS_DEVELOP_STATUS
};

/* Version Get Interface of Version Module  */
ModuleID_Type DataAnalysis_GetVesionModuleVer(sVersion_CodeType * VerPtr)
{      
    *VerPtr = DataAnalysis_VerDef;
    return MODULE_DATAANALYSIS_ID;   
}