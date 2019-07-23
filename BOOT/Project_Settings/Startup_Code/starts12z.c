/*****************************************************
    starts12z.c - startup code for S12Z (S12/L-ISA)
 ----------------------------------------------------
   Copyright (c) Freescale Semiconductor
               All rights reserved

 *****************************************************/



#include "starts12z.h"

#ifdef __cplusplus
#define __EXTERN_C  extern "C"
#else
#define __EXTERN_C
#endif

#if __ASM_DATA_ADDR_OPT__
const
#endif
struct _tagStartup _startupData 
#if __ASM_DATA_ADDR_OPT__
#ifdef __cplusplus
= {}
#endif
#endif
;					/* read-only: */
					/* _startupData is allocated in ROM and */
					/* initialized by the linker */

void main(void);		/* prototype of main function */

static void DoZeroOut(void) {
	__asm {
		LD D6, _startupData.nofZeroOuts
		BEQ end					/* nothing to do */  
		LD X, _startupData.pZeroOut
	zeroOutLoop:
		LD Y,  (0,X)				/* X points to the first range */
		LD D7, (3,X)				/* D7 holds size */
	doZeroOut:
		CLR.b (Y+)
		DBNE D7, doZeroOut
		LEA X, (7,X)
		DBNE D6, zeroOutLoop
	end:
	}
}

static void DoCopyDown(void) {
 	__asm {
		LD Y, _startupData.toCopyDownBeg
		BEQ end					/* the pointer is NULL */
	nextItemLoop:
		LD D6, (Y+)				/* load the size */
		BEQ end
		LD X, (Y+)				/* load the destination */
	copyLoop:
		MOV.b (Y+), (X+)			/* copy the data */
		DBNE D6, copyLoop
		BRA nextItemLoop
	end:
	}
}

#ifdef __cplusplus
static void __static_init(void) {
	__asm {
		LD D5, _startupData.nofInitBodies
		BEQ end
		LD X, _startupData.initBodies
	initNextBody:
		LD Y,(X+)
		PSH ALL
		JSR (Y+)
		PUL ALL
		DBNE D5, initNextBody
	end:
	}
	
}
#endif

extern int __SEG_END_SSTACK[];

__EXTERN_C void _Startup(void) {
	__asm {
		LD S, #__SEG_END_SSTACK-1		/* initialize SP */
#ifdef __ALIGN_STACK_OPT__
    	TFR S, D6                        /* align SP to 4*/
    	AND D6, #-4
    	TFR D6, S
#endif		
	}
	DoZeroOut();
	DoCopyDown();
#ifdef __cplusplus
	__static_init();
#endif
	main();
}
