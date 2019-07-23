

#ifndef EEPROM_S12Z_H_
#define EEPROM_S12Z_H_


//==============================================================================
// Definitions
//==============================================================================
#define EEPROM_SECTOR_SIZE 4  //4 bytes

/* Error codes */
#define OK          		0
#define ERASED      		1
#define NON_ERASED  		2
#define MISALIGNED_ADDRESS  3
#define ACCESS_ERROR        4

//==============================================================================
// Function Prototypes
//==============================================================================
extern unsigned char EEPROM_Erase_Verify_Section(unsigned long int address, unsigned int number_of_words);
extern unsigned char EEPROM_Program(unsigned long int address, unsigned int *ptr, unsigned int number_of_words);
extern unsigned char EEPROM_Erase_Sector(unsigned long int address);
extern unsigned char EEPROM_EraseSectorBySector(unsigned long int addr_l, unsigned long int addr_h);
extern unsigned char EEPROM_Read_Byte(unsigned long int address);
extern unsigned int EEPROM_Read_Word(unsigned long int address);

extern void EEPROM_Init(unsigned char fdiv);

#endif /* EEPROM_S12Z_H_ */
