/*
 * SYSTICK_TIMER.h
 *
 *  Created on: Jul 28, 2025
 *      Author: maday
 */

#ifndef INC_SYSTICK_STRUCTURES_H_
#define INC_SYSTICK_STRUCTURES_H_
#include <stdint.h>

typedef union {
    uint32_t ALL;
    struct {
        uint32_t ENABLE     : 1;  // Bit 0: Counter enable
        uint32_t TICKINT    : 1;  // Bit 1: SysTick exception request enable
        uint32_t CLKSOURCE  : 1;  // Bit 2: Clock source (0 = AHB/8, 1 = AHB)
        uint32_t RESERVED0  : 13;
        uint32_t COUNTFLAG  : 1;  // Bit 16: Returns 1 if timer counted to 0 since last read
        uint32_t RESERVED1  : 15;
    } BITS;
} SysTick_CTRL_REG;

// SysTick full structure
typedef struct {
    volatile SysTick_CTRL_REG CTRL;   // 0x00 - Control and status
    volatile uint32_t LOAD;           // 0x04 - Reload value
    volatile uint32_t VAL;            // 0x08 - Current value
    volatile uint32_t CALIB;          // 0x0C - Calibration value
} RY_SysTick_Type;

#define RY_SYSTICK ((volatile RY_SysTick_Type*)0xE000E010)

#endif /* INC_SYSTICK_STRUCTURES_H_ */
