/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Timer.h
**     Project   : mcal
**     Processor : MC9S12XEP100MAG
**     Component : TimerInt
**     Version   : Component 02.159, Driver 01.21, CPU db: 3.00.036
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2016/1/9, 9:28
**     Abstract  :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : ModulusCounter (16-bit)
**         Compare name                : ModulusComp
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 12000000 Hz
**           Initial period/frequency
**             Xtal ticks              : 40000
**             microseconds            : 5000
**             milliseconds            : 5
**             seconds (real)          : 0.005
**             Hz                      : 200
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Disabled
**              Events                 : Disabled
**
**         Timer registers
**              Counter                : ECT_MCCNT [$0076]
**              Run                    : ECT_MCCTL [$0066]
**
**         Compare registers
**              Compare                : ECT_OC7D  [$0043]
**
**         Flip-flop registers
**     Contents  :
**         Enable       - byte Timer_Enable(void);
**         Disable      - byte Timer_Disable(void);
**         EnableEvent  - byte Timer_EnableEvent(void);
**         DisableEvent - byte Timer_DisableEvent(void);
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __Timer
#define __Timer

/* MODULE Timer. */

#include "Cpu.h"

#pragma CODE_SEG Timer_CODE
#pragma DATA_SEG Timer_DATA            /* Select data segment "Timer_DATA" */



byte Timer_Enable(void);
/*
** ===================================================================
**     Method      :  Timer_Enable (component TimerInt)
**
**     Description :
**         This method enables the component - it starts the timer.
**         Events may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define Timer_Disable() ( \
  clrReg8Bits(ECT_MCCTL, 0x84),        /* Disable interrupt; Disable counter */ \
  ERR_OK                               /* Return result */ \
)
/*
** ===================================================================
**     Method      :  Timer_Disable (component TimerInt)
**
**     Description :
**         This method disables the component - it stops the timer. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte Timer_EnableEvent(void);
/*
** ===================================================================
**     Method      :  Timer_EnableEvent (component TimerInt)
**
**     Description :
**         This method enables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define Timer_DisableEvent() ( \
  ECT_MCCTL_MCZI = 0U,                 /* Disable channel interrupt */ \
  (byte)ERR_OK                         /* Return result */ \
)
/*
** ===================================================================
**     Method      :  Timer_DisableEvent (component TimerInt)
**
**     Description :
**         This method disables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void Timer_Interrupt(void);
/*
** ===================================================================
**     Method      :  Timer_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */
#pragma CODE_SEG DEFAULT

/* END Timer. */

#endif /* ifndef __Timer */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.05 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
