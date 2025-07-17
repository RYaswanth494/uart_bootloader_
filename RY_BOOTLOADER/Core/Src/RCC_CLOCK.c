/*
 * RCC_CLOCK.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */


#include"RCC_CLOCK_DEFINES.h"
#include"FLASH_DEFINES.h"
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
    RCC_RY->CRbits.HSION = 1;
    while (!RCC_RY->CRbits.HSIRDY);   // Wait for HSI ready

    // 2. Set RY_FLASH latency = 0 wait states (≤24MHz)
   // RY_FLASH-> &= ~0x7;
   // RY_FLASH_ACR |= 0x0;

    // 3. Select HSI as system clock
    RCC_RY->CFGRbits.SW = 0b00;       // SYSCLK = HSI
    while (RCC_RY->CFGRbits.SWS != 0b00);  // Wait till HSI used
}
/*********************************************************************************
 *                                                                                *
 *              FUNCTION_NAME:RCC_RY_SYSTEM_CLOCK_HSE[3-25MHZ]                                *
 *                                                                                *
 * ********************************************************************************/
void RCC_SYSTEM_CLOCK_HSE(){
    // 1. Enable HSE
    RCC_RY->CRbits.HSEON = 1;
    while (!RCC_RY->CRbits.HSERDY);   // Wait for HSE ready

    // 2. Set RY_FLASH latency = 0 wait states (≤24MHz)
    //RY_FLASH_ACR &= ~0x7;
    //RY_FLASH_ACR |= 0x0;

    // 3. Select HSE as system clock
    RCC_RY->CFGRbits.SW = 0b01;       // SYSCLK = HSE
    while (RCC_RY->CFGRbits.SWS != 0b01);  // Wait till HSE used
}
void RCC_SYSTEM_CLOCK_HSIPLL_64MHZ(){
    // 1. Enable HSI
    RCC_RY->CRbits.HSION = 1;
    while (!RCC_RY->CRbits.HSIRDY);

    // 2. Set 2 wait states in RY_FLASH for >48 MHz
  //  RY_FLASH_ACR &= ~(0x7);  // Clear latency
  //  RY_FLASH_ACR |= 0x2;     // 2 wait states

    // 3. Configure PLL (HSI/2 * 16 = 64 MHz)
    RCC_RY->CFGRbits.PLLSRC = 0;        // HSI/2
    RCC_RY->CFGRbits.PLLMULL = 0b0110;  // x16 (0b0110 means x16)

    // 4. Enable PLL
    RCC_RY->CRbits.PLLON = 1;
    while (!RCC_RY->CRbits.PLLRDY);

    // 5. Select PLL as system clock
    RCC_RY->CFGRbits.SW = 0b10;
    while (RCC_RY->CFGRbits.SWS != 0b10);
}
void RCC_SYSTEM_CLOCK_HSEPLL_72MHZ(){
//    // 1. Enable HSE
//    RCC_RY->CRbits.HSEON = 1;
//    while (!RCC_RY->CRbits.HSERDY);
//
//    // 2. Set 2 wait states in RY_FLASH for >48 MHz
//    RY_FLASH_ACR &= ~(0x7);
//    RY_FLASH_ACR |= 0x2;
//
//    // 3. Configure PLL (HSE * 9 = 72 MHz)
//    RCC_RY->CFGRbits.PLLSRC = 1;         // HSE
//    RCC_RY->CFGRbits.PLLXTPRE = 0;       // No division
//    RCC_RY->CFGRbits.PLLMULL = 0b0111;   // x9 (0b0111 = x9)
//
//    // 4. Enable PLL
//    RCC_RY->CRbits.PLLON = 1;
//    while (!RCC_RY->CRbits.PLLRDY);
//
//    // 5. Switch system clock to PLL
//    RCC_RY->CFGRbits.SW = 0b10;
//    while (RCC_RY->CFGRbits.SWS != 0b10);
    // 1. Enable HSE (external 8 MHz)
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY)); // Wait until HSE is ready

    // 2. Configure PLL: PLLCLK = HSE * 9 = 72 MHz
    RCC->CFGR &= ~RCC_CFGR_PLLSRC; // Clear PLLSRC
    RCC->CFGR |= RCC_CFGR_PLLSRC;  // 1: HSE oscillator clock selected as PLL input
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;
    RCC->CFGR |= RCC_CFGR_PLLMULL9; // PLL MUL = 9

    // 3. Set AHB prescaler to 1, APB1 prescaler to 2 (max 36 MHz), APB2 prescaler to 1
    RCC->CFGR &= ~RCC_CFGR_HPRE;
    RCC->CFGR &= ~RCC_CFGR_PPRE1; RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 = HCLK/2
    RCC->CFGR &= ~RCC_CFGR_PPRE2; // APB2 = HCLK

    // 4. Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY)); // Wait until PLL is ready

    // 5. Select PLL as SYSCLK source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait for switch

    // 6. (Optional) Update SystemCoreClock variable if used
     SystemCoreClock = 72000000;
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
//    RCC_CFGR |= RCC_CFGR_MCO_SYSCLK;
//}
