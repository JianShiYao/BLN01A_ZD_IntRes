/** ###################################################################
**     Filename  : mcal.c
**     Project   : mcal
**     Processor : MC9S12XEP100MAG
**     Version   : Driver 01.14
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2013/9/12, 14:56
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE mcal */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TimerEvents.h"
#include "CAN0Events.h"
#include "CAN1Events.h"
#include "CAN4Events.h"
#include "AC_CP_IOCEvents.h"
#include "wdi.h"
#include "Timer.h"
#include "CAN0.h"
#include "CAN1.h"
#include "CAN4.h"
#include "RELAY_HEAT.h"
#include "ISO_CTRL_POS.h"
#include "ISO_CTRL_NEG.h"
#include "CPUDI1.h"
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
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "PE_cfg.h"
#ifdef PE_CBK_EN
#include "Sch_Cbk.h"
#include "Sch_Main.h"
#endif

void main(void)
{
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  #ifdef PE_CBK_EN
  Sch_MainInit(); 
  #endif 
  
  for(;;){
  #ifdef PE_CBK_EN
   Main_Task();
  #endif
  
  }
  
  

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END mcal */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.04 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
