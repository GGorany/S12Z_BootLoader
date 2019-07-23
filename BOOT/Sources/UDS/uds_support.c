/***************************************************************************//**
    \file          uds-support.c
    \author     
    \mail          
    \version       0.01
    \date          2016-10-8
    \description   uds service spport code, include read/write data,
                   io control and routine control
*******************************************************************************/

/*******************************************************************************
    Include Files
*******************************************************************************/
#include "uds_support.h"
#include "FLASH_Control.h"
#include "Config_for_BootLoader.h"
#include <string.h>


#define NULL    ((void *)0)

/*******************************************************************************
    Function  declaration
*******************************************************************************/
static uint8_t rtctrl_nothing(void);
static uint8_t rtctrl_eraseApplication(void);

static void ioctrl_init_backlight(void);
static void ioctrl_stop_backlight(void);
static void ioctrl_init_buzzer(void);
static void ioctrl_stop_buzzer(void);
static void ioctrl_init_gages(void);
static void ioctrl_stop_gages(void);
static void ioctrl_init_display(void);
static void ioctrl_stop_display(void);
static void ioctrl_init_indicator(void);
static void ioctrl_stop_indicator(void);

void uds_save_rwdata(void);

/*******************************************************************************
    Global Varaibles
*******************************************************************************/
uint8_t ASC_boot_ver[8] = {0, };
extern uint8_t uds_session;
uint8_t ASC_sys_supplier_id[5] = {'1', '2', '3', '4', '5'};
uint8_t ASC_soft_ver[8]= {0, };
uint8_t ASC_sys_name[10]= {'I', 'C', 'U', '-', 'm', '1', '2', 'e', 0, 0};


//uint8_t ASC_ecu_part_num[15]  __at(0x20000400);
//uint8_t BCD_manufacture_date[3] __at(0x2000040F);
//uint8_t HEX_ecu_sn[10] __at(0x20000412);
//uint8_t ASC_VIN[17] __at(0x2000041C);
//uint8_t HEX_tester_sn[10] __at(0x2000042D);
//uint8_t BCD_program_date[3] __at(0x20000437);

uint8_t ASC_ecu_part_num[15] = {0, };
uint8_t BCD_manufacture_date[3] = {0, };
uint8_t HEX_ecu_sn[10] = {0, };
uint8_t ASC_VIN[17] = {0, };
uint8_t HEX_tester_sn[10] = {0, };
uint8_t BCD_program_date[3] = {0, };


// we add read write data and it's identify here to support service 22
const uds_rwdata_t rwdata_list[RWDATA_CNT] =
{
	{0xF189, ASC_soft_ver,         7, UDS_RWDATA_RDONLY,      UDS_RWDATA_DFLASH},
	{0xF195, ASC_boot_ver,         7, UDS_RWDATA_RDONLY,      UDS_RWDATA_DFLASH},
    //{0xF183, ASC_boot_ver,         10, UDS_RWDATA_RDONLY,      UDS_RWDATA_DFLASH},
    {0xF186, &uds_session,         1,  UDS_RWDATA_RDONLY,      UDS_RWDATA_RAM}
    //{0xF187, ASC_ecu_part_num,     15, UDS_RWDATA_RDWR_INBOOT, UDS_RWDATA_EEPROM},
    //{0xF18A, ASC_sys_supplier_id,  5,  UDS_RWDATA_RDONLY,      UDS_RWDATA_DFLASH},
    //{0xF18B, BCD_manufacture_date, 3,  UDS_RWDATA_RDONLY,      UDS_RWDATA_EEPROM}, /* be writen after manufacture */
    //{0xF18C, HEX_ecu_sn,           10, UDS_RWDATA_RDONLY,      UDS_RWDATA_EEPROM}, /* be writen after manufacture */
    //{0xF190, ASC_VIN,              17, UDS_RWDATA_RDWR_WRONCE, UDS_RWDATA_EEPROM}, /* be writen after installment */
    //{0xF195, ASC_soft_ver,         10, UDS_RWDATA_RDONLY,      UDS_RWDATA_DFLASH},
    //{0xF197, ASC_sys_name,         10, UDS_RWDATA_RDONLY,      UDS_RWDATA_DFLASH},
    //{0xF198, HEX_tester_sn,        10, UDS_RWDATA_RDWR_INBOOT, UDS_RWDATA_EEPROM}, /* update by tester after program */
    //{0xF199, BCD_program_date,     3,  UDS_RWDATA_RDWR_INBOOT, UDS_RWDATA_EEPROM} /* update by tester after program */
};


const uds_rtctrl_t rtctrl_list[RTCTRL_CNT] =
{
	//{0, UDS_RT_ST_IDLE, &rtctrl_nothing, &rtctrl_nothing, &rtctrl_nothing}
	{0xFF00, UDS_RT_ST_IDLE, &rtctrl_eraseApplication, &rtctrl_nothing, &rtctrl_nothing}		// Erase memory
};


extern const unsigned char BootLoader_Version_array[];



/*******************************************************************************
    Function  Definition
*******************************************************************************/


/*******************************************************************************
    Function  Definition - extern to uds
*******************************************************************************/


void init_uds_support(void)
{
	memcpy(ASC_boot_ver, BootLoader_Version_array, sizeof(uint8_t)*8);
	memcpy(ASC_soft_ver, (uint8_t*)Application_version_Address, sizeof(uint8_t)*8);
}


/**
 * rtctrl_nothing - a temp Function for routine control
 *
 * @void :
 *
 * returns:
 *     0 - ok
 */
static uint8_t rtctrl_nothing(void)
{
    return 0;
}

static uint8_t rtctrl_eraseApplication(void)
{
    (void)FLASH_EraseApplication();

    return 0;
}





/**
 * uds_ioctrl_allstop - main handle of io control
 *
 * @void : 
 *
 * returns:
 *     void
 */
void uds_ioctrl_allstop(void)
{
#if 0
    uint16_t did_n;

    for (did_n = 0; did_n < IOCTRL_NUM; did_n++)
    {
        if (ioctrl_list[did_n].enable == TRUE)
        {
            /* need to mutex with 2F service UDS_IOCTRL_RETURN_TO_ECU */
            ioctrl_list[did_n].enable = FALSE;
            if (ioctrl_list[did_n].stop_ioctrl != NULL)
                ioctrl_list[did_n].stop_ioctrl ();
        }
    }
#endif
}


/**
 * uds_load_rwdata - load read / write data from eeprom to ram
 *
 * @void : 
 *
 * returns:
 *     void
 */
void uds_load_rwdata(void)      
{
    //memset (ASC_ecu_part_num, 0x55, (15+3+10+17+10+3));      // read the  rwdata_list which is in eeprom,and then assign to  rwdata_list element
}

/**
 * uds_save_rwdata - save read / write data from eeprom to ram
 *
 * @void : 
 *
 * returns:
 *     void
 */
void uds_save_rwdata(void)
{
    //memset (ASC_ecu_part_num, 0x55, (15+3+10+17+10+3));  // //  then rwdata_list element  assign to  a certern space and write to flash
}
/****************EOF****************/
