// SensorDi.h
#ifndef SENSOR_H
#define SENSOR_H

#include "GeneralTypeDef.h"
#include "Ecu.h"
#include "Version_Type.h" 


/*
 * Module Version Define 
 */
#define MODULE_SENSORDI_ID               36 
#define MODULE_SENSORDI_NAME             "DI"    //  platform name include "EV02" "EV03" "EV04" "EV05"                                      
#define SENSORDI_SW_MAJOR_VERSION         1     //  size is uByte,max number is 255                                            
#define SENSORDI_SW_MINOR_VERSION         1    //  size is uWord,max number is 65535                                           
#define SENSORDI_SW_REVISION_VERSION      0   //  size is uWord,max number is 65535                                               
#define SENSORDI_DEVELOP_STATUS           "" /* status include "beta" "rc" ""                                 
                                               *  "beta" ---- beta
                                               *  "rc"   ---- Release Candidate
                                               *  ""  or the blank or '\0' represent Release,display blank in monitor
                                               */  
                                         

typedef enum
{
  DI_STATUS_LOW,
  DI_STATUS_HIGH,
  DI_STATUS_ERROR
}eSensor_DiStatusType;

#define CPU_DI1_ID 0
#define CPU_DI2_ID 1


/* Version Module Get Interface */
ModuleID_Type SensorDi_GetVesionModuleVer(sVersion_CodeType * VerPtr);
extern eSensor_DiStatusType Sensor_GetDiSt(uByte di_id);//,eSensor_DiStatusType *StPtr);

#endif