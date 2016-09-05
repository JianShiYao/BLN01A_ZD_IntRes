/** ###################################################################
**     Filename  : Events.h
**     Project   : mcal
**     Processor : MC9S12XEP100MAG
**     Component : Events
**     Version   : Driver 01.04
**     Compiler  : CodeWarrior HCS12X C Compiler
**     Date/Time : 2013-9-18, 17:20
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         EE_IIC_OnRxChar       - void EE_IIC_OnRxChar(void);
**         EE_IIC_OnTxChar       - void EE_IIC_OnTxChar(void);
**         EE_IIC_OnNACK         - void EE_IIC_OnNACK(void);
**         TIMER_IIC_OnRxChar    - void TIMER_IIC_OnRxChar(void);
**         TIMER_IIC_OnTxChar    - void TIMER_IIC_OnTxChar(void);
**         TIMER_IIC_OnNACK      - void TIMER_IIC_OnNACK(void);
**         SUMV_EXT_IIC_OnRxChar - void SUMV_EXT_IIC_OnRxChar(void);
**         SUMV_EXT_IIC_OnTxChar - void SUMV_EXT_IIC_OnTxChar(void);
**         SUMV_EXT_IIC_OnNACK   - void SUMV_EXT_IIC_OnNACK(void);
**         SUMV_IIC_OnRxChar     - void SUMV_IIC_OnRxChar(void);
**         SUMV_IIC_OnTxChar     - void SUMV_IIC_OnTxChar(void);
**         SUMV_IIC_OnNACK       - void SUMV_IIC_OnNACK(void);
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

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
#include "RELAY_PRE.h"
#include "RELAY_NEG.h"
#include "RELAY_POS.h"
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

#pragma CODE_SEG DEFAULT

void EE_IIC_OnRxChar(void);
/*
** ===================================================================
**     Event       :  EE_IIC_OnRxChar (module Events)
**
**     Component   :  EE_IIC [SW_I2C]
**     Description :
**         Called when a correct character is received. In the SLAVE
**         mode, this event is not called if the component receives the
**         first byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void EE_IIC_OnTxChar(void);
/*
** ===================================================================
**     Event       :  EE_IIC_OnTxChar (module Events)
**
**     Component   :  EE_IIC [SW_I2C]
**     Description :
**         Called when a correct character is sent. In MASTER mode,
**         this event is not called if the component sends the first
**         byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void EE_IIC_OnNACK(void);
/*
** ===================================================================
**     Event       :  EE_IIC_OnNACK (module Events)
**
**     Component   :  EE_IIC [SW_I2C]
**     Description :
**         In the MASTER mode, this event is called when an invalid
**         slaves acknowledgement occurs during communication transfer.
**         If the acknowledge polling is provided (MASTER mode only), i.
**         e., the <Acknowledge polling trials> property value is
**         higher than one, this event is called only when no trial is
**         successful. In the SLAVE mode, this event is called when a
**         master sends an acknowledgement instead of no
**         acknowledgement at the end of the last byte transfer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TIMER_IIC_OnRxChar(void);
/*
** ===================================================================
**     Event       :  TIMER_IIC_OnRxChar (module Events)
**
**     Component   :  TIMER_IIC [SW_I2C]
**     Description :
**         Called when a correct character is received. In the SLAVE
**         mode, this event is not called if the component receives the
**         first byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TIMER_IIC_OnTxChar(void);
/*
** ===================================================================
**     Event       :  TIMER_IIC_OnTxChar (module Events)
**
**     Component   :  TIMER_IIC [SW_I2C]
**     Description :
**         Called when a correct character is sent. In MASTER mode,
**         this event is not called if the component sends the first
**         byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TIMER_IIC_OnNACK(void);
/*
** ===================================================================
**     Event       :  TIMER_IIC_OnNACK (module Events)
**
**     Component   :  TIMER_IIC [SW_I2C]
**     Description :
**         In the MASTER mode, this event is called when an invalid
**         slaves acknowledgement occurs during communication transfer.
**         If the acknowledge polling is provided (MASTER mode only), i.
**         e., the <Acknowledge polling trials> property value is
**         higher than one, this event is called only when no trial is
**         successful. In the SLAVE mode, this event is called when a
**         master sends an acknowledgement instead of no
**         acknowledgement at the end of the last byte transfer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SUMV_EXT_IIC_OnRxChar(void);
/*
** ===================================================================
**     Event       :  SUMV_EXT_IIC_OnRxChar (module Events)
**
**     Component   :  SUMV_EXT_IIC [SW_I2C]
**     Description :
**         Called when a correct character is received. In the SLAVE
**         mode, this event is not called if the component receives the
**         first byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SUMV_EXT_IIC_OnTxChar(void);
/*
** ===================================================================
**     Event       :  SUMV_EXT_IIC_OnTxChar (module Events)
**
**     Component   :  SUMV_EXT_IIC [SW_I2C]
**     Description :
**         Called when a correct character is sent. In MASTER mode,
**         this event is not called if the component sends the first
**         byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SUMV_EXT_IIC_OnNACK(void);
/*
** ===================================================================
**     Event       :  SUMV_EXT_IIC_OnNACK (module Events)
**
**     Component   :  SUMV_EXT_IIC [SW_I2C]
**     Description :
**         In the MASTER mode, this event is called when an invalid
**         slaves acknowledgement occurs during communication transfer.
**         If the acknowledge polling is provided (MASTER mode only), i.
**         e., the <Acknowledge polling trials> property value is
**         higher than one, this event is called only when no trial is
**         successful. In the SLAVE mode, this event is called when a
**         master sends an acknowledgement instead of no
**         acknowledgement at the end of the last byte transfer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SUMV_IIC_OnRxChar(void);
/*
** ===================================================================
**     Event       :  SUMV_IIC_OnRxChar (module Events)
**
**     Component   :  SUMV_IIC [SW_I2C]
**     Description :
**         Called when a correct character is received. In the SLAVE
**         mode, this event is not called if the component receives the
**         first byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SUMV_IIC_OnTxChar(void);
/*
** ===================================================================
**     Event       :  SUMV_IIC_OnTxChar (module Events)
**
**     Component   :  SUMV_IIC [SW_I2C]
**     Description :
**         Called when a correct character is sent. In MASTER mode,
**         this event is not called if the component sends the first
**         byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SUMV_IIC_OnNACK(void);
/*
** ===================================================================
**     Event       :  SUMV_IIC_OnNACK (module Events)
**
**     Component   :  SUMV_IIC [SW_I2C]
**     Description :
**         In the MASTER mode, this event is called when an invalid
**         slaves acknowledgement occurs during communication transfer.
**         If the acknowledge polling is provided (MASTER mode only), i.
**         e., the <Acknowledge polling trials> property value is
**         higher than one, this event is called only when no trial is
**         successful. In the SLAVE mode, this event is called when a
**         master sends an acknowledgement instead of no
**         acknowledgement at the end of the last byte transfer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.04 [04.46]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
