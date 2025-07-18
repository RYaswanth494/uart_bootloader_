/*
 * RCC_STRUCTURES.h
 *
 *  Created on: Jul 5, 2025
 *      Author: maday
 */

#ifndef INC_RCC_STRUCTURES_H_
#define INC_RCC_STRUCTURES_H_

#include <stdint.h>

/* RCC_CR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t HSION     :1;
        uint32_t HSIRDY    :1;
        uint32_t RESERVED0 :1;
        uint32_t HSITRIM   :5;
        uint32_t HSICAL    :8;
        uint32_t HSEON     :1;
        uint32_t HSERDY    :1;
        uint32_t HSEBYP    :1;
        uint32_t CSSON     :1;
        uint32_t RESERVED1 :4;
        uint32_t PLLON     :1;
        uint32_t PLLRDY    :1;
        uint32_t RESERVED2 :6;
    } BITS;
} RY_RCC_CR_REG;

/* RCC_CFGR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t SW        :2;
        uint32_t SWS       :2;
        uint32_t HPRE      :4;
        uint32_t PPRE1     :3;
        uint32_t PPRE2     :3;
        uint32_t ADCPRE    :2;
        uint32_t PLLSRC    :1;
        uint32_t PLLXTPRE  :1;
        uint32_t PLLMULL   :4;
        uint32_t USBPRE    :1;
        uint32_t RESERVED1 :1;
        uint32_t MCO       :3;
        uint32_t RESERVED2 :5;
    } BITS;
} RY_RCC_CFGR_REG;

/* RCC_CIR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t LSIRDYF   :1;
        uint32_t LSERDYF   :1;
        uint32_t HSIRDYF   :1;
        uint32_t HSERDYF   :1;
        uint32_t PLLRDYF   :1;
        uint32_t CSSF      :1;
        uint32_t RESERVED0 :2;
        uint32_t LSIRDYIE  :1;
        uint32_t LSERDYIE  :1;
        uint32_t HSIRDYIE  :1;
        uint32_t HSERDYIE  :1;
        uint32_t PLLRDYIE  :1;
        uint32_t RESERVED1 :3;
        uint32_t LSIRDYC   :1;
        uint32_t LSERDYC   :1;
        uint32_t HSIRDYC   :1;
        uint32_t HSERDYC   :1;
        uint32_t PLLRDYC   :1;
        uint32_t CSSC      :1;
        uint32_t RESERVED2 :10;
    } BITS;
} RY_RCC_CIR_REG;

/* RCC_APB2RSTR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t AFIORST   :1;
        uint32_t RESERVED0 :1;
        uint32_t IOPARST   :1;
        uint32_t IOPBRST   :1;
        uint32_t IOPCRST   :1;
        uint32_t IOPDRST   :1;
        uint32_t IOFERST   :1;
        uint32_t IOPFRST   :1;
        uint32_t IOPGRST   :1;
        uint32_t ADC1RST   :1;
        uint32_t ADC2RST   :1;
        uint32_t TIM1RST   :1;
        uint32_t SPI1RST   :1;
        uint32_t TIM8RST   :1;
        uint32_t USART1RST :1;
        uint32_t ADC3RST   :1;
        uint32_t RESERVED1 :16;
    } BITS;
} RY_RCC_APB2RSTR_REG;

/* RCC_APB1RSTR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t TIM2RST   :1;
        uint32_t TIM3RST   :1;
        uint32_t TIM4RST   :1;
        uint32_t TIM5RST   :1;
        uint32_t TIM6RST   :1;
        uint32_t TIM7RST   :1;
        uint32_t TIM12RST  :1;
        uint32_t TIM13RST  :1;
        uint32_t TIM14RST  :1;
        uint32_t RESERVED0 :2;
        uint32_t WWDGRST   :1;
        uint32_t RESERVED1 :2;
        uint32_t SPI2RST   :1;
        uint32_t SPI3RST   :1;
        uint32_t RESERVED2 :1;
        uint32_t USART2RST :1;
        uint32_t USART3RST :1;
        uint32_t UART4RST  :1;
        uint32_t UART5RST  :1;
        uint32_t I2C1RST   :1;
        uint32_t I2C2RST   :1;
        uint32_t USBRST    :1;
        uint32_t RESERVED3 :1;
        uint32_t CANRST    :1;
        uint32_t RESERVED4 :1;
        uint32_t BKPRST    :1;
        uint32_t PWRRST    :1;
        uint32_t DACRST    :1;
        uint32_t RESERVED5 :2;
    } BITS;
} RY_RCC_APB1RSTR_REG;

/* RCC_AHBENR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t DMA1EN    :1;
        uint32_t DMA2EN    :1;
        uint32_t SRAMEN    :1;
        uint32_t RESERVED0 :1;
        uint32_t FLITFEN   :1;
        uint32_t RESERVED1 :1;
        uint32_t CRCEN     :1;
        uint32_t RESERVED2 :9;
        uint32_t FSMCEN    :1;
        uint32_t RESERVED3 :15;
    } BITS;
} RY_RCC_AHBENR_REG;

/* RCC_APB2ENR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t AFIOEN    :1;
        uint32_t RESERVED0 :1;
        uint32_t IOPAEN    :1;
        uint32_t IOPBEN    :1;
        uint32_t IOPCEN    :1;
        uint32_t IOPDEN    :1;
        uint32_t IOPEEN    :1;
        uint32_t IOPFEN    :1;
        uint32_t IOPGEN    :1;
        uint32_t ADC1EN    :1;
        uint32_t ADC2EN    :1;
        uint32_t TIM1EN    :1;
        uint32_t SPI1EN    :1;
        uint32_t TIM8EN    :1;
        uint32_t USART1EN  :1;
        uint32_t ADC3EN    :1;
        uint32_t RESERVED1 :16;
    } BITS;
} RY_RCC_APB2ENR_REG;

/* RCC_APB1ENR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t TIM2EN    :1;
        uint32_t TIM3EN    :1;
        uint32_t TIM4EN    :1;
        uint32_t TIM5EN    :1;
        uint32_t TIM6EN    :1;
        uint32_t TIM7EN    :1;
        uint32_t TIM12EN   :1;
        uint32_t TIM13EN   :1;
        uint32_t TIM14EN   :1;
        uint32_t RESERVED0 :2;
        uint32_t WWDGEN    :1;
        uint32_t RESERVED1 :2;
        uint32_t SPI2EN    :1;
        uint32_t SPI3EN    :1;
        uint32_t RESERVED2 :1;
        uint32_t USART2EN  :1;
        uint32_t USART3EN  :1;
        uint32_t UART4EN   :1;
        uint32_t UART5EN   :1;
        uint32_t I2C1EN    :1;
        uint32_t I2C2EN    :1;
        uint32_t USBEN     :1;
        uint32_t RESERVED3 :1;
        uint32_t CANEN     :1;
        uint32_t RESERVED4 :1;
        uint32_t BKPEN     :1;
        uint32_t PWREN     :1;
        uint32_t DACEN     :1;
        uint32_t RESERVED5 :2;
    } BITS;
} RY_RCC_APB1ENR_REG;

/* RCC_BDCR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t LSEON     :1;
        uint32_t LSERDY    :1;
        uint32_t LSEBYP    :1;
        uint32_t RESERVED0 :5;
        uint32_t RTCSEL    :2;
        uint32_t RESERVED1 :5;
        uint32_t RTCEN     :1;
        uint32_t BDRST     :1;
        uint32_t RESERVED2 :16;
    } BITS;
} RY_RCC_BDCR_REG;

/* RCC_CSR Register */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t LSION     :1;
        uint32_t LSIRDY    :1;
        uint32_t RESERVED0 :22;
        uint32_t RMVF      :1;
        uint32_t PINRSTF   :1;
        uint32_t PORRSTF   :1;
        uint32_t SFTRSTF   :1;
        uint32_t IWDGRSTF  :1;
        uint32_t WWDGRSTF  :1;
        uint32_t LPWRRSTF  :1;
        uint32_t RESERVED1 :2;
    } BITS;
} RY_RCC_CSR_REG;

/* RCC Register Structure */
typedef struct {
    RY_RCC_CR_REG        CR;        // 0x00
    RY_RCC_CFGR_REG      CFGR;      // 0x04
    RY_RCC_CIR_REG       CIR;       // 0x08
    RY_RCC_APB2RSTR_REG  APB2RSTR;  // 0x0C
    RY_RCC_APB1RSTR_REG  APB1RSTR;  // 0x10
    RY_RCC_AHBENR_REG    AHBENR;    // 0x14
    RY_RCC_APB2ENR_REG   APB2ENR;   // 0x18
    RY_RCC_APB1ENR_REG   APB1ENR;   // 0x1C
    RY_RCC_BDCR_REG      BDCR;      // 0x20
    RY_RCC_CSR_REG       CSR;       // 0x24
} RY_RCC_Register;

#define RY_RCC  ((volatile RY_RCC_Register*) 0x40021000)

#endif /* INC_RCC_STRUCTURES_H_ */
