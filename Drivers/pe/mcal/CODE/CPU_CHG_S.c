/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : CPU_CHG_S.c
**     Project   : mcal
**     Processor : MC9S12XEP100MAG
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.14, CPU db: 3.00.036
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2016/6/6, 15:35
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
**                       5             |  PJ2_KWJ2_CS1
**             ----------------------------------------------------
**
**         Port name                   : J
**
**         Bit number (in port)        : 2
**         Bit mask of the port        : $0004
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTJ       [$0268]
**         Port control register       : DDRJ      [$026A]
**
**         Optimization for            : speed
**     Contents  :
**         GetVal - bool CPU_CHG_S_GetVal(void);
**         PutVal - void CPU_CHG_S_PutVal(bool Val);
**         ClrVal - void CPU_CHG_S_ClrVal(void);
**         SetVal - void CPU_CHG_S_SetVal(void);
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE CPU_CHG_S. */

#include "CPU_CHG_S.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma DATA_SEG CPU_CHG_S_DATA        /* Select data segment "CPU_CHG_S_DATA" */
#pragma CODE_SEG CPU_CHG_S_CODE
#pragma CONST_SEG CPU_CHG_S_CONST      /* Constant section for this module */
/*
** ===================================================================
**     Method      :  CPU_CHG_S_GetVal (component BitIO)
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
/*
bool CPU_CHG_S_GetVal(void)

**  This method is implemented as a macro. See CPU_CHG_S.h file.  **
*/

/*
** ===================================================================
**     Method      :  CPU_CHG_S_PutVal (component BitIO)
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
void CPU_CHG_S_PutVal(bool Val)
{
  if (Val) {
    setReg8Bits(PTJ, 0x04U);           /* PTJ2=0x01U */
  } else { /* !Val */
    clrReg8Bits(PTJ, 0x04U);           /* PTJ2=0x00U */
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  CPU_CHG_S_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void CPU_CHG_S_ClrVal(void)

**  This method is implemented as a macro. See CPU_CHG_S.h file.  **
*/

/*
** ===================================================================
**     Method      :  CPU_CHG_S_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void CPU_CHG_S_SetVal(void)

**  This method is implemented as a macro. See CPU_CHG_S.h file.  **
*/


/* END CPU_CHG_S. */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.05 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
