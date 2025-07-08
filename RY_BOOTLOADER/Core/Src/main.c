#include"RCC_CLOCK_DEFINES.h"
#include"RCC_DECLARATIONS.h"
#include"DEFINATIONS.h"
#include"LED.h"
#include "stm32f1xx.h"  // Or "core_cm3.h" if using raw CMSIS
#define APP_ADDRESS 0x08004000
#define SCB_VTOR (*(volatile uint32_t*)0xE000ED08)
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
	LED_INIT();
	int i=0;
  //  SYSTEM_CLOCK_TEST();
	while(1){
		for( i=0;i<5;i++){
			TOGGLE_LED();
			for(int j=0;j<1000000;j++);
		}
		if(i>4){
			jump_to_application();
		}
	}
}
