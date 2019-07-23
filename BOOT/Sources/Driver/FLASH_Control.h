

#ifndef FLASH_CONTROL_H_
#define FLASH_CONTROL_H_


#include "PE_Types.h"

typedef enum { 
	noErr = 0,
	SRecRangeError = 1,      //S-Record Out Of Range
	SRecOddError = 2,        //S-Record Size Must Be Even
	FlashProgramError = 3,  //Flash Programming Error
	FlashEraseError = 4,    //Flash Erase Error
	BadHexData = 5,          //Bad Hex Data
	SRecTooLong = 6,        //S-Record Too Long
	CheckSumErr = 7,        //Checksum Error
	No_SRecord = 8,			//This is no SRecord
	CAN_Frame_missing = 9	//CAN Frame missing
}Error_type;


uint8_t FLASH_EraseApplication(void);
uint8_t ProgramFlash(uint8_t msg_buf[], uint16_t msg_dlc);


#endif /* FLASH_CONTROL_H_ */
