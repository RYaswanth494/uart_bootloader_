/*
 * RCC_CLOCK.c
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */


#include"RCC_CLOCK_DEFINES.h"
#include"FLASH_DEFINES.h"
#include"DEFINATIONS.h"
#include"GPIO.h"
//#define FLASH_ACR   (*(volatile uint32_t *)0x40022000)

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

    // 2. Set FLASH latency = 0 wait states (≤24MHz)
    FLASH_ACR &= ~0x7;
    FLASH_ACR |= 0x0;

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

    // 2. Set FLASH latency = 0 wait states (≤24MHz)
    FLASH_ACR &= ~0x7;
    FLASH_ACR |= 0x0;

    // 3. Select HSE as system clock
    RCC_RY->CFGRbits.SW = 0b01;       // SYSCLK = HSE
    while (RCC_RY->CFGRbits.SWS != 0b01);  // Wait till HSE used
}
void RCC_SYSTEM_CLOCK_HSIPLL_64MHZ(){
    // 1. Enable HSI
    RCC_RY->CRbits.HSION = 1;
    while (!RCC_RY->CRbits.HSIRDY);

    // 2. Set 2 wait states in FLASH for >48 MHz
    FLASH_ACR &= ~(0x7);  // Clear latency
    FLASH_ACR |= 0x2;     // 2 wait states

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
    // 1. Enable HSE
    RCC_RY->CRbits.HSEON = 1;
    while (!RCC_RY->CRbits.HSERDY);

    // 2. Set 2 wait states in FLASH for >48 MHz
    FLASH_ACR &= ~(0x7);
    FLASH_ACR |= 0x2;

    // 3. Configure PLL (HSE * 9 = 72 MHz)
    RCC_RY->CFGRbits.PLLSRC = 1;         // HSE
    RCC_RY->CFGRbits.PLLXTPRE = 0;       // No division
    RCC_RY->CFGRbits.PLLMULL = 0b0111;   // x9 (0b0111 = x9)

    // 4. Enable PLL
    RCC_RY->CRbits.PLLON = 1;
    while (!RCC_RY->CRbits.PLLRDY);

    // 5. Switch system clock to PLL
    RCC_RY->CFGRbits.SW = 0b10;
    while (RCC_RY->CFGRbits.SWS != 0b10);
}
//void SYSTEM_CLOCK_TEST(){
//    // Enable GPIOA clock
//    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
//    // Set 2 wait states for 64 MHz
//    FLASH_ACR &= ~FLASH_ACR_LATENCY_MASK;
//    FLASH_ACR |= FLASH_ACR_LATENCY_2;
//    // Configure PA8 as Alternate Function Push-Pull, 50 MHz
//    GPIOA_CRH &= ~GPIOA_CRH_MASK_PA8;
//    GPIOA_CRH |= GPIOA_CRH_AF_PP_50MHz;
//    // Select MCO = SYSCLK
//    RCC_CFGR &= ~RCC_CFGR_MCO_MASK;
//    RCC_CFGR |= RCC_CFGR_MCO_SYSCLK;
//}
