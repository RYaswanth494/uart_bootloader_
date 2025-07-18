#include"RCC_CLOCK_DEFINES.h"
#include"RCC_DECLARATIONS.h"
#include"GPIO_STRUCTURES.h"
#include"FLASH_DECLARATIONS.h"
#include"LED.h"
#include"UART_DECLARATIONS.h"
#include "stm32f1xx.h"  // Or "core_cm3.h" if using raw CMSIS
#define APP_ADDRESS 0x08004000
#define SCB_VTOR (*(volatile uint32_t*)0xE000ED08)
#define DELAY_VALUE_ADDR   0x0801FC00
void jump_to_application(void) {
    // 1. Read the MSP and Reset Handler from application vector table
    uint32_t app_stack = *(volatile uint32_t*)(APP_ADDRESS);
    uint32_t app_reset = *(volatile uint32_t*)(APP_ADDRESS + 4);

    // 2. Set the Vector Table base
    SCB->VTOR = APP_ADDRESS;

    // 3. Set the Main Stack Pointer
    __set_MSP(app_stack);

    // 4. Jump to the application's Reset Handler
    void (*app_entry)(void) = (void*)app_reset;
    app_entry();
}

#define BAUD_RATE          115200
#define CMD_HELLO  0x55
#define CMD_ACK    0xAA
#define CMD_SIZE   0x10
#define CMD_BEGIN  0x01
#define CMD_DATA   0x02
#define CMD_END    0x03
volatile uint32_t firmware_size = 0;
int main(){
	RCC_SYSTEM_CLOCK_HSE();
	//RCC_SYSTEM_CLOCK_HSEPLL_72MHZ();
	LED_INIT();
	UART1_INIT(BAUD_RATE);
	//uart1_init();
  //  SYSTEM_CLOCK_TEST();
	while(1){
        SendByte('A');
		RY_GPIOB->ODR.BITS.ODR2=1;
		for(int i=0;i<100000;i++);
		RY_GPIOB->ODR.BITS.ODR2=0;
		for(int i=0;i<100000;i++);
//        uint8_t cmd = uart_recv();
//
//        if (cmd == CMD_HELLO) {
//        	SendByte(CMD_ACK);
//        }
//
//        else if (cmd == CMD_SIZE) {
//            firmware_size = uart_recv();          // MSB
//            firmware_size <<= 8; firmware_size |= uart_recv();
//            firmware_size <<= 8; firmware_size |= uart_recv();
//            firmware_size <<= 8; firmware_size |= uart_recv();
//            SendByte(CMD_ACK);
//        }
//
//        else if (cmd == CMD_BEGIN) {
//        	RY_FLASH_EraseAppRegion();
//            SendByte(CMD_ACK);
//        }
//
//        else if (cmd == CMD_DATA) {
//            uint16_t addr = uart_recv() << 8;
//            addr |= uart_recv();
//            uint8_t len = uart_recv();
//
//            uint8_t buffer[256];
//            for (uint8_t i = 0; i < len; i++) {
//                buffer[i] = uart_recv();
//            }
//
//            RY_FLASH_ProgramBuffer(APP_ADDRESS + addr, buffer, len);
//            SendByte(CMD_ACK);
//        }
//
//        else if (cmd == CMD_END) {
//        	SendByte(CMD_ACK);
//            HAL_Delay(1000);
//            jump_to_application();  // jump to app at 0x08004000
//        }
		//uart_tx('j');
//		for(int i=0;i<8;i++){
//			TOGGLE_LED();
//			for(int j=0;j<100000;j++);
//		}
//		uint32_t delay_ms = 500;
//		RY_FLASH_ErasePage(DELAY_VALUE_ADDR);  // Optional: Only if not already erased
//		RY_FLASH_ProgramBuffer(DELAY_VALUE_ADDR, (uint8_t*)&delay_ms, sizeof(delay_ms));
//
//		jump_to_application();
	}
}
