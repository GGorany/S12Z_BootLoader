

#include "FLASH_Control.h"
#include "FLASH_S12Z.h"
#include "EEPROM_S12Z.h"
#include "Config_for_BootLoader.h"
#include <string.h>


/*******************************************************************************
 Function Name : FLASH_EraseApplication
 *******************************************************************************/
uint8_t FLASH_EraseApplication(void)
{
	uint8_t error = noErr;
	error = PFLASH_EraseSectorBySector(APP_FLASH_START_ADD, APP_FLASH_END_ADD);
	
	if (error)
	{
		error = (uint8_t)FlashEraseError;
	}
	
	return error;
}


/*******************************************************************************
 Function Name : ProgramFlash
 *******************************************************************************/
uint8_t ProgramFlash(uint8_t msg_buf[], uint16_t msg_dlc)
{
	uint8_t error = (uint8_t)noErr;
	uint32_t addr = 0;

	if (msg_dlc != 38)
	{
		return (FlashProgramError);
	}

	memcpy(&addr, &msg_buf[2], sizeof(uint8_t)*4);
	
	if (addr == APPLICATION_RESET_VEC_SRC)		// Application Reset Vector
	{
	   	//Program reset vector to address 0xFFBFFD (0xFFC000 - 4)
	   	error = PFLASH_Program((APPLICATION_RESET_VEC_ADD & 0xFFFFF8), (uint16_t *)&msg_buf[30]);
	   	if (error)
	   	{
	   		return (FlashProgramError);
	   	}
	}
	else
	{
	   	//is the address within a physical flash?
	    if ((addr >= APP_FLASH_START_ADD) && (addr <= APP_FLASH_END_ADD))
	    {
	      	error = PFLASH_Program(addr, (uint16_t *)&msg_buf[6]);
	       	if (error)
	       	{
	       		return (uint8_t)FlashProgramError;
	       	}
	       	
	       	error = PFLASH_Program(addr+8, (uint16_t *)&msg_buf[14]);
	       	if (error)
	       	{
	       		return (uint8_t)FlashProgramError;
	       	}

	       	error = PFLASH_Program(addr+16, (uint16_t *)&msg_buf[22]);
	       	if (error)
	       	{
	       		return (uint8_t)FlashProgramError;
	       	}

	       	error = PFLASH_Program(addr+24, (uint16_t *)&msg_buf[30]);
	       	if (error)
	       	{
	       		return (uint8_t)FlashProgramError;
	       	}
	    }
	    else return (uint8_t)FlashProgramError;
	}

    return (uint8_t)noErr;
}

