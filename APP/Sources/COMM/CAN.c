

/**********************************************************************************************************************
* MODULES USED 
**********************************************************************************************************************/
#include "CAN.h"
#include "CANComm.h"
#include "CAN_Config.h"
#include "E2P.h"
#include "MCU_SYSTEM.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void TXMESSAGE(CAN_Frame* msg);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
CAN_Frame msg_ECU_Reset_Pos = {
		DIAG_PHYS_TX_ID,
		8,
		{0x02, 0x51, 0x20, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}
};

CAN_Frame msg_ECU_Reset_Neg = {
		DIAG_PHYS_TX_ID,
		8,
		{0x03, 0x7F, 0x11, 0x10, 0xAA, 0xAA, 0xAA, 0xAA}
};

CAN_Frame temp_CAN = {
		0x00112233,
		8,
		{0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}
};

/*--------------------------------------------------------------------------*/
/* Function  | TASK of CAN Control                                          */
/* Name      | Task_CAN                                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Task_CAN(void)
{
	static uint16_t count = 0;
	
    count++;
    
    if (count == 200)
    {
    	count = 0;
    	TXMESSAGE(&temp_CAN);
    }
}


/*--------------------------------------------------------------------------*/
/* Function  | CAN TX Message                                               */
/* Name      | TXMESSAGE                                                    */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void TXMESSAGE(CAN_Frame* msg)
{
	(void)CANComm_SendFrameExt(msg->CAN_ID | CAN_EXTENDED_FRAME_ID, DATA_FRAME, msg->Length, msg->data);
}


/*--------------------------------------------------------------------------*/
/* Function  | Called by CAN RX interrupt                                   */
/* Name      | RXMESSAGE                                                    */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RXMESSAGE(void)
{
	uint32_t ID;
	uint8_t dummy1, dummy2;
	uint8_t dlc;
	uint8_t data[8];

	CANComm_ReadFrame(&ID, &dummy1, &dummy2, &dlc, data);

	if (ID == DIAG_PHYS_RX_ID)
	{
        if ((data[0] == 0x02) && (data[1] == 0x11)) // ECU Reset
        {
            if (data[2] == 0x20)    // Reset to BootLoader
            {
                if (TRUE == Check_Exist_BootLoader())
                {
                    TXMESSAGE(&msg_ECU_Reset_Pos);
                    while(CANComm_GetStateTX() != 0x07){};
                    SET_GOTO_BOOTLOADER();
                    MCU_SYSTEM_SWReset();
                }
                else
                {
                    TXMESSAGE(&msg_ECU_Reset_Neg);
                }
            }
        }
	}
}
