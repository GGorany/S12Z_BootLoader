

#include "S_Record.h"
#include "Flash_Control.h"


uint8_t SRec_Buffer_Before[CAN_SRec_Num];
SRecDataRec SRec_Buffer;


/*******************************************************************************
 Function Name : isdigit
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : NONE 
 Modifies      : NONE
 Returns       : TRUE/FALSE
 Notes         : check whether character is decimal number.
 Issues        : NONE
 *******************************************************************************/
int isdigit(int ch)
{
  return ((ch >= '0') && (ch <= '9'));
} 

/*******************************************************************************
 Function Name : isxdigit
 Engineer      : NXA19261
 Date          : Aug-17-2017
 Parameters    : NONE 
 Modifies      : NONE
 Returns       : TRUE/FALSE
 Notes         : check whether character is hexadecimal number.
 Issues        : NONE
 *******************************************************************************/
int isxdigit (int ch)
{
  return (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F')));
}

/*******************************************************************************
 Function Name : Parsing_SRecord
 *******************************************************************************/
uint8_t Make_Hex_Byte(uint8_t *MemByte, uint8_t High_side, uint8_t Low_side)
{
	if (!isxdigit(High_side))      //is it a valid hex digit
	{
	    return(BadHexData);  //no. return an error
	}
	
	//convert the ASCII character to a binary hex nybble
	*MemByte = (isdigit(High_side) ? High_side - '0' : High_side - 'A' + 10) << 4;

	if (!isxdigit(Low_side))      //is it a valid hex digit
	{
	    return(BadHexData);  //no. return an error
	}
	
	//convert the ASCII character to a binary hex nybble
	*MemByte += (isdigit(Low_side) ? Low_side - '0' : Low_side - 'A' + 10);
	
	return(noErr);         //return 'no error'
}

/*******************************************************************************
 Function Name : Making_SRecord
 *******************************************************************************/
uint8_t Making_SRecord(void)
{
	uint8_t x = 0;		// For Loop
	uint8_t Error = noErr;
	uint8_t CheckSum;			//used to hold calculated checksum value
	uint8_t SRecByte;			//used to hold memory/address bytes received through GetHexByte()
	uint8_t LoadAddress = 0;	//holds the converted load address of S-Record
	uint8_t Received_CheckSum = 0;	//Received Checksum
	
	if ((SRec_Buffer_Before[0] == 'S') && (SRec_Buffer_Before[1] == '2'))
	{
		Error = noErr;
		SRec_Buffer.RecType = DataRec;	// S2
	}
	else
	{
		return (Error);
	}
	
	// Get SRecord Number Bytes
	Error = Make_Hex_Byte(&SRec_Buffer.NumBytes, SRec_Buffer_Before[2], SRec_Buffer_Before[3]);
	if (Error != noErr)
	{
		return (SRecRangeError);
	}
	
	//initialize the checksum with the record length
	CheckSum = SRec_Buffer.NumBytes;
	
	// Get SRecord Address
	Error = Make_Hex_Byte(&LoadAddress, SRec_Buffer_Before[4], SRec_Buffer_Before[5]);
	SRec_Buffer.LoadAddr = LoadAddress;
	CheckSum += LoadAddress;
	if (Error != noErr)
	{
		return(Error);          //yes. report an error
	}
	
	Error = Make_Hex_Byte(&LoadAddress, SRec_Buffer_Before[6], SRec_Buffer_Before[7]);
	SRec_Buffer.LoadAddr = SRec_Buffer.LoadAddr<<8;
	SRec_Buffer.LoadAddr += LoadAddress;
	CheckSum += LoadAddress;
	if (Error != noErr)
	{
		return(Error);          //yes. report an error
	}
	
	Error = Make_Hex_Byte(&LoadAddress, SRec_Buffer_Before[8], SRec_Buffer_Before[9]);
	SRec_Buffer.LoadAddr = SRec_Buffer.LoadAddr<<8;
	SRec_Buffer.LoadAddr += LoadAddress;
	CheckSum += LoadAddress;
	if (Error != noErr)
	{
		return(Error);          //yes. report an error
	}

	// Get Data field
	for (x=0 ; x<32 ; x++)  //receive the data field
	{
		Error = Make_Hex_Byte(&SRec_Buffer.Data[x], SRec_Buffer_Before[10+(x*2)], SRec_Buffer_Before[11+(x*2)]);
		if (Error != noErr)     //get a data field byte. valid hex byte?
		{
			return(Error);        //no return an error
		}
		
		CheckSum += SRec_Buffer.Data[x];   //yes. add it in to the checksum    
	}
	
	// the record checksum (last byte of the record). valid hex byte?
	Error = Make_Hex_Byte(&Received_CheckSum, SRec_Buffer_Before[74], SRec_Buffer_Before[75]);
	if (Error != noErr)
	{
		return(Error);          //yes. report an error
	}
	
	CheckSum = ~CheckSum;	//take 1's compliment of calculated checksum
	if (CheckSum != Received_CheckSum)		//calculated checksum == received checksum ?
	{
		return(CheckSumErr);    //no. return an error
	}
	else
	{
		
		return(noErr);
	}
}

