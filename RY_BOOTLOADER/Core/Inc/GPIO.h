/*
 * GPIO.h
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */

#ifndef GPIO_H_
#define GPIO_H_


#define GPIOA_BASE      0x40010800
#define GPIOA_CRH       (*(volatile uint32_t *)(GPIOA_BASE + 0x04))



// GPIOA CRH settings for PA8 (bits 3:0)
#define GPIOA_CRH_MASK_PA8      0x0000000F
#define GPIOA_CRH_AF_PP_50MHz   0x0000000B  // MODE = 11, CNF = 10 → 0b1011

#define GPIOB_CRL     (*(volatile unsigned int*)0x40010C00)
#define GPIOB_ODR     (*(volatile unsigned int*)0x40010C0C)


#endif /* GPIO_H_ */
