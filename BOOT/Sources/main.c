/* ###################################################################
**     Filename    : main.c
**     Project     : SJB_BOOT
**     Processor   : MC9S12ZVC64MKH
**     Version     : Driver 01.14
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2019-06-19, 16:13, # CodeGen: 0
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
#include "CANComm.h"
#include "CANPHY0.h"
#include "Timer_1ms.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Config_for_BootLoader.h"
#include "CAN.h"
#include "FLASH_S12Z.h"
#include "EEPROM_S12Z.h"


//#define BL_FCLKDIV           0x0Fu   //Flash Clock Divider for 16MHz bus clock
#define BL_FCLKDIV           0x18u   //Flash Clock Divider for 25MHz bus clock

//Please select Bootloader area which will be protected
//#define BL_FPROT  0xDF       //upper 16kB of P-Flash protected.
//#define BL_FPROT  0xD7       //upper 8kB of P-Flash protected.
//#define BL_FPROT  0xCF       //upper 4kB of P-Flash protected.
#define BL_FPROT  0xFF       //unprotected.
#define BL_DFPROT 0xFF       //EEPROM unprotected.
#define BL_FOPT   0xFF       //COP is not active after reset.

#if 0
const unsigned char flash_array[] @0xFFFE08 = {0xFF, 0xFF, 0xFF, 0xFF,		
                                               BL_FPROT, 	//P-Flash Protection byte
                                               BL_DFPROT, 	//EEPROM Protection byte
                                               BL_FOPT, 	//Flash Nonvolatile byte
                                               0xFE};
#endif
// 1ms Tick
bool Tick_1ms = FALSE;

const unsigned char BootLoader_Version_array[] @BootLoader_version_Address = {'v', 'e', 'r', '-', '1', '.', '0'};


void main(void)
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	FCNFG = 0x0C;                             //WSTAT=0b11 - disable flash wait states
	while (!FPSTAT_WSTATACK){}                //wait until Wait-State switch is complete

	PFLASH_Init(BL_FCLKDIV);                  //internal oscillator 1MHz.

	// CAN PHY Init
	CANPHY0_Init();

	// Enable Components
	(void)CANComm_Enable();
	(void)Timer_1ms_Enable();

    // UDS Init
    Init_UDS();

    while(TRUE)
    {
        if (Tick_1ms == TRUE)
        {
        	Tick_1ms = FALSE;
            TASK_UDS();
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
