/*
 * RCC_CLOCK.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */


#include"RCC_STRUCTURES.h"
#include"FLASH_DEFINES.h"
#include"FLASH_STRUCTURES.h"
//#include"GPIO.h"
#include"main.h"
//#define RY_FLASH_ACR   (*(volatile uint32_t *)0x40022000)

extern void TOGGLE_LED();
/*********************************************************************************
 *                                                                                *
 *              FUNCTION_NAME:RCC_RY_SYSTEM_CLOCK_HSI[8MHZ]                                *
 *                                                                                *                                                            *
 * ********************************************************************************/
    // 1. Enable HSI
    // 2. Wait until HSI is ready
    // 3. Select HSI as system clock & Clear SW bits to select HSI
    // 4. Wait until HSI is confirmed as system clock
void RCC_SYSTEM_CLOCK_HSI(){
    // 1. Enable HSI
	RY_RCC->CR.BITS.HSION= 1;
    while (!(RY_RCC->CR.BITS.HSIRDY));   // Wait for HSI ready

    // 2. Set RY_FLASH latency = 0 wait states (≤24MHz)
   // RY_FLASH-> &= ~0x7;
   // RY_FLASH_ACR |= 0x0;

    // 3. Select HSI as system clock
    RY_RCC->CFGR.BITS.SW = 0b00;       // SYSCLK = HSI
    while (RY_RCC->CFGR.BITS.SWS != 0b00);  // Wait till HSI used
}
/*********************************************************************************
 *                                                                                *
 *              FUNCTION_NAME:RCC_RY_SYSTEM_CLOCK_HSE[3-25MHZ]                                *
 *                                                                                *
 * ********************************************************************************/
void RCC_SYSTEM_CLOCK_HSE(){
    // 1. Enable HSE
	RY_RCC->CR.BITS.HSEON = 1;
    while (!RY_RCC->CR.BITS.HSERDY);   // Wait for HSE ready

    // 2. Set RY_FLASH latency = 0 wait states (≤24MHz)
    //RY_FLASH_ACR &= ~0x7;
    //RY_FLASH_ACR |= 0x0;

    // 3. Select HSE as system clock
    RY_RCC->CFGR.BITS.SW = 0b01;       // SYSCLK = HSE
    while (RY_RCC->CFGR.BITS.SWS != 0b01);  // Wait till HSE used
}/*
void RCC_SYSTEM_CLOCK_HSIPLL_64MHZ(){
    // 1. Enable HSI
	RY_RCC->CRbits.HSION = 1;
    while (!RCC_RY->CRbits.HSIRDY);

    // 2. Set 2 wait states in RY_FLASH for >48 MHz
  //  RY_FLASH_ACR &= ~(0x7);  // Clear latency
  //  RY_FLASH_ACR |= 0x2;     // 2 wait states

    // 3. Configure PLL (HSI/2 * 16 = 64 MHz)
    RY_RCC->CFGRbits.PLLSRC = 0;        // HSI/2
    RY_RCC->CFGRbits.PLLMULL = 0b0110;  // x16 (0b0110 means x16)

    // 4. Enable PLL
    RY_RCC->CRbits.PLLON = 1;
    while (!RY_RCC->CRbits.PLLRDY);

    // 5. Select PLL as system clock
    RY_RCC->CFGRbits.SW = 0b10;
    while (RY_RCC->CFGRbits.SWS != 0b10);
}*/
void RCC_SYSTEM_CLOCK_HSEPLL_72MHZ(){
//    // 1. Enable HSE
	RCC_SYSTEM_CLOCK_HSE();
////    // 2. Set 2 wait states in RY_FLASH for >48 MHz
////    RY_FLASH_ACR |= 0x2;


	// 1. Enable HSE
//	RCC->CR |= RCC_CR_HSEON;
//	while (!(RCC->CR & RCC_CR_HSERDY));  // Wait for HSE ready

	RY_FLASH->RY_ACR.RY_ALL &= ~0x07;         // Clear LATENCY (3 bits)
	RY_FLASH->RY_ACR.RY_ALL |= (2 << 0);      // Set 2 wait states
	RY_FLASH->RY_ACR.RY_ALL |= (1 << 4);      // Enable prefetch (PRFTBE)


   // 3. Configure PLL (HSE * 9 = 72 MHz)
	    RY_RCC->CFGR.BITS.PLLSRC = 1;         // HSE
	    RY_RCC->CFGR.BITS.PLLMULL = 0b0111;   // x9 (0b0111 = x9)
	// 4. Enable PLL
	  RY_RCC->CR.BITS.PLLON = 1;
	 while (!RY_RCC->CR.BITS.PLLRDY);
	// 5. Switch SYSCLK to PLL
	 RY_RCC->CFGR.BITS.SW = 0b10;
	 while (RY_RCC->CFGR.BITS.SWS != 0b10);

}
uint32_t GetSystemClockHz(void)
{
    uint32_t sysclk = 0;

    switch (RY_RCC->CFGR.BITS.SWS)
    {
        case 0x00: // HSI used as system clock
            sysclk = HSI_VALUE;
            break;

        case 0x01: // HSE used as system clock
            sysclk = HSE_VALUE;
            break;

        case 0x02: // PLL used as system clock
        {
            uint32_t pllmul = RY_RCC->CFGR.BITS.PLLMULL + 2;
            if (pllmul == 17) pllmul = 16;  // 0xF means x16

            if (RY_RCC->CFGR.BITS.PLLSRC == 0)
            {
                // PLL source is HSI / 2
                sysclk = (HSI_VALUE / 2) * pllmul;
            }
            else
            {
                // PLL source is HSE or HSE/2
                uint32_t hse_input = (RY_RCC->CFGR.BITS.PLLXTPRE) ? (HSE_VALUE / 2) : HSE_VALUE;
                sysclk = hse_input * pllmul;
            }
            break;
        }

        default: // Invalid
            sysclk = 0;
            break;
    }

    return sysclk;
}

//void SYSTEM_CLOCK_TEST(){
//    // Enable GPIOA clock
//    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
//    // Set 2 wait states for 64 MHz
//    RY_FLASH_ACR &= ~RY_FLASH_ACR_LATENCY_MASK;
//    RY_FLASH_ACR |= RY_FLASH_ACR_LATENCY_2;
//    // Configure PA8 as Alternate Function Push-Pull, 50 MHz
//    GPIOA_CRH &= ~GPIOA_CRH_MASK_PA8;
//    GPIOA_CRH |= GPIOA_CRH_AF_PP_50MHz;
//    // Select MCO = SYSCLK
//    RCC_CFGR &= ~RCC_CFGR_MCO_MASK;
//    RCC_CFGR |= RCC_CFGR_MCO_SYSCLK;*/
//}
