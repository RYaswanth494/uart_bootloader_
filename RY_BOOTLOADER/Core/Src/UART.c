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
#include<stdio.h>
#include"GPIO_STRUCTURES.h"
#include"UART_DEFINES.h"
#include"UART_STRUCTURES.h"
#include"RCC_STRUCTURES.h"
#include"RCC_CLOCK_DEFINES.h"
//#include"main.h"
#define GPIOA_BASE      0x40010800
#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x18))
#define GPIOA_CRL       (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_CRH       (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define RCC_RY_USART1EN (1 << 14)

#define RCC_IOPAEN      (1 << 2)
/* ==== Function Implementations ==== */

 UART_Status_t SetBaudRate(uint32_t baudrate) {
    if (baudrate == 0) return UART_ERROR;
    uint32_t pclk = 8000000;
    uint32_t RY_USARTdiv = (pclk + (baudrate / 2)) / baudrate;
    RY_USART1->BRR.BITS.DIV_Mantissa = (RY_USARTdiv >> 4) & 0xFFF;
    RY_USART1->BRR.BITS.DIV_Fraction = RY_USARTdiv & 0xF;
    return UART_OK;
}
UART_Status_t UART1_INIT(uint32_t baud_rate){
	RY_RCC->APB2ENR.BITS.USART1EN=0;
	RY_RCC->APB2ENR.BITS.USART1EN=1;
	RY_RCC->APB2ENR.BITS.IOPAEN=0;
	RY_RCC->APB2ENR.BITS.IOPAEN=1;
	//GPIOA->CRH.REG&= ~(0xF << 4);
	RY_GPIOA->CRH.BITS.CNF9=0b10;
	RY_GPIOA->CRH.BITS.MODE9=0b11;
	RY_GPIOA->CRH.BITS.CNF10=0b01;
	RY_GPIOA->CRH.BITS.MODE10=0b00;
	RY_USART1->CR1.BITS.UE=0;
	RY_USART1->CR1.BITS.TE=0;
	RY_USART1->CR1.BITS.TE=1;
	RY_USART1->CR1.BITS.RE=0;
	RY_USART1->CR1.BITS.RE=1;
	SetBaudRate(baud_rate);
	RY_USART1->CR1.BITS.UE=1;
	return UART_OK;
}
UART_Status_t SendByte(uint8_t byte){
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
UART_Status_t  ReceiveByte(uint8_t *byte){
    while (!RY_USART1->SR.BITS.RXNE);
    *byte = RY_USART1->DR.BITS.DR & 0xFF;
    return UART_OK;
}
uint8_t uart_recv(){
    while (!RY_USART1->SR.BITS.RXNE);
    uint8_t byte = RY_USART1->DR.BITS.DR & 0xFF;
    return byte;
}



UART_Status_t SetBaudRate_USART2(uint32_t baudrate) {
   if (baudrate == 0) return UART_ERROR;
   uint32_t pclk = 8000000;
   uint32_t RY_USARTdiv = (pclk + (baudrate / 2)) / baudrate;
   RY_USART2->BRR.BITS.DIV_Mantissa = (RY_USARTdiv >> 4) & 0xFFF;
   RY_USART2->BRR.BITS.DIV_Fraction = RY_USARTdiv & 0xF;
   return UART_OK;
}
UART_Status_t UART2_INIT(uint32_t baud_rate) {
    // Enable USART2 and GPIOA clocks
    RY_RCC->APB1ENR.BITS.USART2EN = 0;
    RY_RCC->APB1ENR.BITS.USART2EN = 1;
    RY_RCC->APB2ENR.BITS.IOPAEN = 0;
    RY_RCC->APB2ENR.BITS.IOPAEN = 1;
    // Configure PA2 (TX) as Alternate function push-pull, 50MHz
    RY_GPIOA->CRL.BITS.CNF2 = 0b10;  // AF Push-Pull
    RY_GPIOA->CRL.BITS.MODE2 = 0b11; // Output mode, max speed 50 MHz
    // Configure PA3 (RX) as Input floating
    RY_GPIOA->CRL.BITS.CNF3 = 0b01;  // Floating input
    RY_GPIOA->CRL.BITS.MODE3 = 0b00; // Input mode
    // Disable USART2 before configuration
    RY_USART2->CR1.BITS.UE = 0;
    // Enable Transmitter and Receiver
    RY_USART2->CR1.BITS.TE = 0;
    RY_USART2->CR1.BITS.TE = 1;
    RY_USART2->CR1.BITS.RE = 0;
    RY_USART2->CR1.BITS.RE = 1;
    // Set baud rate
    SetBaudRate_USART2(baud_rate); // <- You must write this for USART2
    // Enable USART2
    RY_USART2->CR1.BITS.UE = 1;

    return UART_OK;
}
UART_Status_t SendByte2(uint8_t byte){
    while (!RY_USART2->SR.BITS.TXE);
    RY_USART2->DR.BITS.DR = byte;
    return UART_OK;
}
UART_Status_t SendString2(const char *str) {
   while (*str) {
       if (SendByte2((uint8_t)(*str++)) != UART_OK)
           return UART_ERROR;
   }
   return UART_OK;
}
UART_Status_t  ReceiveByte2(uint8_t *byte){
    while (!RY_USART2->SR.BITS.RXNE);
    *byte = RY_USART2->DR.BITS.DR & 0xFF;
    return UART_OK;
}
/* Interface table */
UART1_Interface_t UART1 = {
    .UART1_INIT = UART1_INIT,
	.SetBaudRate=SetBaudRate,
	.SendByte=SendByte,
	.SendString=SendString,
	.ReceiveByte=ReceiveByte,

};
