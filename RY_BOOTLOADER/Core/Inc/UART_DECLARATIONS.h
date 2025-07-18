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
 uint8_t TX_BufferEmpty(void);
 uint8_t RX_BufferEmpty(void);
 void TX_BufferPush(uint8_t data);
 void RX_BufferPush(uint8_t data);
 UART_Status_t UART1_INIT(uint32_t baudrate);
 UART_Status_t SetBaudRate(uint32_t baudrate);
 UART_Status_t SendByte(uint8_t byte);
 UART_Status_t SendString(const char *str);
 UART_Status_t SendBytes(const uint8_t *data, uint16_t len);
 UART_Status_t ReceiveByte(uint8_t *byte) ;
 UART_Status_t ReceiveByteTimeout(uint8_t *byte, uint32_t timeout_us);
 UART_Status_t ReceiveByteAsync(uint8_t *byte);
 UART_Status_t SendByteAsync(uint8_t byte) ;
 UART_Status_t SendBytesAsync(const uint8_t *data, uint16_t len);
 UART_Status_t ProcessTX(void) ;
 uint8_t uart_recv();
 void FlushTX(void) ;
 void FlushRX(void) ;
 uint8_t TXBusy(void) ;
 UART_Status_t CheckErrors(void) ;
#endif /* INC_UART_DECLARATIONS_H_ */
