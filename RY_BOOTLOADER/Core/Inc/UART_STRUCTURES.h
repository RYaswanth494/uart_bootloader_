/*
 * UART_STRUCTURES.h
 *
 *  Created on: Jul 12, 2025
 *      Author: maday
 */

#ifndef INC_UART_STRUCTURES_H_
#define INC_UART_STRUCTURES_H_

#include <stdint.h>

/* RY_USART Status Register (RY_USART_SR) */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t PE    :1;
        uint32_t FE    :1;
        uint32_t NE    :1;
        uint32_t ORE   :1;
        uint32_t IDLE  :1;
        uint32_t RXNE  :1;
        uint32_t TC    :1;
        uint32_t TXE   :1;
        uint32_t LBD   :1;
        uint32_t CTS   :1;
        uint32_t RESERVED :22;
    } BITS;
} RY_USART_SR_REG;

/* RY_USART Data Register (RY_USART_DR) */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t DR :9;
        uint32_t RESERVED :23;
    } BITS;
} RY_USART_DR_REG;

/* RY_USART Baud Rate Register (RY_USART_BRR) */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t DIV_Fraction :4;
        uint32_t DIV_Mantissa :12;
        uint32_t RESERVED     :16;
    } BITS;
} RY_USART_BRR_REG;

/* RY_USART Control Register 1 (RY_USART_CR1) */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t SBK     :1;
        uint32_t RWU     :1;
        uint32_t RE      :1;
        uint32_t TE      :1;
        uint32_t IDLEIE  :1;
        uint32_t RXNEIE  :1;
        uint32_t TCIE    :1;
        uint32_t TXEIE   :1;
        uint32_t PEIE    :1;
        uint32_t PS      :1;
        uint32_t PCE     :1;
        uint32_t WAKE    :1;
        uint32_t M       :1;
        uint32_t UE      :1;
        uint32_t RESERVED:18;
    } BITS;
} RY_USART_CR1_REG;

/* RY_USART Control Register 2 (RY_USART_CR2) */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t ADD      :4;
        uint32_t RESERVED1:1;
        uint32_t LBDL     :1;
        uint32_t LBDIE    :1;
        uint32_t RESERVED2:1;
        uint32_t LBCL     :1;
        uint32_t CPHA     :1;
        uint32_t CPOL     :1;
        uint32_t CLKEN    :1;
        uint32_t STOP     :2;
        uint32_t LINEN    :1;
        uint32_t RESERVED :17;
    } BITS;
} RY_USART_CR2_REG;

/* RY_USART Control Register 3 (RY_USART_CR3) */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t EIE     :1;
        uint32_t IREN    :1;
        uint32_t IRLP    :1;
        uint32_t HDSEL   :1;
        uint32_t NACK    :1;
        uint32_t SCEN    :1;
        uint32_t DMAR    :1;
        uint32_t DMAT    :1;
        uint32_t RTSE    :1;
        uint32_t CTSE    :1;
        uint32_t CTSIE   :1;
        uint32_t RESERVED:21;
    } BITS;
} RY_USART_CR3_REG;

/* RY_USART Guard Time and Prescaler Register (RY_USART_GTPR) */
typedef union {
    uint32_t ALL;
    struct {
        uint32_t PSC :8;
        uint32_t GT  :8;
        uint32_t RESERVED :16;
    } BITS;
} RY_USART_GTPR_REG;
typedef struct {
    RY_USART_SR_REG   SR;     // 0x00
    RY_USART_DR_REG   DR;     // 0x04
    RY_USART_BRR_REG  BRR;    // 0x08
    RY_USART_CR1_REG  CR1;    // 0x0C
    RY_USART_CR2_REG  CR2;    // 0x10
    RY_USART_CR3_REG  CR3;    // 0x14
    RY_USART_GTPR_REG GTPR;   // 0x18
} RY_USART_Register;

#define RY_USART1   ((volatile RY_USART_Register*)0x40013800)


#endif /* INC_UART_STRUCTURES_H_ */
