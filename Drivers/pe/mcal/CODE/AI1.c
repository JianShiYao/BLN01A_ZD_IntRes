/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : AI1.c
**     Project   : mcal
**     Processor : MC9S12XEP100MAG
**     Component : ADC
**     Version   : Component 01.630, Driver 01.19, CPU db: 3.00.036
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2016/6/6, 18:52
**     Abstract  :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings  :
**          Component name                                 : AI1
**          A/D converter                                  : ADC0
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Disabled
**          A/D channels                                   : 15
**            Channel0                                     : 
**              A/D channel (pin)                          : PAD05_AN05
**              A/D channel (pin) signal                   : 
**            Channel1                                     : 
**              A/D channel (pin)                          : PAD12_AN12
**              A/D channel (pin) signal                   : 
**            Channel2                                     : 
**              A/D channel (pin)                          : PAD15_AN15
**              A/D channel (pin) signal                   : 
**            Channel3                                     : 
**              A/D channel (pin)                          : PAD07_AN07
**              A/D channel (pin) signal                   : 
**            Channel4                                     : 
**              A/D channel (pin)                          : PAD14_AN14
**              A/D channel (pin) signal                   : 
**            Channel5                                     : 
**              A/D channel (pin)                          : PAD06_AN06
**              A/D channel (pin) signal                   : 
**            Channel6                                     : 
**              A/D channel (pin)                          : PAD11_AN11
**              A/D channel (pin) signal                   : 
**            Channel7                                     : 
**              A/D channel (pin)                          : PAD03_AN03
**              A/D channel (pin) signal                   : 
**            Channel8                                     : 
**              A/D channel (pin)                          : PAD10_AN10
**              A/D channel (pin) signal                   : 
**            Channel9                                     : 
**              A/D channel (pin)                          : PAD02_AN02
**              A/D channel (pin) signal                   : 
**            Channel10                                    : 
**              A/D channel (pin)                          : PAD09_AN09
**              A/D channel (pin) signal                   : 
**            Channel11                                    : 
**              A/D channel (pin)                          : PAD01_AN01
**              A/D channel (pin) signal                   : 
**            Channel12                                    : 
**              A/D channel (pin)                          : PAD08_AN08
**              A/D channel (pin) signal                   : 
**            Channel13                                    : 
**              A/D channel (pin)                          : PAD13_AN13
**              A/D channel (pin) signal                   : 
**            Channel14                                    : 
**              A/D channel (pin)                          : PAD00_AN00
**              A/D channel (pin) signal                   : 
**          A/D resolution                                 : 12 bits
**          Conversion time                                : 5.333 �s
**          Sample time                                    : 24 clock periods
**          Discharge before sampling                      : Disabled
**          Result mode                                    : Right justified
**          Autoscan mode                                  : Disabled
**          AD conversions in STOP mode                    : Disabled
**          External trigger                               : Disabled
**          Internal trigger                               : Disabled
**          Number of conversions                          : 4
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          High input limit                               : 1
**          Low input limit                                : 0
**          Get value directly                             : yes
**          Wait for result                                : yes
**     Contents  :
**         Enable          - byte AI1_Enable(void);
**         Disable         - byte AI1_Disable(void);
**         MeasureChanWait - byte AI1_MeasureChanWait(byte Channel);
**         GetChanValue    - byte AI1_GetChanValue(byte Channel, void* Value);
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/


/* MODULE AI1. */

#pragma MESSAGE DISABLE C5703          /* Disable warning C5703 "Parameter is not referenced" */
#pragma MESSAGE DISABLE C4002          /* Disable warning C4002 "Result not used is ignored" */
#pragma MESSAGE DISABLE C12056         /* Disable warning C12056 "SP debug info incorrect because of optimization or inline assembler" */

#include "AI1.h"

#pragma DATA_SEG AI1_DATA              /* Select data segment "AI1_DATA" */
#pragma CODE_SEG AI1_CODE
#pragma CONST_SEG AI1_CONST            /* Constant section for this module */

#define STOP            0U             /* STOP state           */
#define MEASURE         1U             /* MESURE state         */
#define CONTINUOUS      2U             /* CONTINUOUS state      */
#define SINGLE          3U             /* SINGLE state         */

static const word Table[] = {          /* Table of mask constants */
0x01U,0x02U,0x04U,0x08U,0x10U,0x20U,0x40U,0x80U,0x0100U,0x0200U,0x0400U,0x0800U,0x1000U,0x2000U,0x4000U};
static const byte Channels[] = {       /* Contents for the device control register */
0x05U,0x0CU,0x0FU,0x07U,0x0EU,0x06U,0x0BU,0x03U,0x0AU,0x02U,0x09U,0x01U,0x08U,0x0DU,0x00U};
static bool EnUser;                    /* Enable/Disable device */
static word OutFlg;                    /* Measurement finish flag */
static byte SumChan;                   /* Number of measured channels */
volatile static byte ModeFlg;          /* Current state of device */
static byte SumCnt;                    /* Counter of conversions */
static word AI1_OutV[15];              /* Array of measured values */
/*
** ===================================================================
**     Method      :  HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (EnUser) {                        /* Enable device? */
    if (ModeFlg) {                     /* Start or stop measurement? */
      OutFlg &= (word)(~(word)Table[SumChan]); /* Output value isn't available */
      AI1_OutV[SumChan] = 0U;          /* Set variable for storing measured values to 0 */
      for (SumCnt = 0U; SumCnt < 4U; SumCnt++) {
        ATD0CTL5 = Channels[SumChan];  /* Start measurement of next channel */
        while (ATD0STAT0_SCF == 0U) {} /* Wait for AD conversion complete */
        AI1_OutV[SumChan] += ATD0DR0;  /* Save measured value */
      }
      OutFlg |= Table[SumChan];        /* Value of measured channel is available */
      ModeFlg = STOP;                  /* Set the device to the stop mode */
    }
    else {
      /* ATD0CTL3: DJM=1,S8C=0,S4C=0,S2C=0,S1C=1,FIFO=0,FRZ1=0,FRZ0=0 */
      ATD0CTL3 = 0x88U;                /* Abort current measurement */
    }
  }
}

/*
** ===================================================================
**     Method      :  AI1_Enable (component ADC)
**
**     Description :
**         Enables A/D converter component. <Events> may be generated
**         (<DisableEvent>/<EnableEvent>). If possible, this method
**         switches on A/D converter device, voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AI1_Enable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    return ERR_OK;                     /* If yes then set the flag "device enabled" */
  }
  EnUser = TRUE;                       /* Set the flag "device enabled" */
  HWEnDi();                            /* Enable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AI1_Disable (component ADC)
**
**     Description :
**         Disables A/D converter component. No <events> will be generated.
**         If possible, this method switches off A/D converter device,
**         voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AI1_Disable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_OK;                     /* If yes then OK */
  }
  EnUser = FALSE;                      /* If yes then set the flag "device disabled" */
  HWEnDi();                            /* Disable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AI1_MeasureChanWait (component ADC)
**
**     Description :
**         This method performs one measurement on one channel and
**         waits till the end of the measurement. (Note: If the <number
**         of conversions> is more than one the conversion of A/D
**         channels is performed specified number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored, because the parameter
**                           is set inside this method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
**                           ERR_RANGE - Parameter "Channel" out of range
** ===================================================================
*/
byte AI1_MeasureChanWait(byte Channel)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  if (Channel >= 15U) {                /* Is channel number greater than or equal to 15 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = SINGLE;                    /* Set state of device to the measure mode */
  SumChan = Channel;                   /* Set required channel */
  HWEnDi();                            /* Start measurement */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AI1_GetChanValue (component ADC)
**
**     Description :
**         Returns the last measured value of the required channel.
**         Format and width of the value is a native format of the A/D
**         converter.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**       * Value           - Pointer to the measured value. Data
**                           type is a byte, a word or an int. It
**                           depends on the supported modes, resolution,
**                           etc. of the AD converter. See the Version
**                           specific information for the current CPU in
**                           <General Info>.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/
byte AI1_GetChanValue(byte Channel,void* Value)
{
  if (Channel >= 15U) {                /* Is channel number greater than or equal to 15 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if ((OutFlg & Table[Channel]) == 0U) { /* Is measured value(s) available? */
    return ERR_NOTAVAIL;
  }
  *((word*)Value)= AI1_OutV[Channel] / 4U; /* Save measured values to the output buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AI1_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AI1_Init(void)
{
  EnUser = TRUE;                       /* Enable device */
  OutFlg = 0U;                         /* No measured value */
  ModeFlg = STOP;                      /* Device isn't running */
  /* ATD0CTL4: SMP2=1,SMP1=1,SMP0=1,PRS4=0,PRS3=0,PRS2=1,PRS1=1,PRS0=1 */
  ATD0CTL4 = 0xE7U;                    /* Set sample time and prescaler */
  /* ATD0CTL3: DJM=1,S8C=0,S4C=0,S2C=0,S1C=1,FIFO=0,FRZ1=0,FRZ0=0 */
  ATD0CTL3 = 0x88U;                    /* Set ATD control register 3 */
  /* ATD0CTL0: ??=0,??=0,??=0,??=0,WRAP3=1,WRAP2=1,WRAP1=1,WRAP0=1 */
  ATD0CTL0 = 0x0FU;                    /* Set wrap around */
  /* ATD0CTL1: ETRIGSEL=0,SRES1=1,SRES0=0,SMP_DIS=0,ETRIGCH3=1,ETRIGCH2=1,ETRIGCH1=1,ETRIGCH0=1 */
  ATD0CTL1 = 0x4FU;                    /* Set resolution and discharge */
  /* ATD0CTL2: ??=0,AFFC=1,ICLKSTP=0,ETRIGLE=0,ETRIGP=0,ETRIGE=0,ASCIE=0,ACMPIE=0 */
  ATD0CTL2 = 0x40U;                    /* Set ATD control register 2 */
}

/* END AI1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.05 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
