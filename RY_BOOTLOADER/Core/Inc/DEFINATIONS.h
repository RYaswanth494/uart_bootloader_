/*
 * DEFINATIONS.h
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */

#ifndef INC_DEFINATIONS_H_
#define INC_DEFINATIONS_H_

#define RCC_IOPBEN    (1 << 3)
#define PB2_OUTPUT_2MHZ_GP_PUSH_PULL  (0x2 << (2 * 4))


#define RCC_CR_HSION    (1<<0)   // Enable HSI
#define RCC_CR_HSIRDY   (1<<1)   // Bit 1: HSI ready flag
#define RCC_CR_HSEON    (1<<16)  // Bit 16: HSE enable
#define RCC_CR_HSERDY   (1 << 17)  // Bit 17: HSE ready flag
#define RCC_CR_PLLON    (1 << 24)  // Bit 24: PLL enable
#define RCC_CR_PLLRDY   (1 << 25)  // Bit 25: PLL ready flag
#define RCC_CR_HSEBYP   (1<<18)   //BIT 18: Osc bypassed with external clock


#define RCC_CFGR_SW_HSI    (0x0 << 0)  // SW: 00 = HSI selected as SYSCLK
#define RCC_CFGR_SW_MASK   (0x3 << 0)  // SW mask
#define RCC_CFGR_SWS_HSI   (0x0 << 2)  // SWS: 00 = HSI used as SYSCLK
#define RCC_CFGR_SWS_MASK  (0x3 << 2)  // SWS mask

#define RCC_CFGR_SW_HSE    (0X1<<0)    //SW:01=HSE selected as system clock
#define RCC_CFGR_SWS_HSE   (0X1<<2)    // SWS: 01 = HSE used as SYSCLK

#define RCC_CFGR_SW_PLL   (0X2<<0)
#define RCC_CFGR_SWS_PLL  (0X2<<2)
#define RCC_CFGR_PLLSRC   (0X1<<16)

// RCC_CFGR PLL Multiplier options (PLLMUL[21:18])
#define RCC_CFGR_PLLMUL2    (0x0U << 18)  // x2
#define RCC_CFGR_PLLMUL3    (0x1U << 18)  // x3
#define RCC_CFGR_PLLMUL4    (0x2U << 18)  // x4
#define RCC_CFGR_PLLMUL5    (0x3U << 18)  // x5
#define RCC_CFGR_PLLMUL6    (0x4U << 18)  // x6
#define RCC_CFGR_PLLMUL7    (0x5U << 18)  // x7
#define RCC_CFGR_PLLMUL8    (0x6U << 18)  // x8
#define RCC_CFGR_PLLMUL9    (0x7U << 18)  // x9
#define RCC_CFGR_PLLMUL10   (0x8U << 18)  // x10
#define RCC_CFGR_PLLMUL11   (0x9U << 18)  // x11
#define RCC_CFGR_PLLMUL12   (0xAU << 18)  // x12
#define RCC_CFGR_PLLMUL13   (0xBU << 18)  // x13
#define RCC_CFGR_PLLMUL14   (0xCU << 18)  // x14
#define RCC_CFGR_PLLMUL15   (0xDU << 18)  // x15
#define RCC_CFGR_PLLMUL16   (0xEU << 18)  // x16
#define RCC_CFGR_PLLMUL17    (0XFU<<18)    //X16


// RCC_CFGR MCO settings
#define RCC_CFGR_MCO_MASK       0x07000000
#define RCC_CFGR_MCO_SYSCLK     0x04000000  // MCO = SYSCLK

// RCC APB2 Peripheral Enable
#define RCC_APB2ENR_IOPAEN      0x00000004

#endif /* INC_DEFINATIONS_H_ */
