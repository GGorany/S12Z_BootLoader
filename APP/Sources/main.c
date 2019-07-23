/* ###################################################################
**     Filename    : main.c
**     Project     : SJB_APP
**     Processor   : MC9S12ZVC64MKH
**     Version     : Driver 01.14
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2019-06-18, 14:37, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.14
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Timer_1ms.h"
#include "CANComm.h"
#include "CANPHY0.h"
#include "LED_ORG.h"
#include "LED_YEL.h"
#include "LED_GR.h"
#include "LED_RED.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "CAN.h"
#include "LED.h"
#include "EEPROM_S12Z.h"
#include "Config_for_BootLoader.h"

#define BL_FCLKDIV           0x0Fu   //Flash Clock Divider for 16MHz bus clock
//#define BL_FCLKDIV           0x18u   //Flash Clock Divider for 25MHz bus clock

// 1ms Tick
bool Tick_1ms = FALSE;

// Application Version Information in Flash
const unsigned char Application_Version_array[] @Application_version_Address = {'v', 'e', 'r', '-', '1', '.', '9'};


void main(void)
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	/* For example: for(;;) { } */

    FCNFG = 0x0C;                             //WSTAT=0b11 - disable flash wait states
	while (!FPSTAT_WSTATACK){}                //wait until Wait-State switch is complete

	EEPROM_Init(BL_FCLKDIV);                  //internal oscillator 1MHz.

	// CAN PHY Init
	CANPHY0_Init();

	// Enable Components
	(void)CANComm_Enable();
	(void)Timer_1ms_Enable();

	while(TRUE)
    {
        if (Tick_1ms == TRUE)
        {
        	Tick_1ms = FALSE;
        	Task_CAN();
        	Task_LED();
        }
    }

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
