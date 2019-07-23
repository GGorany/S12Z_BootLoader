/*
 * Config_for_BootLoader.h
 *
 *  Created on: Jun 19, 2019
 *      Author: TE381294
 */

#ifndef CONFIG_FOR_BOOTLOADER_H_
#define CONFIG_FOR_BOOTLOADER_H_


// Memory Map Address
#define EEPROM_START_ADD				0x100000UL 	// EEPROM start address
#define EEPROM_END_ADD					0x1003FFUL 	// EEPROM end address

#define APP_FLASH_START_ADD 			0xFF0000UL 	// Application Flash memory start address
#define APP_FLASH_END_ADD 				0xFFBFFFUL 	// Application Flash memory end address

#define BOOT_FLASH_START_ADD			0xFFC000UL	// Bootloader Flash memory start address
#define BOOT_FLASH_END_ADD				0xFFFFFFUL	// Bootloader Flash memory end address
#define BOOTLOADER_SIZE					(BOOT_FLASH_END_ADD - BOOT_FLASH_START_ADD)

#define APPLICATION_RESET_VEC_SRC		0xFFFFE0UL	// last 32bytes in Flash with reset vector. Reset vector starts at 0xFFFFFD
#define APPLICATION_END_ADD				(BOOT_FLASH_START_ADD - 4)	// last four bytes from Application are allocated for Application Start Address Vector
#define APPLICATION_RESET_VEC_ADD		APPLICATION_END_ADD			// here is stored Application Start vector of user application

#define INT_VECTOR_TABLE_ADDR			0x00FF0010UL	// Application's Interrupt vector table




// GOTO BootLoader Value
#define GOTOBOOTLOADER      0xFFFFU
// GOTO Application Value
#define GOTOAPPLICATION     0x5A5AU

// Version information
#define Application_version_Address		0xFFBDF0UL	// 0xFFBFFF - 0x200 - 0x10
#define BootLoader_version_Address		0xFFFDF0UL	// 0xFFFFFF - 0x200 - 0x10




#endif /* CONFIG_FOR_BOOTLOADER_H_ */
