/*
 * RCC_CLOCK.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */


#include"RCC_CLOCK_DEFINES.h"
#include"DEFINATIONS.h"
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
