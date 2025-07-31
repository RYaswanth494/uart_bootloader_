/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define BUTTON_PIN       0       // PA0
#define LED_PIN        2        // PB2
#define DEBOUNCE_TIME    50      // ms
#define BOOT_ADDRESS 0X08000000
#define BOOTLOADER_MAGIC 0xDEADBEEF
#define BOOTLOADER_FLAG_ADDR ((volatile uint32_t*)0x2000FFF0)
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void GPIO_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN;  // Enable GPIOA clock
    // PA0 as floating input
    GPIOA->CRL &= ~(0xF << (BUTTON_PIN * 4));  // Clear MODE/CNF
    GPIOA->CRL |=  (0b1000 << (BUTTON_PIN * 4));  // CNF = 01 (floating input), MODE = 00
    GPIOA->ODR&=~(1<<BUTTON_PIN);
    // PB0 as push-pull output, 2 MHz
    // PB2 as output push-pull, 2 MHz
    GPIOB->CRL &= ~(0xF << (LED_PIN * 4));
    GPIOB->CRL |=  (0x2 << (LED_PIN * 4));     // MODE=10 (2 MHz), CNF=00
    GPIOB->ODR &= ~(1 << LED_PIN);
}
uint8_t read_button(void) {
    return ((GPIOA->IDR & (1 << BUTTON_PIN)) != 0);  // HIGH = pressed
}
// Initialize SysTick to trigger every 1ms
void SysTick_Init(void) {
    // SystemCoreClock should be 72 MHz (set in startup or defined globally)
    SysTick->LOAD  = (72000000 / 1000) - 1;  // 72,000 - 1 = 71,999
    SysTick->VAL   = 0;                             // Clear current value
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |   // Use processor clock
                     SysTick_CTRL_TICKINT_Msk   |   // Enable SysTick interrupt
                     SysTick_CTRL_ENABLE_Msk;       // Enable SysTick
}
// Turn LED ON
void led_on(void) {
    GPIOB->ODR |= (1 << LED_PIN);
}
// Turn LED OFF
void led_off(void) {
    GPIOB->ODR &= ~(1 << LED_PIN);
}
void jump_to_bootloader(void) {
    // 1. Read the MSP and Reset Handler from application vector table
    uint32_t boot_stack = *(volatile uint32_t*)(BOOT_ADDRESS);
    uint32_t boot_reset = *(volatile uint32_t*)(BOOT_ADDRESS + 4);
    // 2. Set the Vector Table base
    SCB->VTOR = BOOT_ADDRESS;
    // 3. Set the Main Stack Pointer
    __set_MSP(boot_stack);
    // 4. Jump to the application's Reset Handler
    void (*boot_entry)(void) = (void*)boot_reset;
    boot_entry();
}
void recurse(void) {
	recurse();
}

void check_for_bootloader_flag(void) {
    if (*BOOTLOADER_FLAG_ADDR == BOOTLOADER_MAGIC) {
        *BOOTLOADER_FLAG_ADDR = 0;
        jump_to_bootloader();
    }
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint32_t mytick=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
uint32_t last_debounce=0;
uint8_t last_read=0,current_read=0,button_state=0;
static uint8_t cnt=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
//  check_for_bootloader_flag();
  GPIO_init();
  SysTick_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
current_read=read_button();
if(current_read!=last_read){
	last_debounce=mytick;
}
if((mytick-last_debounce)>DEBOUNCE_TIME){
	if(button_state!=current_read){
		button_state=current_read;
		if(button_state){
			cnt++;
			led_on();
			if(cnt==6){
				// Enable UsageFault and division-by-zero trap
				SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;    // Enable UsageFault
				SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;          // Trap divide-by-zero
                int a=1/0;
			}
			if(cnt==7){//stack over flow/corruption
				recurse();  // eventually triggers Hard Fault
			}
			if(cnt==8){//executing code from invalid memory
				void (*invalid_code)(void) = (void *)0xFFFFFFF1;
				invalid_code();  // crashes
			}
			if(cnt==9){//dereferenceing null pointer
				volatile uint32_t *ptr = (uint32_t *)0x00000000;
				*ptr = 0x12345678;  // causes Hard Fault
			}
			if(cnt==10){//unaligned memory access
				volatile uint32_t *bad = (uint32_t*)0xFFFFFFF0; // Invalid address
				uint32_t val = *bad;  // Will cause HardFault
			}
		}else{
			led_off();
		}
	}
}
last_read = current_read;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
