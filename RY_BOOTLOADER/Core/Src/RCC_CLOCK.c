/*
 * RCC_CLOCK.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */


#include"RCC_CLOCK_DEFINES.h"
#include"DEFINATIONS.h"
#include"GPIO.h"
/*********************************************************************************
 *                                                                                *
 *              FUNCTION_NAME:RCC_SYSTEM_CLOCK_HSI[8MHZ]                                *
 *                                                                                *                                                            *
 * ********************************************************************************/
    // 1. Enable HSI
    // 2. Wait until HSI is ready
    // 3. Select HSI as system clock & Clear SW bits to select HSI
    // 4. Wait until HSI is confirmed as system clock
void RCC_SYSTEM_CLOCK_HSI(){
    RCC_CR |= RCC_CR_HSION;
    while (!(RCC_CR & RCC_CR_HSIRDY));
    RCC_CFGR &= ~RCC_CFGR_SW_MASK;
    while ((RCC_CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_HSI);
}
/*********************************************************************************
 *                                                                                *
 *              FUNCTION_NAME:RCC_SYSTEM_CLOCK_HSE[3-25MHZ]                                *
 *                                                                                *
 * ********************************************************************************/
void RCC_SYSTEM_CLOCK_HSE(){
	//RCC_CR&=~(0XFFFFFFFF);
	RCC_CR|=RCC_CR_HSEON;
	while(!(RCC_CR&RCC_CR_HSERDY));
	RCC_CR|=RCC_CR_HSEBYP;
	RCC_CFGR|=RCC_CFGR_SW_HSE;
	while(((RCC_CFGR & RCC_CFGR_SWS_HSE)!=(RCC_CFGR_SWS_HSE)));
}
void RCC_SYSTEM_CLOCK_HSIPLL_64MHZ(){
	RCC_CR|=RCC_CR_HSION;
    while (!(RCC_CR & RCC_CR_HSIRDY));
    RCC_CFGR&=~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLMUL17);
    RCC_CR|=RCC_CR_PLLON;
	while(!(RCC_CR & RCC_CR_PLLRDY));
	RCC_CFGR|=RCC_CFGR_SW_PLL;
	while(((RCC_CFGR & RCC_CFGR_SWS_MASK)!=(RCC_CFGR_SWS_PLL)));
}
void SYSTEM_CLOCK_TEST(){
    // Enable GPIOA clock
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure PA8 as Alternate Function Push-Pull, 50 MHz
    GPIOA_CRH &= ~GPIOA_CRH_MASK_PA8;
    GPIOA_CRH |= GPIOA_CRH_AF_PP_50MHz;

    // Select MCO = SYSCLK
    RCC_CFGR &= ~RCC_CFGR_MCO_MASK;
    RCC_CFGR |= RCC_CFGR_MCO_SYSCLK;
}
