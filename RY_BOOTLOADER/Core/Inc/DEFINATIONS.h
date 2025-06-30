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


#endif /* INC_DEFINATIONS_H_ */
