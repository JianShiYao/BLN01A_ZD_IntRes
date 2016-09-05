/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : BAL_SDA2.h
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
**                       29            |  PC1_DATA9
**             ----------------------------------------------------
**
**         Port name                   : C
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : $0002
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 1
**         Initial pull option         : off
**
**         Port data register          : PORTC     [$0004]
**         Port control register       : DDRC      [$0006]
**
**         Optimization for            : speed
**     Contents  :
**         SetInput  - void BAL_SDA2_SetInput(void);
**         SetOutput - void BAL_SDA2_SetOutput(void);
**         GetVal    - bool BAL_SDA2_GetVal(void);
**         ClrVal    - void BAL_SDA2_ClrVal(void);
**         SetVal    - void BAL_SDA2_SetVal(void);
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef BAL_SDA2_H_
#define BAL_SDA2_H_

/* MODULE BAL_SDA2. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG BAL_SDA2_CODE
/*
** ===================================================================
**     Method      :  BAL_SDA2_GetVal (component BitIO)
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
#define BAL_SDA2_GetVal() ( \
    (bool)((getReg8(PORTC) & 0x02U))   /* Return port data */ \
  )

/*
** ===================================================================
**     Method      :  BAL_SDA2_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define BAL_SDA2_ClrVal() ( \
    (void)clrReg8Bits(PORTC, 0x02U)    /* PC1=0x00U */, \
    (Shadow_C &= 0xFDU)                /* Set appropriate bit in shadow variable */ \
  )

/*
** ===================================================================
**     Method      :  BAL_SDA2_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define BAL_SDA2_SetVal() ( \
    (void)setReg8Bits(PORTC, 0x02U)    /* PC1=0x01U */, \
    (Shadow_C |= 0x02U)                /* Set appropriate bit in shadow variable */ \
  )

/*
** ===================================================================
**     Method      :  BAL_SDA2_SetInput (component BitIO)
**
**     Description :
**         This method sets direction of the component to input.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define BAL_SDA2_SetInput() ( \
    (void)clrReg8Bits(DDRC, 0x02U)     /* DDRC1=0x00U */ \
  )

/*
** ===================================================================
**     Method      :  BAL_SDA2_SetOutput (component BitIO)
**
**     Description :
**         This method sets direction of the component to output.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BAL_SDA2_SetOutput(void);

#pragma CODE_SEG DEFAULT

/* END BAL_SDA2. */
#endif /* #ifndef __BAL_SDA2_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.05 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
