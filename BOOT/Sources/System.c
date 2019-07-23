/*
 * System.c
 *
 *  Created on: Jul 19, 2019
 *      Author: dhkim
 */

#include "CPU.h"
#include "System.h"
#include "Config_for_BootLoader.h"


#pragma CODE_SEG _PRESTART
void Dispatcher_2(void);
void Jump_to_Application(void);
#pragma CODE_SEG DEFAULT


/*******************************************************************************
* Name:			Dispatcher
*******************************************************************************/
#pragma CODE_SEG _PRESTART
void Dispatcher(void)
{
	asm LD S, #__SEG_END_SSTACK-1;		/* Temporary initialise SP, Bootloader or Application will do it again */

	Dispatcher_2();
}
#pragma CODE_SEG DEFAULT


/*******************************************************************************
* Name:			Dispatcher_2
*******************************************************************************/
#pragma CODE_SEG _PRESTART
void Dispatcher_2(void)
{
	if ((( *(unsigned int *)(EEPROM_END_ADD-1) ) == GOTOAPPLICATION) && (Check_Exist_Application() == TRUE))
	{
		Jump_to_Application();
	}
	
	_EntryPoint();  // Go to BootLoader
}
#pragma CODE_SEG DEFAULT


/*******************************************************************************
* Name:			Jump_to_Application
*******************************************************************************/
#pragma CODE_SEG _PRESTART
void Jump_to_Application(void)
{
	unsigned long int app_vector;

	//Jump to main application
	app_vector = *(unsigned long int *) (APPLICATION_RESET_VEC_ADD+1);
	asm LD X,app_vector;
	asm JMP (0,X);
}
#pragma CODE_SEG DEFAULT


/*******************************************************************************
* Name:			Check_Exist_Application
*******************************************************************************/
#pragma CODE_SEG _PRESTART
bool Check_Exist_Application(void)
{
	if ((*(unsigned long *) APPLICATION_RESET_VEC_ADD) != 0xFFFFFFFF)
		return TRUE;
	else
		return FALSE;
	
	return FALSE;
}
#pragma CODE_SEG DEFAULT


/*******************************************************************************
* Name:			SW_RESET
*******************************************************************************/
#pragma CODE_SEG _PRESTART
void SW_RESET(void)
{
	// CPMURFLG_COPRF : After SW reset, plz check this Register
	CPMUCOP = 0x01u;
	CPMUARMCOP = 0x66u;
	CPMUARMCOP = 0xAAu;
	while(1){};
}
#pragma CODE_SEG DEFAULT

