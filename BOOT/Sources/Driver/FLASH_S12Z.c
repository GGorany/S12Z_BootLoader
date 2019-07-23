

#include <hidef.h>           /* common defines and macros */
#include "IO_Map.h"
#include "flash_S12Z.h"


/*******************************************************************************
 Function Name : PFLASH_Send_Command
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : NONE
 Modifies      : NONE
 Returns       : NONE
 Notes         : We cannot simultaneously execute code from the same flash block which we program.
                 Therefore PFLASH_Send_Command() is executed from RAM.
                 The PFLASH_Send_Command() function disable interrupts for avoiding Flash reading, 
                 launch Flash command and wait until command finish.
                 When command finish, the function restore the CCR register back.
 Issues        : NONE
 *******************************************************************************/ 
#pragma CODE_SEG DEFAULT_RAM
void PFLASH_Send_Command(void)
{
    asm PSH CCL;	//Store Condition Code register on stack
    DisableInterrupts;

    FSTAT_CCIF = 1;           //launch command
    while(FSTAT_CCIF == 0){}; //wait for done

    asm PUL CCL; //Restore Condition Code register from stack
}
#pragma CODE_SEG DEFAULT

/*******************************************************************************
 Function Name : PFLASH_Erase_Verify_Section
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : target address, number of tested phrases
 Modifies      : NONE
 Returns       : Error codes
 Notes         : Test whether Flash area is erased or not.
 Issues        : NONE
 *******************************************************************************/ 
unsigned char PFLASH_Erase_Verify_Section(unsigned long int address, unsigned int number_of_phrases)
{
    //check if address is aligned (global address [2:0] = 000)
    if((address & 0x00000007) != 0)
        return MISALIGNED_ADDRESS; 

    while(FSTAT_CCIF == 0){};   //wait if command in progress
    FSTAT = 0x30;               //clear ACCERR and PVIOL

    FCCOBIX = 0x02;             //we will write command up to FCCOB2
    FCCOB0HI = 0x03;
    FCCOB0LO = ((address & 0x00FF0000)>>16);

    FCCOB1 = (address & 0x0000FFFF);

    FCCOB2 = number_of_phrases;

    PFLASH_Send_Command();

    if((FSTAT & (FSTAT_ACCERR_MASK | FSTAT_FPVIOL_MASK)) != 0)
        return ACCESS_ERROR;

    //check if phrases are erased and return result
    if(FSTAT_MGSTAT != 0)
        return NON_ERASED;
    else
        return ERASED;
}

/*******************************************************************************
 Function Name : PFLASH_Program
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : target address, pointer to data
 Modifies      : NONE
 Returns       : Error codes
 Notes         : Write phrase to the Flash.
 Issues        : NONE
 *******************************************************************************/
unsigned char PFLASH_Program(unsigned long int address, unsigned int *ptr)
{
    unsigned char i;

    //check if address is aligned (global address [2:0] != 000)
    if((address & 0x00000007) != 0)
        return MISALIGNED_ADDRESS; 

    //check if the phrase is erased    
    if((PFLASH_Erase_Verify_Section(address, 1)) == NON_ERASED)
        return NON_ERASED;  

    while(FSTAT_CCIF == 0){};   //wait if command in progress
    FSTAT = 0x30;               //clear ACCERR and PVIOL

    FCCOBIX = 0x05;             //we will write command up to FCCOB5
    FCCOB0HI = 0x06;
    FCCOB0LO = ((address & 0x00FF0000)>>16);

    FCCOB1 = (address & 0x0000FFFF);

    FCCOB2 = ptr[0];
    FCCOB3 = ptr[1];
    FCCOB4 = ptr[2];
    FCCOB5 = ptr[3];

    PFLASH_Send_Command();

    if((FSTAT & (FSTAT_ACCERR_MASK | FSTAT_FPVIOL_MASK)) != 0)
        return ACCESS_ERROR;
    else
        return OK;
}

/*******************************************************************************
 Function Name : PFLASH_Erase_Sector
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : target sector address
 Modifies      : NONE
 Returns       : Error codes
 Notes         : Erase Flash sector.
 Issues        : NONE
 *******************************************************************************/
unsigned char PFLASH_Erase_Sector(unsigned long int address)
{
    //size of sector is 512B

    //check if address is aligned (global address [2:0] != 000)  
    if((address & 0x00000007) != 0)
    return MISALIGNED_ADDRESS; 

    while(FSTAT_CCIF == 0){};   //wait if command in progress
    FSTAT = 0x30;               //clear ACCERR and PVIOL

    FCCOBIX = 0x01;             //we will write command up to FCCOB1
    FCCOB0HI = 0x0A;
    FCCOB0LO = ((address & 0x00FF0000)>>16);

    FCCOB1 = (address & 0x0000FFFF);

    PFLASH_Send_Command();

    if((FSTAT & (FSTAT_ACCERR_MASK | FSTAT_FPVIOL_MASK)) != 0)
        return ACCESS_ERROR;
    else    
        return OK;
}

/*******************************************************************************
 Function Name : PFLASH_EraseSectorBySector
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : sector address FROM, sector address TO
 Modifies      : NONE
 Returns       : Error codes
 Notes         : Erase Flash sector by sector.
 Issues        : NONE
 *******************************************************************************/
unsigned char PFLASH_EraseSectorBySector(unsigned long int addr_l, unsigned long int addr_h)
{ 
    unsigned long int Address;
    unsigned char Error;
  
    for(Address = addr_l; Address < addr_h; Address += FLASH_SECTOR_SIZE)
    {
        Error = PFLASH_Erase_Sector(Address);
        if(Error != OK)
        return(NON_ERASED);
    }
    return OK;
}

/*******************************************************************************
 Function Name : PFLASH_Protection_Override
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : Protection Override Key, new FPROT value, new DFPROT value, Protection Update Selection 
 Modifies      : NONE
 Returns       : error codes
 Notes         : Modify FPROT/DFPROT/(FPROT+DFPROT) register value(s) when Protection Override Key is correct.
 Issues        : NONE
 *******************************************************************************/
unsigned char PFLASH_Protection_Override(unsigned int comparison_key, unsigned char new_FPROT_value, unsigned char new_DPROT_value, unsigned char protection_update_selection)
{
    unsigned char i;

    while(FSTAT_CCIF == 0){};   //wait if command in progress
    FSTAT = 0x30;               //clear ACCERR and PVIOL    

    FCCOBIX = 0x03;             //we will write command up to FCCOB3
    FCCOB0HI = 0x13;            //Protection Override Command
    FCCOB0LO = protection_update_selection;            
                              //Protection Update Selection - 
                              //0x01 update FPROT,
                              //0x02 update DFPROT, 
                              //0x03 update FPROT and DFPROT 

    FCCOB1 = comparison_key;

    FCCOB2LO = new_FPROT_value;
    FCCOB3LO = new_DPROT_value;

    PFLASH_Send_Command();

    if((FSTAT & (FSTAT_ACCERR_MASK | FSTAT_FPVIOL_MASK)) != 0)
        return ACCESS_ERROR;
    else    
        return OK;
}

/*******************************************************************************
 Function Name : PFLASH_Read_Byte
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : Target address 
 Modifies      : NONE
 Returns       : data
 Notes         : Read a Byte.
 Issues        : NONE
 *******************************************************************************/
unsigned char PFLASH_Read_Byte(unsigned long int address)
{
    unsigned char data8;
    data8 = *(unsigned char *)address;
    return data8;
}

/*******************************************************************************
 Function Name : PFLASH_Read_Word
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : Target address 
 Modifies      : NONE
 Returns       : data
 Notes         : Read a Word.
 Issues        : NONE
 *******************************************************************************/
unsigned int PFLASH_Read_Word(unsigned long int address)
{
    unsigned int data16;
    data16 = *(unsigned int *)address;
    return data16;
}

/*******************************************************************************
 Function Name : PFLASH_Init
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : FCLKDIV value - Flash Clock Divider  
 Modifies      : NONE
 Returns       : NONE
 Notes         : Set Flash Clock Divider.
 Issues        : NONE
 *******************************************************************************/
void PFLASH_Init(unsigned char fdiv)
{
    while(FSTAT_CCIF == 0){};   //wait if command in progress  
    FCLKDIV = fdiv;             //osc = ? MHz    
}
