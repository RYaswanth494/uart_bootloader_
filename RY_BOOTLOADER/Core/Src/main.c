#include"RCC_DECLARATIONS.h"
#include"GPIO.h"
#include"RCC_CLOCK_DEFINES.h"
#include"LED.h"
//#include"LED.h"
int main(){
//	HAL_init();
	RCC_SYSTEM_CLOCK_HSE();
	LED_INIT();
	while(1){
		TOGGLE_LED();
	}
}
