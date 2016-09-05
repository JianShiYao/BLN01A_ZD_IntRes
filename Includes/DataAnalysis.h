// DATAANALYSIS.h
#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include "Version_Type.h" 

/*
 * Module Version Define 
 */
#define MODULE_DATAANALYSIS_ID               11 
#define MODULE_DATAANALYSIS_NAME             "DATAANALYSIS"   //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define DATAANALYSIS_SW_MAJOR_VERSION        1      //  size is uByte,max number is 255                                            
#define DATAANALYSIS_SW_MINOR_VERSION        1      //  size is uWord,max number is 65535                                           
#define DATAANALYSIS_SW_REVISION_VERSION     0      //  size is uWord,max number is 65535                                               
#define DATAANALYSIS_DEVELOP_STATUS          "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */
extern ModuleID_Type DataAnalysis_GetVesionModuleVer(sVersion_CodeType * VerPtr);                                               
#endif                                               