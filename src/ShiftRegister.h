#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include "Arduino.h"
#include "BITDEFS.H"
#include <stdint.h>
#include <stdbool.h>
//#include <cstdint> 


// Definitions on Port D (pins 0 - 7) 
#define SER BIT3HI
#define SRCK BIT4HI
#define RCK BIT2HI


// https://forum.arduino.cc/index.php?topic=45003.0

#ifdef __cplusplus
extern "C" {
#endif

void sr_init(void); 
void sr_write8(uint8_t data_out);
void sr_write16(uint16_t data_out);
void sr_write32(uint32_t data_out);
void sr_write64(uint64_t data_out);


#ifdef __cplusplus
}
#endif


#endif // SHIFT_REGISTER_H
