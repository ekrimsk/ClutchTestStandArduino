/****************************************************************************
 Module
     ES_Port.h
 Description
     header file to collect all of the hardware/platform dependent info for
     a particular port of the ES framework
 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 08/13/13 12:12 jec      moved the timer rate constants from ES_Timers.h here
 08/05/13 14:24 jec      new version replacing port.h and adding define to
                         capture the C99 compliant behavior of the compiler
*****************************************************************************/
#ifndef ES_PORT_H
#define ES_PORT_H


#include <stdio.h>
#include "Bin_Const.h"     /* macros to specify binary constants in C */
#include "ES_Types.h"


// macro to control the use of C99 data types (or simulations in case you don't
// have a C99 compiler).

// Codewarrior V5, is not C99 so keep this commented out for C32 & E128
//#define COMPILER_IS_C99

// The macro 'ES_FLASH' is needed on some compilers to allocate const data to 
// ROM. The macro must be defined, even if it evaluates to nothing.
// for the 'C32 & E128 this is not needed so it evaluates to nothing
#define ES_FLASH 

// the macro 'ES_READ_FLASH_BYTE' is needed on some Harvard machines to generate
// code to read a byte from the program space (Flash)
// The macro must be defined, even if it evaluates to nothing.
// for the 'C32 & E128 we don't need special instructions so it evaluates to a
// simple reference to the variable
#define ES_READ_FLASH_BYTE(_flash_var_)    (_flash_var_)                  

// these macros provide the wrappers for critical regions, where ints will be off
// but the state of the interrupt enable prior to entry will be restored.
// allocation of temp var for saving interrupt enable status should be defined
// in ES_Port.c
extern unsigned char _CCR_temp;

#define EnterCritical()   __disable_irq()  //{ __asm pshc; __asm sei; __asm movb 1,SP+,_CCR_temp; } /* This macro saves CCR register and disables global interrupts. */
#define ExitCritical()  	__enable_irq()	//{ __asm movb _CCR_temp, 1,-SP ; __asm pulc; } /* This macro restores CCR register saved EnterCritical(). */


/* Rate constants for programming the RTI to generate tick interrupts
   these assume an 8MHz OSCCLK, they are the values to be used to program
   the RTICTL regiser
 */
typedef enum { ES_Timer_RATE_OFF  =   (0),
               ES_Timer_RATE_1MS  = 977, /* 1.024mS */
               ES_Timer_RATE_2MS  = 504, /* 2.048mS */
               ES_Timer_RATE_4MS  = 256, /* 4.096mS */
               ES_Timer_RATE_8MS  = 129, /* 8.196mS */
               ES_Timer_RATE_16MS = 65, /* 16.384mS */
               ES_Timer_RATE_32MS = 32  /* 32.768mS */
} TimerRate_t;

// map the generic functions for testing the serial port to actual functions 
// for this platform. If the C compiler does not provide functions to test
// and retieve serial characters, you should write them in ES_Port.c
//#define IsNewKeyReady()  ( kbhit() != 0 )
//#define GetNewKey()      getchar()

// prototypes for the hardware specific routines
void _HW_Timer_Init(TimerRate_t Rate);
bool _HW_Process_Pending_Ints( void );

#endif /* ES_PORT_H */
