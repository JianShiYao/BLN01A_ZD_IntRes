//Current_Lcfg.h
#ifndef CURRENT_LCFG_H
#define CURRENT_LCFG_H

#include "CurrentIf.h"

typedef struct
{
 const void (* CsPutValPtr)(bool val);
 const void (* SckPutValPtr)(bool val); 
 const bool (* SdoGetValPtr)(void);
 const void (* SdiPutValPtr)(bool val);
 const bool (* IntGetValPtr)(void);
 const void (* PowPutValPtr)(bool val);
}sCurrent_OperationType;

// Add define below
#define MAX_CURRENT_IC_MODULE_NUM   1

extern const sCurrent_OperationType Current_Operation[];

#define GET_DEVICE_HANDLE(id) (&(Current_Operation[id]))

#endif