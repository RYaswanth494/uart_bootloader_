#include"RCC_CLOCK_DEFINES.h"
#include"RCC_DECLARATIONS.h"
#include"DEFINATIONS.h"
#include"LED.h"
// RCC and GPIOB Register Addresses
#define RCC_APB2ENR   (*(volatile unsigned int *)0x40021018)
#define GPIOB_CRL     (*(volatile unsigned int *)0x40010C00)
#define GPIOB_ODR     (*(volatile unsigned int *)0x40010C0C)
void delay_ms(unsigned int ms)
{
    for (unsigned int i = 0; i < ms * 8000; i++) {
        __asm__("nop");
    }
}
int main(){
	//RCC_SYSTEM_CLOCK_HSI();
	//LED_INIT();
	//RCC_SYSTEM_CLOCK_HSIPLL_64MHZ();
	RCC_SYSTEM_CLOCK_HSEPLL_72MHZ();
    //SYSTEM_CLOCK_TEST();
	//LED_INIT();
    // 1. Enable GPIOB clock (bit 3 in RCC_APB2ENR)
    RCC_APB2ENR |= (1 << 3);

    // 2. Set PB2 as Output Push-Pull, 2 MHz
    GPIOB_CRL &= ~(0xF << (2 * 4));     // Clear bits [11:8] for PB2
    GPIOB_CRL |=  (0x2 << (2 * 4));
	while(1){
		//TOGGLE_LED();
        GPIOB_ODR |=  (1 << 2);    // LED ON (PB2 HIGH)
        delay_ms(500);

        GPIOB_ODR &= ~(1 << 2);    // LED OFF (PB2 LOW)
        delay_ms(500);
	}
}
