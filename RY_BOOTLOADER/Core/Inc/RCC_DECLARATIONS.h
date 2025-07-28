/*
 * RCC_DECLARATIONS.h
 *
 *  Created on: Jun 30, 2025
 *      Author: maday
 */

#ifndef INC_RCC_DECLARATIONS_H_
#define INC_RCC_DECLARATIONS_H_

void RCC_SYSTEM_CLOCK_HSI();
void RCC_SYSTEM_CLOCK_HSE();
void RCC_SYSTEM_CLOCK_HSIPLL_64MHZ();
void RCC_SYSTEM_CLOCK_HSEPLL_72MHZ();
void SYSTEM_CLOCK_TEST();
uint32_t GetSystemClockHz(void);
#endif /* INC_RCC_DECLARATIONS_H_ */
