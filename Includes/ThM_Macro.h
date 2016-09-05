// ThM.h
#ifndef THM_MACRO_H
#define THM_MACRO_H

#include "GeneralTypeDef.h"
#include "Ecu.h"

// select solution 
#define USE_THM_AB

/* sub function enable macro */
#define THM_FUN_ENABLE      1
#define THM_FUN_DISABLE     0

// select function

#if (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D)
#define THM_BCU_CTRL_BCU    THM_FUN_ENABLE
#else
#define THM_BCU_CTRL_BCU    THM_FUN_DISABLE
#endif

#define THM_BCU_CTRL_BMU    THM_FUN_DISABLE


#if (ECU_CATEGORY == M_BCU_C) || (ECU_CATEGORY == M_BCU_D)
#define FAN_RELAY_ID  CPU_FAN_ID
#define HEAT_RELAY_ID  CPU_HEAT_ID
#endif

#if (ECU_CATEGORY == M_BMU) || (ECU_CATEGORY == M_BMU_R)
#define FAN_RELAY_ID  CPU_FAN_ID
#define HEAT_RELAY_ID  CPU_HEAT_ID
#endif


#define FAN_ON_MIN_T  55

#define FAN_HIGH_SPEED  1000
#define FAN_LOW_SPEED   500

#define THM_CNT_5S      10


#endif /* THM_H */