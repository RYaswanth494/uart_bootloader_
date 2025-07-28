/*
 * SYS_TICK.c
 *
 *  Created on: Jul 28, 2025
 *      Author: maday
 */
#include"main.h"
#include"SYSTICK_STRUCTURES.h"
#include"SYSTICK_DECLARATIONS.h"
 uint32_t systick_ms_counter;

// Set up for 1ms tick with 72 MHz clock
void systick_init(uint32_t ticks_per_ms)
{
    RY_SYSTICK->LOAD = ticks_per_ms - 1;    // e.g., 72000 - 1
    RY_SYSTICK->VAL  = 0;
    RY_SYSTICK->CTRL.BITS.CLKSOURCE = 1;    // Use core clock (AHB)
    RY_SYSTICK->CTRL.BITS.TICKINT   = 1;    // Enable interrupt
    RY_SYSTICK->CTRL.BITS.ENABLE    = 1;    // Start timer

}
void systick_reset(void)
{
    systick_ms_counter = 0;
}
uint32_t systick_get_ms(void)
{
    return systick_ms_counter;
}

// SysTick driver instance
SysTickDriver systick = {
    .init = systick_init,
    .reset = systick_reset,
    .get_ms = systick_get_ms
};
