#include"RCC_CLOCK_DEFINES.h"
#include"RCC_DECLARATIONS.h"
#include"DEFINATIONS.h"
#include"LED.h"
int main(){
	RCC_SYSTEM_CLOCK_HSI();
    SYSTEM_CLOCK_TEST();
	LED_INIT();
	while(1){
		TOGGLE_LED();
	}
}
