/*
 * LED.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */
#include "RCC_CLOCK_DEFINES.h"
#include"GPIO_STRUCTURES.h"
#include"main.h"

// RCC registers
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
// GPIOB registers
#define GPIOB_CRL       (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
void LED_INIT(){
   // RCC_APB2ENR |= (1 << 3); // IOPBEN
	RY_RCC->APB2ENR.BITS.IOPBEN=1;
	//GPIOB->CRL.ALL&=~(0XF<<(2*8));
	RY_GPIOB->CRL.BITS.CNF2=0b00;
	RY_GPIOB->CRL.BITS.MODE2=0b10;
}
void TOGGLE_LED(){
    GPIOB_ODR ^=(1 << 2); ;
	//RY_GPIOB->ODR.BITS.ODR2=1;
	}
void STATUS_LEDS_APP_OR_BOOT_INIT(){
	RY_RCC->APB2ENR.BITS.IOPCEN=1;
	RY_GPIOC->CRH.BITS.CNF13=0b00;
	RY_GPIOC->CRH.BITS.CNF13=0b10;
	RY_GPIOC->CRH.BITS.CNF14=0b00;
	RY_GPIOC->CRH.BITS.CNF14=0b10;
}
