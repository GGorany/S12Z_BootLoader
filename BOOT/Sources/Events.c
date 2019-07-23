/* ###################################################################
**     Filename    : Events.c
**     Project     : SJB_BOOT
**     Processor   : MC9S12ZVC64MKH
**     Component   : Events
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2019-06-19, 16:13, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "CAN.h"


#pragma CODE_SEG DEFAULT

extern bool Tick_1ms;


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
void CANComm_OnFreeTxBuffer(word BufferMask)
{
	/* Write your code here ... */
}

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
void CANComm_OnFullRxBuffer(void)
{
	/* Write your code here ... */
	RXMESSAGE();
}

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
void CANComm_OnBusOff(void)
{
	/* Write your code here ... */
}

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
void Timer_1ms_OnInterrupt(void)
{
	/* Write your code here ... */
	Tick_1ms = TRUE;
}

/* END Events */

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
