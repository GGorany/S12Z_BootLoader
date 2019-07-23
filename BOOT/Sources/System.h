/*
 * System.h
 *
 *  Created on: Jul 19, 2019
 *      Author: dhkim
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "PE_Types.h"

//==============================================================================
// Definitions
//==============================================================================
extern int __SEG_END_SSTACK[];

//==============================================================================
// Function Prototypes
//============================================================================== 
#pragma CODE_SEG _PRESTART

void Dispatcher(void);		/* prototype of main function */
bool Check_Exist_Application(void);
void SW_RESET(void);

#pragma CODE_SEG DEFAULT



#endif /* SYSTEM_H_ */
