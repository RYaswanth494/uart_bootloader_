/*
 * RCC_STRUCTURES.h
 *
 *  Created on: Jul 5, 2025
 *      Author: maday
 */

#ifndef INC_RCC_STRUCTURES_H_
#define INC_RCC_STRUCTURES_H_
//--------------------------------------
// RCC_CR register bitfield structure
//--------------------------------------
typedef struct {
    volatile uint32_t HSION     :1;  // Bit 0: HSI enable
    volatile uint32_t HSIRDY    :1;  // Bit 1: HSI ready
    volatile uint32_t RESERVED0 :1;  // Bit 2: Reserved
    volatile uint32_t HSITRIM   :5;  // Bits 3–7: HSI trimming
    volatile uint32_t HSICAL    :8;  // Bits 8–15: HSI calibration
    volatile uint32_t HSEON     :1;  // Bit 16: HSE enable
    volatile uint32_t HSERDY    :1;  // Bit 17: HSE ready
    volatile uint32_t HSEBYP    :1;  // Bit 18: HSE bypass
    volatile uint32_t CSSON     :1;  // Bit 19: Clock security system enable
    volatile uint32_t RESERVED1 :4;  // Bits 20–23: Reserved
    volatile uint32_t PLLON     :1;  // Bit 24: PLL enable
    volatile uint32_t PLLRDY    :1;  // Bit 25: PLL ready
    volatile uint32_t RESERVED2 :6;  // Bits 26–31: Reserved
} RCC_CR_bits;


//--------------------------------------
// RCC_CFGR register bitfield structure
//--------------------------------------
typedef struct {
    volatile uint32_t SW        :2;  // Bits 0–1: System clock switch
    volatile uint32_t SWS       :2;  // Bits 2–3: System clock switch status
    volatile uint32_t HPRE      :4;  // Bits 4–7: AHB prescaler
    volatile uint32_t PPRE1     :3;  // Bits 8–10: APB1 prescaler
    volatile uint32_t PPRE2     :3;  // Bits 11–13: APB2 prescaler
    volatile uint32_t ADCPRE    :2;  // Bits 14–15: ADC prescaler
    volatile uint32_t PLLSRC    :1;  // Bit 16: PLL clock source
    volatile uint32_t PLLXTPRE  :1;  // Bit 17: HSE divider for PLL entry
    volatile uint32_t PLLMULL   :4;  // Bits 18–21: PLL multiplication factor
    volatile uint32_t USBPRE    :1;  // Bit 22: USB prescaler
    volatile uint32_t RESERVED1 :1;  // Bit 23: Reserved
    volatile uint32_t MCO       :3;  // Bits 24–26: MCO output
    volatile uint32_t RESERVED2 :5;  // Bits 27–31: Reserved
} RCC_CFGR_bits;
typedef struct {
    volatile uint32_t LSIRDYF   :1;
    volatile uint32_t LSERDYF   :1;
    volatile uint32_t HSIRDYF   :1;
    volatile uint32_t HSERDYF   :1;
    volatile uint32_t PLLRDYF   :1;
    volatile uint32_t CSSF      :1;
    volatile uint32_t RESERVED0 :2;
    volatile uint32_t LSIRDYIE  :1;
    volatile uint32_t LSERDYIE  :1;
    volatile uint32_t HSIRDYIE  :1;
    volatile uint32_t HSERDYIE  :1;
    volatile uint32_t PLLRDYIE  :1;
    volatile uint32_t RESERVED1 :3;
    volatile uint32_t LSIRDYC   :1;
    volatile uint32_t LSERDYC   :1;
    volatile uint32_t HSIRDYC   :1;
    volatile uint32_t HSERDYC   :1;
    volatile uint32_t PLLRDYC   :1;
    volatile uint32_t CSSC      :1;
    volatile uint32_t RESERVED2 :10;
} RCC_CIR_bits;
typedef struct {
    volatile uint32_t AFIORST   :1;
    volatile uint32_t RESERVED0 :1;
    volatile uint32_t IOPARST   :1;
    volatile uint32_t IOPBRST   :1;
    volatile uint32_t IOPCRST   :1;
    volatile uint32_t IOPDRST   :1;
    volatile uint32_t IOFERST   :1;
    volatile uint32_t IOPFRST   :1;
    volatile uint32_t IOPGRST   :1;
    volatile uint32_t ADC1RST   :1;
    volatile uint32_t ADC2RST   :1;
    volatile uint32_t TIM1RST   :1;
    volatile uint32_t SPI1RST   :1;
    volatile uint32_t TIM8RST   :1;
    volatile uint32_t USART1RST :1;
    volatile uint32_t ADC3RST   :1;
    volatile uint32_t RESERVED1 :16;
} RCC_APB2RSTR_bits;

typedef struct {
    volatile uint32_t TIM2RST   :1;
    volatile uint32_t TIM3RST   :1;
    volatile uint32_t TIM4RST   :1;
    volatile uint32_t TIM5RST   :1;
    volatile uint32_t TIM6RST   :1;
    volatile uint32_t TIM7RST   :1;
    volatile uint32_t TIM12RST  :1;
    volatile uint32_t TIM13RST  :1;
    volatile uint32_t TIM14RST  :1;
    volatile uint32_t RESERVED0 :2;
    volatile uint32_t WWDGRST   :1;
    volatile uint32_t RESERVED1 :2;
    volatile uint32_t SPI2RST   :1;
    volatile uint32_t SPI3RST   :1;
    volatile uint32_t RESERVED2 :1;
    volatile uint32_t USART2RST :1;
    volatile uint32_t USART3RST :1;
    volatile uint32_t UART4RST  :1;
    volatile uint32_t UART5RST  :1;
    volatile uint32_t I2C1RST   :1;
    volatile uint32_t I2C2RST   :1;
    volatile uint32_t USBRST    :1;
    volatile uint32_t RESERVED3 :1;
    volatile uint32_t CANRST    :1;
    volatile uint32_t RESERVED4 :1;
    volatile uint32_t BKPRST    :1;
    volatile uint32_t PWRRST    :1;
    volatile uint32_t DACRST    :1;
    volatile uint32_t RESERVED5 :2;
} RCC_APB1RSTR_bits;
typedef struct {
    volatile uint32_t DMA1EN    :1;
    volatile uint32_t DMA2EN    :1;
    volatile uint32_t SRAMEN    :1;
    volatile uint32_t RESERVED0 :1;
    volatile uint32_t FLITFEN   :1;
    volatile uint32_t RESERVED1 :1;
    volatile uint32_t CRCEN     :1;
    volatile uint32_t RESERVED2 :9;
    volatile uint32_t FSMCEN    :1;
    volatile uint32_t RESERVED3 :15;
} RCC_AHBENR_bits;
typedef struct {
    volatile uint32_t AFIOEN    :1;
    volatile uint32_t RESERVED0 :1;
    volatile uint32_t IOPAEN    :1;
    volatile uint32_t IOPBEN    :1;
    volatile uint32_t IOPCEN    :1;
    volatile uint32_t IOPDEN    :1;
    volatile uint32_t IOPEEN    :1;
    volatile uint32_t IOPFEN    :1;
    volatile uint32_t IOPGEN    :1;
    volatile uint32_t ADC1EN    :1;
    volatile uint32_t ADC2EN    :1;
    volatile uint32_t TIM1EN    :1;
    volatile uint32_t SPI1EN    :1;
    volatile uint32_t TIM8EN    :1;
    volatile uint32_t USART1EN  :1;
    volatile uint32_t ADC3EN    :1;
    volatile uint32_t RESERVED1 :16;
} RCC_APB2ENR_bits;
typedef struct {
    volatile uint32_t TIM2EN    :1;
    volatile uint32_t TIM3EN    :1;
    volatile uint32_t TIM4EN    :1;
    volatile uint32_t TIM5EN    :1;
    volatile uint32_t TIM6EN    :1;
    volatile uint32_t TIM7EN    :1;
    volatile uint32_t TIM12EN   :1;
    volatile uint32_t TIM13EN   :1;
    volatile uint32_t TIM14EN   :1;
    volatile uint32_t RESERVED0 :2;
    volatile uint32_t WWDGEN    :1;
    volatile uint32_t RESERVED1 :2;
    volatile uint32_t SPI2EN    :1;
    volatile uint32_t SPI3EN    :1;
    volatile uint32_t RESERVED2 :1;
    volatile uint32_t USART2EN  :1;
    volatile uint32_t USART3EN  :1;
    volatile uint32_t UART4EN   :1;
    volatile uint32_t UART5EN   :1;
    volatile uint32_t I2C1EN    :1;
    volatile uint32_t I2C2EN    :1;
    volatile uint32_t USBEN     :1;
    volatile uint32_t RESERVED3 :1;
    volatile uint32_t CANEN     :1;
    volatile uint32_t RESERVED4 :1;
    volatile uint32_t BKPEN     :1;
    volatile uint32_t PWREN     :1;
    volatile uint32_t DACEN     :1;
    volatile uint32_t RESERVED5 :2;
} RCC_APB1ENR_bits;
typedef struct {
    volatile uint32_t LSEON     :1;
    volatile uint32_t LSERDY    :1;
    volatile uint32_t LSEBYP    :1;
    volatile uint32_t RESERVED0 :5;
    volatile uint32_t RTCSEL    :2;
    volatile uint32_t RESERVED1 :5;
    volatile uint32_t RTCEN     :1;
    volatile uint32_t BDRST     :1;
    volatile uint32_t RESERVED2 :16;
} RCC_BDCR_bits;
typedef struct {
    volatile uint32_t LSION     :1;
    volatile uint32_t LSIRDY    :1;
    volatile uint32_t RESERVED0 :22;
    volatile uint32_t RMVF      :1;
    volatile uint32_t PINRSTF   :1;
    volatile uint32_t PORRSTF   :1;
    volatile uint32_t SFTRSTF   :1;
    volatile uint32_t IWDGRSTF  :1;
    volatile uint32_t WWDGRSTF  :1;
    volatile uint32_t LPWRRSTF  :1;
    volatile uint32_t RESERVED1 :2;
} RCC_CSR_bits;

//------------------- Full RCC Structure -------------------
typedef struct {
    union {
    	volatile uint32_t CR;
    	RCC_CR_bits    CRbits;
    };
    union {
    	volatile uint32_t CFGR;
    	RCC_CFGR_bits  CFGRbits;
    };
    union {
    	volatile uint32_t CIR;
    	RCC_CIR_bits   CIRbits;
    };
    union {
    	volatile uint32_t APB2RSTR;
    	RCC_APB2RSTR_bits APB2RSTRbits;
    };
    union {
    	volatile uint32_t APB1RSTR;
    	RCC_APB1RSTR_bits APB1RSTRbits;
    };
    union {
    	volatile uint32_t AHBENR;
    	RCC_AHBENR_bits   AHBENRbits;
    };
    union {
    	volatile uint32_t APB2ENR;
    	RCC_APB2ENR_bits  APB2ENRbits;
    };
    union {
    	volatile uint32_t APB1ENR;
    	RCC_APB1ENR_bits  APB1ENRbits;
    };
    union {
    	volatile uint32_t BDCR;
    	RCC_BDCR_bits     BDCRbits;
    };
    union {
    	volatile uint32_t CSR;
    	RCC_CSR_bits      CSRbits;
    };
} RCC_RY_TYPEDEF;
#endif /* INC_RCC_STRUCTURES_H_ */
