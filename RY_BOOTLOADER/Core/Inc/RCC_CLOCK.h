/*
 * RCC_CLOCK.h
 *
 *  Created on: Jun 26, 2025
 *      Author: maday
 */

#ifndef INC_RCC_CLOCK_H_
#define INC_RCC_CLOCK_H_

#define RESET_CLOCK_CONTROL_BASE_ADDRESS  0x40021000

#define RCC_CR         (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x00)
#define RCC_CFGR       (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x04)
#define RCC_CIR        (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x08)
#define RCC_APB2RSTR   (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x0C)
#define RCC_APB1RSTR   (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x10)
#define RCC_AHBENR     (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x14)
#define RCC_APB2ENR    (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x18)
#define RCC_APB1ENR    (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x1C)
#define RCC_BDCR       (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x20)
#define RCC_CSR        (volatile uint32_t *)(RESET_CLOCK_CONTROL_BASE_ADDRESS+0x24)

#endif /* INC_RCC_CLOCK_H_ */
