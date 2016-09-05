//CurrentIf_Type.h
#ifndef CURRENT_TYPE_H
#define CURRENT_TYPE_H

#include "GeneralTypeDef.h"

// Add define below

/*typedef enum
{
  ERR_OK = 0,
  ERR_CRC_SUMI,             //CRC error 
  ERR_WR_SUMI,             //write error
  ERR_BUSY_SUMI,            //busy
  ERR_CFG_SUMI,             //configuration register error
}eCurrent_ReturnType;

typedef struct
{
    unsigned char DeviceType;   
    unsigned char DrvSwVesion;  // device software driver seri numeber
}sDeviceInfo;    */

/*#define MAX_CURRENT_IC_MODULE_NUM   1
#define GET_DEVICE_HANDLE(id) (&(Current_DeviceOperation[id]))



typedef struct
{
 uByte (* WrBytePtr)(uByte Wr_Data);
 uByte (* RdBytePtr)(uByte * Rd_DataPtr);
}sCurrent_RdWrOperationType;  





typedef struct
{
 const void (* CCsPutValPtr)(bool val);
 const void (* CSckPutValPtr)(bool val); 
 const bool (* CSoGetValPtr)(void);
 const void (* CSiPutValPtr)(bool val);
 const bool (* CIntGetValPtr)(void);
 const void (* CPowPutValPtr)(bool val);
}sCurrent_DeviceOperationType;

typedef enum
{
  SUMI_CS5460A_1,
  
}eCurrentIf_DeviceIdType;
*/


#endif