#include"RCC_CLOCK_DEFINES.h"
#include"RCC_DECLARATIONS.h"
#include"FLASH_DECLARATIONS.h"
#include"LED.h"
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

int main(){
	RCC_SYSTEM_CLOCK_HSE();
	//RCC_SYSTEM_CLOCK_HSEPLL_72MHZ();
	LED_INIT();
  //  SYSTEM_CLOCK_TEST();
	while(1){
		for(int i=0;i<8;i++){
			TOGGLE_LED();
			for(int j=0;j<100000;j++);
		}
		uint32_t delay_ms = 50;
		RY_FLASH_ErasePage(DELAY_VALUE_ADDR);  // Optional: Only if not already erased
		RY_FLASH_ProgramBuffer(DELAY_VALUE_ADDR, (uint8_t*)&delay_ms, sizeof(delay_ms));
		jump_to_application();
	}
}
