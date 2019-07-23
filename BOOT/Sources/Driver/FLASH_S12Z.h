

#ifndef FLASH_S12Z_H_
#define FLASH_S12Z_H_


//==============================================================================
// Definitions
//==============================================================================
#define FLASH_SECTOR_SIZE 512

/* Error codes */
#define OK          			0
#define ERASED      			1
#define NON_ERASED  			2
#define MISALIGNED_ADDRESS  	3
#define ACCESS_ERROR        	4

//==============================================================================
// Function Prototypes
//============================================================================== 
#pragma CODE_SEG DEFAULT_RAM
extern void PFLASH_Send_Command(void);
#pragma CODE_SEG DEFAULT


extern unsigned char PFLASH_Erase_Verify_Section(unsigned long int address, unsigned int number_of_phrases);
extern unsigned char PFLASH_Program(unsigned long int address, unsigned int *ptr);
extern unsigned char PFLASH_Erase_Sector(unsigned long int address);
extern unsigned char PFLASH_EraseSectorBySector(unsigned long int addr_l, unsigned long int addr_h);
extern unsigned char PFLASH_Protection_Override(unsigned int comparison_key, unsigned char new_FPROT_value, unsigned char new_DPROT_value, unsigned char protection_update_selection);
extern unsigned char PFLASH_Read_Byte(unsigned long int address);
extern unsigned int PFLASH_Read_Word(unsigned long int address);

extern void PFLASH_Init(unsigned char fdiv);



#endif /* FLASH_S12Z_H_ */
