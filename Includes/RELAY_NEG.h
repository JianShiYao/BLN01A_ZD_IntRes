/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : RELAY_NEG.h
**     Project   : mcal
**     Processor : MC9S12XEP100MAG
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.14, CPU db: 3.00.036
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2016/1/9, 9:28
**     Abstract  :
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       3             |  PP1_KWP1_PWM1_MOSI1_TIMIOC1
**             ----------------------------------------------------
**
**         Port name                   : P
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : $0002
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTP       [$0258]
**         Port control register       : DDRP      [$025A]
**
**         Optimization for            : speed
**     Contents  :
**         GetVal - bool RELAY_NEG_GetVal(void);
**         PutVal - void RELAY_NEG_PutVal(bool Val);
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef RELAY_NEG_H_
#define RELAY_NEG_H_

/* MODULE RELAY_NEG. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG RELAY_NEG_CODE
/*
** ===================================================================
**     Method      :  RELAY_NEG_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
#define RELAY_NEG_GetVal() ( \
    (bool)((getReg8(PTP) & 0x02U))     /* Return port data */ \
  )

/*
** ===================================================================
**     Method      :  RELAY_NEG_PutVal (component BitIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void RELAY_NEG_PutVal(bool Val);

#pragma CODE_SEG DEFAULT

/* END RELAY_NEG. */
#endif /* #ifndef __RELAY_NEG_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.05 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
