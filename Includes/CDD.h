// CDD.h
#include "Version_Type.h"

/*
 * Module Version Define 
 */
#define MODULE_CDD_ID               9 
#define MODULE_CDD_NAME             "CDD"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define CDD_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define CDD_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define CDD_SW_REVISION_VERSION      0   //  size is uWord,max number is 65535                                               
#define CDD_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  
/* Version Module Get Interface */
ModuleID_Type Cdd_GetVesionModuleVer(sVersion_CodeType * VerPtr); 