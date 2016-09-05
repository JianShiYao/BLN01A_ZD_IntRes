#ifndef DOIF_H
#define DOIF_H

#include "GeneralTypeDef.h"
#include "Ecu.h"
#include "IoIf_Type.h"

#include "CPU_CHG_S.h"
#include "DO_CON.h"



#define DOIF_MAX_NUM  2
typedef enum 
{
   DOIF_CON_NO,
   DOIF_CPU_CHG_S_NO,
  
  
}eDoIf_IdNumType; 


typedef enum 
{
   DOIF_CMD_LOW,   /* DO output value low level */
   DOIF_CMD_HIGH   /* DO output value high level */
}eDoIf_CmdType;


GeneralReturnType DoIf_Ctrl(uByte DoIf_Id,bool DoIf_Cmd);


#endif /* DOIF_H */