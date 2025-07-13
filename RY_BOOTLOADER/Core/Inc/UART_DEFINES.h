/*
 * UART_DEFINES.h
 *
 *  Created on: Jul 12, 2025
 *      Author: maday
 */

#ifndef INC_UART_DEFINES_H_
#define INC_UART_DEFINES_H_
#include<stdint.h>
#include<stdbool.h>
// Status codes
typedef enum {
    UART_OK = 0,
    UART_ERROR,
    UART_BUSY,
    UART_NO_DATA,
    UART_TIMEOUT,
    UART_OVERFLOW
} UART_Status_t;

// UART API using function pointers
typedef struct {
    UART_Status_t (*Init)(uint32_t baudrate);
    UART_Status_t (*SetBaudRate)(uint32_t baudrate);
    UART_Status_t (*SendByte)(uint8_t byte);
    UART_Status_t (*SendString)(const char *str);
    UART_Status_t (*SendBytes)(const uint8_t *data, uint16_t len);
    UART_Status_t (*ReceiveByte)(uint8_t *byte);
    UART_Status_t (*ReceiveByteTimeout)(uint8_t *byte, uint32_t timeout_us);
    UART_Status_t (*ReceiveByteAsync)(uint8_t *byte);
    UART_Status_t (*SendByteAsync)(uint8_t byte);
    UART_Status_t (*SendBytesAsync)(const uint8_t *data, uint16_t len);
    UART_Status_t (*ProcessTX)(void);  // must be called in main loop
    void          (*FlushTX)(void);
    void          (*FlushRX)(void);
    uint8_t       (*TXBusy)(void);
    uint8_t       (*RXAvailable)(void);
    UART_Status_t (*CheckErrors)(void);
} UART_Interface_t;


#define UART_TX_BUFFER_SIZE 128
#define UART_RX_BUFFER_SIZE 128


#define RY_USART_SR_PE     (1 << 0)  // Parity Error
#define RY_USART_SR_FE     (1 << 1)  // Framing Error
#define RY_USART_SR_NE     (1 << 2)  // Noise Error
#define RY_USART_SR_ORE    (1 << 3)  // Overrun Error
#define RY_USART_SR_IDLE   (1 << 4)  // IDLE line detected
#define RY_USART_SR_RXNE   (1 << 5)  // Read Data Register Not Empty
#define RY_USART_SR_TC     (1 << 6)  // Transmission Complete
#define RY_USART_SR_TXE    (1 << 7)  // Transmit Data Register Empty
#define RY_USART_SR_LBD    (1 << 8)  // LIN Break Detection Flag
#define RY_USART_SR_CTS    (1 << 9)  // CTS Flag

#define RY_USART_CR1_SBK     (1 << 0)   // Send Break
#define RY_USART_CR1_RWU     (1 << 1)   // Receiver wakeup
#define RY_USART_CR1_RE      (1 << 2)   // Receiver Enable
#define RY_USART_CR1_TE      (1 << 3)   // Transmitter Enable
#define RY_USART_CR1_IDLEIE  (1 << 4)   // IDLE Interrupt Enable
#define RY_USART_CR1_RXNEIE  (1 << 5)   // RXNE Interrupt Enable
#define RY_USART_CR1_TCIE    (1 << 6)   // Transmission Complete Interrupt Enable
#define RY_USART_CR1_TXEIE   (1 << 7)   // TXE Interrupt Enable
#define RY_USART_CR1_PEIE    (1 << 8)   // PE Interrupt Enable
#define RY_USART_CR1_PS      (1 << 9)   // Parity Selection
#define RY_USART_CR1_PCE     (1 << 10)  // Parity Control Enable
#define RY_USART_CR1_WAKE    (1 << 11)  // Wakeup method
#define RY_USART_CR1_M       (1 << 12)  // Word length
#define RY_USART_CR1_UE      (1 << 13)  // RY_USART Enable


#define RY_USART_CR2_ADD       (0xF << 0)   // Address of the RY_USART node [0:3]
#define RY_USART_CR2_LBDL      (1 << 5)     // LIN Break Detection Length
#define RY_USART_CR2_LBDIE     (1 << 6)     // LIN Break Detection Interrupt Enable
#define RY_USART_CR2_LBCL      (1 << 8)     // Last Bit Clock Pulse
#define RY_USART_CR2_CPHA      (1 << 9)     // Clock Phase
#define RY_USART_CR2_CPOL      (1 << 10)    // Clock Polarity
#define RY_USART_CR2_CLKEN     (1 << 11)    // Clock Enable
#define RY_USART_CR2_STOP      (0x3 << 12)  // STOP[13:12]: STOP bits
#define RY_USART_CR2_LINEN     (1 << 14)    // LIN Mode Enable

#define RY_USART_CR3_EIE     (1 << 0)   // Error Interrupt Enable
#define RY_USART_CR3_IREN    (1 << 1)   // IrDA Mode Enable
#define RY_USART_CR3_IRLP    (1 << 2)   // IrDA Low-Power
#define RY_USART_CR3_HDSEL   (1 << 3)   // Half-Duplex Selection
#define RY_USART_CR3_NACK    (1 << 4)   // Smartcard NACK Enable
#define RY_USART_CR3_SCEN    (1 << 5)   // Smartcard Mode Enable
#define RY_USART_CR3_DMAR    (1 << 6)   // DMA Enable Receiver
#define RY_USART_CR3_DMAT    (1 << 7)   // DMA Enable Transmitter
#define RY_USART_CR3_RTSE    (1 << 8)   // RTS Enable
#define RY_USART_CR3_CTSE    (1 << 9)   // CTS Enable
#define RY_USART_CR3_CTSIE   (1 << 10)  // CTS Interrupt Enable

#define RY_USART_GTPR_PSC_MASK   (0xFF << 0)  // Prescaler value
#define RY_USART_GTPR_GT_MASK    (0xFF << 8)  // Guard time value


 extern UART_Interface_t UART1;

#endif /* INC_UART_DEFINES_H_ */
