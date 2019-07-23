

#ifndef S_RECORD_H_
#define S_RECORD_H_

#include "PE_Types.h"

//==============================================================================
// Definitions
//==============================================================================

#define DataRec 1
#define EndRec 2
#define HeaderRec 3

#define MaxSRecLen 64
#define S2_Max_SRecLen	32

#define CAN_SRec_Num	76 	//(13*6)-2

typedef struct {
                uint8_t RecType;				// 1
                uint8_t NumBytes;				// 1
                uint32_t LoadAddr;				// 4
                uint8_t Data[S2_Max_SRecLen];	// 32
               } SRecDataRec;

//==============================================================================
// Function Prototypes
//==============================================================================                
int isdigit(int ch);
int isxdigit (int ch);

uint8_t Making_SRecord(void);
uint8_t Make_Hex_Byte(uint8_t *MemByte, uint8_t High_side, uint8_t Low_side);

extern SRecDataRec SRec_Buffer;
extern uint8_t SRec_Buffer_Before[CAN_SRec_Num];


#endif /* S_RECORD_H_ */
