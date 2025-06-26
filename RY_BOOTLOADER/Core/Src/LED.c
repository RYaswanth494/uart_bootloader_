/*
 * LED.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */
#include"GPIO.h"
#include"DEFINATIONS.h"
#include"RCC_CLOCK.h"
#include"main.h"
void LED_INIT(){
	 RCC_APB2ENR |= RCC_IOPBEN;
	 GPIOB_CRL &= ~(0xF << (2 * 4));
	 GPIOB_CRL |= PB2_OUTPUT_2MHZ_GP_PUSH_PULL;
}
void TOGGLE_LED(){
    GPIOB_ODR |= (1 << 2);  // Set PB2 high
    HAL_Delay(100);
    GPIOB_ODR &= ~(1 << 2); // Set PB2 low
    HAL_Delay(100);}
