/* ###################################################################
**     Filename    : Events.h
**     Project     : SJB_APP
**     Processor   : MC9S12ZVC64MKH
**     Component   : Events
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2019-06-18, 14:37, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Timer_1ms.h"
#include "CANComm.h"
#include "CANPHY0.h"
#include "LED_ORG.h"
#include "LED_YEL.h"
#include "LED_GR.h"
#include "LED_RED.h"

#pragma CODE_SEG DEFAULT


void Timer_1ms_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  Timer_1ms_OnInterrupt (module Events)
**
**     Component   :  Timer_1ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CANComm_OnFreeTxBuffer(word BufferMask);
/*
** ===================================================================
**     Event       :  CANComm_OnFreeTxBuffer (module Events)
**
**     Component   :  CANComm [FreescaleCAN]
**     Description :
**         This event is called after a successful transmission of a
**         message. The event is available only if Interrupt
**         service/event is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferMask      - Transmit buffer mask. The
**                           mask can be used to check what message
**                           buffer caused the transmit interrupt.
**     Returns     : Nothing
** ===================================================================
*/

void CANComm_OnFullRxBuffer(void);
/*
** ===================================================================
**     Event       :  CANComm_OnFullRxBuffer (module Events)
**
**     Component   :  CANComm [FreescaleCAN]
**     Description :
**         This event is called when the receive buffer is full after a
**         successful reception of a message. The event is available
**         only if Interrupt service/event is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CANComm_OnBusOff(void);
/*
** ===================================================================
**     Event       :  CANComm_OnBusOff (module Events)
**
**     Component   :  CANComm [FreescaleCAN]
**     Description :
**         This event is called when the node status becomes bus-off.
**         The event is available only if Interrupt service/event is
**         enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS12Z series of microcontrollers.
**
** ###################################################################
*/
