/*
 * GPIO_STRUCTURES.h
 *
 *  Created on: Jul 16, 2025
 *      Author: maday
 */

#ifndef INC_GPIO_STRUCTURES_H_
#define INC_GPIO_STRUCTURES_H_

#include <stdint.h>

#define GPIO_BASE_A ((volatile uint32_t *)0x40010800)
#define GPIO_BASE_B ((volatile uint32_t *)0x40010C00)
#define GPIO_BASE_C ((volatile uint32_t *)0x40011000 )


typedef struct {
    volatile uint32_t MODE : 2;
    volatile uint32_t CNF  : 2;
} GPIO_PinConfigBits;

// CRL and CRH combined as union
typedef union {
    volatile uint32_t REG;
    struct {
        GPIO_PinConfigBits PIN[8];
    } BITS;
} GPIO_CRx;
typedef union {
    volatile uint32_t ALL;
    struct {
        volatile uint32_t IDR0  : 1;
        volatile uint32_t IDR1  : 1;
        volatile uint32_t IDR2  : 1;
        volatile uint32_t IDR3  : 1;
        volatile uint32_t IDR4  : 1;
        volatile uint32_t IDR5  : 1;
        volatile uint32_t IDR6  : 1;
        volatile uint32_t IDR7  : 1;
        volatile uint32_t IDR8  : 1;
        volatile uint32_t IDR9  : 1;
        volatile uint32_t IDR10 : 1;
        volatile uint32_t IDR11 : 1;
        volatile uint32_t IDR12 : 1;
        volatile uint32_t IDR13 : 1;
        volatile uint32_t IDR14 : 1;
        volatile uint32_t IDR15 : 1;
        uint32_t RESERVED       : 16;
    } BITS;
} GPIO_IDR_t;

typedef union {
    volatile uint32_t ALL;
    struct {
        volatile uint32_t ODR0  : 1;
        volatile uint32_t ODR1  : 1;
        volatile uint32_t ODR2  : 1;
        volatile uint32_t ODR3  : 1;
        volatile uint32_t ODR4  : 1;
        volatile uint32_t ODR5  : 1;
        volatile uint32_t ODR6  : 1;
        volatile uint32_t ODR7  : 1;
        volatile uint32_t ODR8  : 1;
        volatile uint32_t ODR9  : 1;
        volatile uint32_t ODR10 : 1;
        volatile uint32_t ODR11 : 1;
        volatile uint32_t ODR12 : 1;
        volatile uint32_t ODR13 : 1;
        volatile uint32_t ODR14 : 1;
        volatile uint32_t ODR15 : 1;
        uint32_t RESERVED       : 16;
    } BITS;
} GPIO_ODR_t;

typedef struct {
    GPIO_CRx CRL;
    GPIO_CRx CRH;
    GPIO_IDR_t IDR;
    GPIO_ODR_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

#define GPIOA ((volatile GPIO_TypeDef*)GPIO_BASE_A)
#define GPIOA ((volatile GPIO_TypeDef*)GPIO_BASE_B)
#define GPIOA ((volatile GPIO_TypeDef*)GPIO_BASE_C)


#endif /* INC_GPIO_STRUCTURES_H_ */
