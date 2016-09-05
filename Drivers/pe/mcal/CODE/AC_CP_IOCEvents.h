/** ###################################################################
**     Filename  : AC_CP_IOCEvents.h
**     Project   : mcal
**     Processor : MC9S12XEP100MAG
**     Component : Events
**     Version   : Driver 01.04
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2013/10/12, 14:10
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         AC_CP_IOC_OnCapture - void AC_CP_IOC_OnCapture(void);
**
** ###################################################################*/

#ifndef __AC_CP_IOCEvents_H
#define __AC_CP_IOCEvents_H
/* MODULE AC_CP_IOCEvents */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "wdi.h"
#include "Timer.h"
#include "CAN0.h"
#include "CAN1.h"
#include "CAN4.h"
#include "RELAY_HEAT.h"
#include "ISO_CTRL_POS.h"
#include "ISO_CTRL_NEG.h"
#include "CPUDI1.h"
#include "CPU_CS1.h"
#include "CPU_SCK.h"
#include "CPU_MOSI.h"
#include "CPU_MISO1.h"
#include "CPU_CS2.h"
#include "CPU_SUMV_SDA.h"
#include "CPU_SUMV_SCL.h"
#include "CPU_SUMV_RDY.h"
#include "SUMV_POW.h"
#include "EN_POW2.h"
#include "BAL_SDA2.h"
#include "EN_POW1.h"
#include "BAL_SDA1.h"
#include "ExternFlash_Rst.h"
#include "ExternFlash_Cs.h"
#include "ExternFlash_Sck.h"
#include "ExternFlash_Si.h"
#include "ExternFlash_So.h"
#include "ExternTimer_Int.h"
#include "ExternTimer_Scl.h"
#include "ExternTimer_Sda.h"
#include "PORTA0.h"
#include "PORTA1.h"
#include "PORTA2.h"
#include "CPU_MISO2.h"
#include "RELAY_POS.h"
#include "RELAY_NEG.h"
#include "RELAY_PRE.h"
#include "RELAY_FAN.h"
#include "AI1.h"
#include "CHG_CAN_POW.h"
#include "CPUCAN_CAR_EN.h"
#include "CPUCAN_INT_EN.h"
#include "CURPOWER.h"
#include "CPUCINT.h"
#include "CPUCSO.h"
#include "CPUCSI.h"
#include "CPUCSCK.h"
#include "CPUCCS.h"
#include "ExtEE_Sck.h"
#include "ExtEE_Sda.h"
#include "ExtEE_Wp.h"
#include "CPUEE.h"
#include "EN_POW3.h"
#include "EN_POW4.h"
#include "EN_CELL.h"
#include "DRDY_CELL.h"
#include "SPI2IF.h"
#include "IntWatchDog.h"
#include "CPUDI2.h"
#include "AC_CP_IOC.h"
#include "CPU_CHG_S.h"
#include "DO_CON.h"
#include "RELAY_PRE.h"
#include "RELAY_NEG.h"
#include "RELAY_POS.h"

#pragma CODE_SEG DEFAULT

void AC_CP_IOC_OnCapture(void);
/*
** ===================================================================
**     Event       :  AC_CP_IOC_OnCapture (module AC_CP_IOCEvents)
**
**     Component   :  AC_CP_IOC [Capture]
**     Description :
**         This event is called on capturing of Timer/Counter actual
**         value (only when the component is enabled - <Enable> and the
**         events are enabled - <EnableEvent>.This event is available
**         only if a <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/* END AC_CP_IOCEvents */
#endif /* __AC_CP_IOCEvents_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.04 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
