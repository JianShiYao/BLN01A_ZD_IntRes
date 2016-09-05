// Sch_Include.h
#ifndef SCH_INCLUDE_H
#define SCH_INCLUDE_H

/*
 * Module Version Define 
 */
#define MODULE_DATALAYER_ID               10 
#define MODULE_DATALAYER_NAME             "DATALAYER"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define DATALAYER_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define DATALAYER_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define DATALAYER_SW_REVISION_VERSION      0   //  size is uWord,max number is 65535                                               
#define DATALAYER_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  

/* Common module for BCU_D, BCU_D, BMU, BMU_R */
#include "SchIf.h"              /* SchIf Module */
#include "SysConf.h"            /* Config --- SysConf Module */
#include "Version.h"            /* Config --- Version Module */
#include "Ecu.h"                /* Bsw --- Ecu Module, Include EcuConf Module */
#include "WdgM.h"               /* Bsw --- Wdgm Module */
//#include "SupplyPowDet.h"       /* Sensors --- SupplyPowDet Module */
#include "AppRelay.h"           /* Actors --- Relay Module */
#include "IntCan.h"             /* Protocols --- IntCan Module, Inlcude Bsw CanIf.h */
#include "BatterySt.h"          /* DataAnalysis --- BatterySt Module */
#include "BmsSysSt.h"           /* DataAnalysis --- BmsSysSt Module */ 
#include "BatterySysst.h"       /* DataAnalysis --- BatterySysst Module */ 
#include "ErrorAlarm.h"         /* DataAnalysis --- ErrorAlarm Module */  
#include "EE.h"                 /* DataAnalysis --- EE module */
#include "Lvm.h"                /* Manage --- Lvm Module */
#include "Thm.h"                /* Manage --- Thm Module */
#include "Balm.h"               /* Manage --- Thm Module */
#include "RunModem.h"           /* Manage --- RunModem Module */
#include "Version.h"

#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R)) 
#include "CurDet.h"             /* Sensors --- CurDet Module */
#include "SumvDet.h"            /* Sensors --- SumvDet Module */
#include "ChargeSt.h"           /* DataAnalysis --- ChargeSt Module */
#include "Chgm.h"               /* Manage --- Chgm Module */
#include "SOC.h"                /* Soc --- Soc Module */
#endif

#if((ECU_CATEGORY == M_BCU_D) || (ECU_CATEGORY == M_BCU_C))
#include "IsoDet.h"             /* Sensors --- IsoDet Module */
#include "ClockIf.h"            /* CDD --- ClockIf Module, special include !!!! */
#include "CarCan.h"             /* Protocols --- CarCan Module, Inlcude Bsw CanIf.h */
#include "ChgCan.h"             /* Protocols --- ChgCan Module, Inlcude Bsw CanIf.h */
#include "DataStore.h"          /* DataAnalysis --- DataStore module */
#include "Hvm.h"                /* Manage --- Hvm Module */
#include "SOH.h"                /* SOH --- SOH Module */
#include "SOF.h"                /* SOF --- SOF Module */
//#include "IntRes.h"             /* IntRes --- IntRes Module */
#include "IocIf.h"
#include "Project.h"
#endif

#include "GbChg_IfDet.h"

#if((ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BMU_R) || (ECU_CATEGORY == M_BMU))
#include "CellvDet.h"           /* Sensors --- CellvDet Module */
#include "TemperDet.h"          /* Sensors --- TemperDet Module */
#endif

/* Version Module Get Interface */
ModuleID_Type DataLayer_GetVesionModuleVer(sVersion_CodeType * VerPtr); 

#endif /* SCH_INCLUDE_H  */