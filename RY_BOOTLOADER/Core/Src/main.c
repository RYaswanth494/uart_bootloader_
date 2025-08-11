#include"RCC_CLOCK_DEFINES.h"
#include"RCC_DECLARATIONS.h"
#include"GPIO_STRUCTURES.h"
#include"FLASH_DECLARATIONS.h"
#include"SYSTICK_DECLARATIONS.h"
#include"LED.h"
#include"UART_DECLARATIONS.h"
#include"UART_STRUCTURES.h"
#include"HEX_STRUCTURES.h"
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

HEX_STRUCTURE hex_records[MAX_RECORDS];

#define BAUD_RATE          115200
#define CMD_HELLO  0x55
#define CMD_ACK    0xAA
#define CMD_NACK 0xff
#define CMD_SIZE   0x10
#define CMD_BEGIN  0x01
#define CMD_DATA   0x02
#define CMD_END    0x03
uint32_t complete_check_sum=0;
uint32_t SYSTEM_CLOCK=0;
uint32_t now=0;
int main(){
	RCC_SYSTEM_CLOCK_HSEPLL_72MHZ();
	systick.init(72000);
    systick.reset();
	SYSTEM_CLOCK=0;
	LED_INIT();
	UART1_INIT(BAUD_RATE);
	while(1){
		while (systick.get_ms()< 1500)
		{
			//TOGGLE_LED();
            if((RY_USART1->SR.BITS.RXNE)){
       		 uint8_t cmd = uart_recv();
                  if(cmd == CMD_HELLO) {
               	SendByte(CMD_ACK);
               }
               else if (cmd == CMD_BEGIN) {
            	   record_index=0;
            	   complete_check_sum=0;
                   SendByte(CMD_ACK);
               }
               else if (cmd == CMD_DATA) {
            	  if(record_index>=MAX_RECORDS){
                      SendByte(CMD_NACK);
                      continue;
            	  }
            	  HEX_STRUCTURE *rec = &hex_records[record_index];
            	  rec->address |=((((uint32_t)uart_recv()<<8))|((uint32_t)uart_recv()<<0));
            	  rec->Byte_count= uart_recv();
            	  uint8_t checksum = rec->Byte_count +
            	                                 ((rec->address >> 8) & 0xFF) +
            	                                 (rec->address & 0xFF);
                  for (uint8_t i = 0; i < rec->Byte_count; i++) {
					  rec->data[i] = uart_recv();
					  checksum += rec->data[i];
				  }
            	  checksum = (~checksum) + 1;
            	 rec->check_sum = uart_recv();
				  if (checksum == rec->check_sum) {
					  complete_check_sum += checksum;
					  record_index++;
					  SendByte(CMD_ACK);
				  } else {
					  SendByte(CMD_NACK);
					  jump_to_application();
				  }
               }
               else if (cmd == CMD_END) {
            	   if(complete_check_sum==(((((uart_recv()<<24))|(uart_recv()<<16))|(uart_recv()<<8))|(uart_recv()<<0))){
                      	SendByte(CMD_ACK);
                      	RY_FLASH_EraseAppRegion();
                        for (uint16_t i = 0; i < record_index; i++) {
                            HEX_STRUCTURE *rec = &hex_records[i];
                            uint32_t absolute_address = 0x08000000 + rec->address;
                            RY_FLASH_ProgramBuffer(absolute_address, rec->data, rec->Byte_count);
                        }
                       jump_to_application();  // jump to app at 0x08004000
            	   }else{
                     	SendByte(CMD_NACK);
                     	TOGGLE_LED();
                     	jump_to_application();
            	   }
               }
            }
		}
        jump_to_application();
	}
}
