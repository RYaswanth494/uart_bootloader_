/*
 * UART.c
 *
 *  Created on: Jul 11, 2025
 *      Author: maday
 */



// STM32F103C8T6 base addresses
// Union-based bitfield structures assumed already defined for RY_USART_Registers_t
 // ← your union/bit structure for RY_USART

// TX/RX buffers

#include<stdint.h>
#include"UART_DEFINES.h"
#include"UART_STRUCTURES.h"
//#include"main.h"
#define GPIOA_BASE      0x40010800
#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x18))
#define GPIOA_CRL       (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_CRH       (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define RCC_RY_USART1EN (1 << 14)

#define RCC_IOPAEN      (1 << 2)
volatile uint8_t tx_buffer[UART_TX_BUFFER_SIZE];
volatile uint16_t tx_head = 0, tx_tail = 0;
volatile uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
volatile uint16_t rx_head = 0, rx_tail = 0;

/* Internal: circular buffer push/pop */
 uint8_t TX_BufferEmpty(void) {
	return (tx_head == tx_tail);
}
 uint8_t RX_BufferEmpty(void) {
	return (rx_head == rx_tail);
}
 void TX_BufferPush(uint8_t data) {
    uint16_t next = (tx_head + 1) % UART_TX_BUFFER_SIZE;
    if (next != tx_tail) {
    	tx_buffer[tx_head] = data; tx_head = next;
    }
}
 void RX_BufferPush(uint8_t data) {
    uint16_t next = (rx_head + 1) % UART_RX_BUFFER_SIZE;
    if (next != rx_tail) {
    	rx_buffer[rx_head] = data; rx_head = next;
    }
}

/* ==== Function Implementations ==== */
 UART_Status_t SetBaudRate(uint32_t baudrate) {
    if (baudrate == 0) return UART_ERROR;
    uint32_t pclk = 8000000;
    uint32_t RY_USARTdiv = (pclk + (baudrate / 2)) / baudrate;
    RY_USART1->BRR.BITS.DIV_Mantissa = (RY_USARTdiv >> 4) & 0xFFF;
    RY_USART1->BRR.BITS.DIV_Fraction = RY_USARTdiv & 0xF;
    return UART_OK;
}
 UART_Status_t Init(uint32_t baudrate) {
    RCC_APB2ENR |= RCC_IOPAEN | RCC_RY_USART1EN;
    // PA9 = TX: AF Push-Pull
    GPIOA_CRH &= ~(0xF << 4);
    GPIOA_CRH |=  (0xB << 4); // MODE9=11, CNF9=10
    // PA10 = RX: Input Floating
    GPIOA_CRH &= ~(0xF << 8);
    GPIOA_CRH |=  (0x4 << 8); // MODE10=00, CNF10=01
    RY_USART1->CR1.ALL = 0;
    SetBaudRate(baudrate);
    RY_USART1->CR1.BITS.RE = 1;
    RY_USART1->CR1.BITS.TE = 1;
    RY_USART1->CR1.BITS.UE = 1;
    return UART_OK;
}
UART_Status_t SendByte(uint8_t byte) {
    while (!RY_USART1->SR.BITS.TXE);
    RY_USART1->DR.BITS.DR = byte;
    return UART_OK;
}

 UART_Status_t SendString(const char *str) {
    while (*str) {
        if (SendByte((uint8_t)(*str++)) != UART_OK)
            return UART_ERROR;
    }
    return UART_OK;
}


 UART_Status_t SendBytes(const uint8_t *data, uint16_t len) {
    while (len--) {
        if (SendByte(*data++) != UART_OK)
        	return UART_ERROR;
    }
    return UART_OK;
}

 UART_Status_t ReceiveByte(uint8_t *byte) {
    while (!RY_USART1->SR.BITS.RXNE);
    *byte = RY_USART1->DR.BITS.DR & 0xFF;
    return UART_OK;
}
 uint8_t uart_recv() {
    while (!RY_USART1->SR.BITS.RXNE);
    uint8_t byte = RY_USART1->DR.BITS.DR & 0xFF;
    return byte;
}
 UART_Status_t ReceiveByteTimeout(uint8_t *byte, uint32_t timeout_us) {
    while (!RY_USART1->SR.BITS.RXNE) {
        if (--timeout_us == 0) return UART_TIMEOUT;
    }
    *byte = RY_USART1->DR.BITS.DR & 0xFF;
    return UART_OK;
}

/* Non-blocking receive (RX FIFO) */
 UART_Status_t ReceiveByteAsync(uint8_t *byte) {
    if (RY_USART1->SR.BITS.RXNE)
        RX_BufferPush(RY_USART1->DR.BITS.DR);
    if (RX_BufferEmpty()) return UART_NO_DATA;
    *byte = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % UART_RX_BUFFER_SIZE;
    return UART_OK;
}

/* Non-blocking TX enqueue */
 UART_Status_t SendByteAsync(uint8_t byte) {
    uint16_t next = (tx_head + 1) % UART_TX_BUFFER_SIZE;
    if (next == tx_tail) return UART_BUSY;
    tx_buffer[tx_head] = byte;
    tx_head = next;
    return UART_OK;
}

 UART_Status_t SendBytesAsync(const uint8_t *data, uint16_t len) {
    while (len--) {
        if (SendByteAsync(*data++) != UART_OK) return UART_BUSY;
    }
    return UART_OK;
}

 UART_Status_t ProcessTX(void) {
    if (RY_USART1->SR.BITS.TXE && (tx_head != tx_tail)) {
    	RY_USART1->DR.BITS.DR = tx_buffer[tx_tail];
        tx_tail = (tx_tail + 1) % UART_TX_BUFFER_SIZE;
        return UART_OK;
    }
    return UART_NO_DATA;
}

 void FlushTX(void) {
	tx_head = tx_tail = 0;
}
 void FlushRX(void) {
	rx_head = rx_tail = 0;
}
 uint8_t TXBusy(void) {
	return (tx_head != tx_tail);
}
 uint8_t RXAvailable(void) {
	return (rx_head != rx_tail);
}

 UART_Status_t CheckErrors(void) {

    uint32_t flags = *(volatile uint32_t*)&RY_USART1->SR;
    if (flags & ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3)))
        return UART_ERROR;
    return UART_OK;
}

/* Interface table */
UART_Interface_t UART1 = {
    .Init = Init,
    .SetBaudRate = SetBaudRate,
    .SendByte = SendByte,
    .SendString = SendString,
    .SendBytes = SendBytes,
    .ReceiveByte = ReceiveByte,
    .ReceiveByteTimeout = ReceiveByteTimeout,
    .ReceiveByteAsync = ReceiveByteAsync,
    .SendByteAsync = SendByteAsync,
    .SendBytesAsync = SendBytesAsync,
    .ProcessTX = ProcessTX,
    .FlushTX = FlushTX,
    .FlushRX = FlushRX,
    .TXBusy = TXBusy,
    .RXAvailable = RXAvailable,
    .CheckErrors = CheckErrors,
};
