/*
 * LED.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */
#include "RCC_CLOCK_DEFINES.h"
#include"GPIO.h"
#include"DEFINATIONS.h"
#include"main.h"

// RCC registers
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
// GPIOB registers
#define GPIOB_CRL       (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
void LED_INIT(){
    RCC_APB2ENR |= (1 << 3); // IOPBEN
	 GPIOB_CRL &= ~(0xF << (2 * 4));
	    GPIOB_CRL |=  (0x2 << 8);     // MODE2 = 10 (Output 2 MHz), CNF2 = 00 (General purpose output push-pull)
}
void TOGGLE_LED(){
    GPIOB_ODR ^=(1 << 2); ;
	}
