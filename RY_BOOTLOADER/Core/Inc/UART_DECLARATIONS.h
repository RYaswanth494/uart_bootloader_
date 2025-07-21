/*
 * UART_DECLARATIONS.h
 *
 *  Created on: Jul 11, 2025
 *      Author: maday
 */

#ifndef INC_UART_DECLARATIONS_H_
#define INC_UART_DECLARATIONS_H_
#include<stdint.h>
#include"UART_DEFINES.h"
#include<stdio.h>
 UART_Status_t UART1_INIT(uint32_t baudrate);
 UART_Status_t SetBaudRate(uint32_t baudrate);
 UART_Status_t SendByte(uint8_t byte);
 UART_Status_t SendString(const char *str);
 UART_Status_t ReceiveByte(uint8_t *byte) ;
uint8_t uart_recv();



 UART_Status_t UART2_INIT(uint32_t baud_rate) ;
 UART_Status_t SetBaudRate_USART2(uint32_t baudrate) ;
 UART_Status_t SendByte2(uint8_t byte);
 UART_Status_t SendString2(const char *str) ;
 UART_Status_t  ReceiveByte2(uint8_t *byte);
#endif /* INC_UART_DECLARATIONS_H_ */
