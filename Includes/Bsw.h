// Bsw.h

#include "Version_Type.h"

/*
 * Module Version Define 
 */
#define MODULE_BSW_ID               8 
#define MODULE_BSW_NAME             "BSW"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define BSW_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define BSW_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define BSW_SW_REVISION_VERSION      1   //  size is uWord,max number is 65535                                               
#define BSW_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  
/* Version Module Get Interface */
ModuleID_Type Bsw_GetVesionModuleVer(sVersion_CodeType * VerPtr);        
