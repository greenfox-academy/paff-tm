 /**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.0.3
  * @date    22-April-2016 
  * @brief   STM32F7xx HAL API Template project 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define mLED0_PORT	GPIOG
#define mLED0_PIN 	GPIO_PIN_7
#define mLED1_PORT	GPIOI
#define mLED1_PIN	GPIO_PIN_0
#define mLED2_PORT	GPIOH
#define mLED2_PIN	GPIO_PIN_6
#define mLED3_PORT	GPIOI
#define mLED3_PIN	GPIO_PIN_3
#define mLED4_PORT	GPIOI
#define mLED4_PIN	GPIO_PIN_2
#define mLED5_PORT	GPIOA
#define mLED5_PIN	GPIO_PIN_15
#define mLED6_PORT	GPIOA
#define mLED6_PIN	GPIO_PIN_8

#define mPB0_PORT	GPIOC
#define mPB0_PIN	GPIO_PIN_7


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

/* Private functions ---------------------------------------------------------*/

void My_Init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	__HAL_RCC_GPIOK_CLK_ENABLE();
}


void LED_Init(GPIO_TypeDef *_port, uint16_t _pin)
{
	GPIO_InitTypeDef led;            // create a config structure
	led.Pin = _pin;
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pull = GPIO_PULLDOWN;
	led.Speed = GPIO_SPEED_HIGH;

	HAL_GPIO_Init(_port, &led);
}

void Button_Init(GPIO_TypeDef *_port, uint16_t _pin)
{
	GPIO_InitTypeDef pb;
	pb.Pin = _pin;
	pb.Mode = GPIO_MODE_INPUT;
	pb.Pull = GPIO_PULLUP;
	pb.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(_port, &pb);
}

struct tPin {
	  GPIO_TypeDef* port;
	  uint16_t		pin;
};

void LED_On(tPin _led)
{
	 HAL_GPIO_WritePin(_led.port, _led.pin, GPIO_PIN_SET);
}

void LED_Off(tPin _led)
{
	 HAL_GPIO_WritePin(_led.port, _led.pin, GPIO_PIN_RESET);
}

void LED_ResetAll(tPin _aPins[], unsigned int _led_num)
{
	for (unsigned int i = 0; i < _led_num; ++i) {
		LED_Off(_aPins[i]);
	}
}

void ShowSpeed(unsigned int _speed, tPin _aPins[], unsigned int _led_num)
{
	LED_ResetAll(_aPins, _led_num);
	float spld_float = _led_num * ((float)_speed / 100);
	unsigned int spld;
	spld = (unsigned int)spld_float;
	for (unsigned int i = 0; i < spld; ++i) {
		LED_On(_aPins[i]);
	}

}

void DoWhenButtonIsPushed(unsigned int *ion, unsigned int *ioff, int *dir, unsigned int *speed, tPin *aPins, unsigned int *led_num)
{
	  *ion = 0;
	  *ioff = *led_num;
	  HAL_Delay(200);
	  if (HAL_GPIO_ReadPin(mPB0_PORT, mPB0_PIN) == 1)
		  *dir = -*dir;
	  else
		  while (HAL_GPIO_ReadPin(mPB0_PORT, mPB0_PIN) == 0) {
			  *speed += 1;
			  if (*speed > 100) {
				  *speed = 0;
		      }
			  ShowSpeed(*speed, aPins, *led_num);

			  if (*speed == 100) {
				  for (unsigned int i = 0; i < 20; ++i)
					  if(HAL_GPIO_ReadPin(mPB0_PORT, mPB0_PIN) == 1)
						  break;
					  else
						  HAL_Delay(100);
		      }
			  HAL_Delay(50);
		  }
    LED_ResetAll(aPins, *led_num);
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /* This project template calls firstly two functions in order to configure MPU feature 
     and to enable the CPU Cache, respectively MPU_Config() and CPU_CACHE_Enable().
     These functions are provided as template implementation that User may integrate 
     in his application, to enhance the performance in case of use of AXI interface 
     with several masters. */ 
  
  /* Configure the MPU attributes as Write Through */
  MPU_Config();

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  /* STM32F7xx HAL library initialization:
       - Configure the Flash ART accelerator on ITCM interface
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the System clock to have a frequency of 216 MHz */
  SystemClock_Config();
  My_Init();


  /* Add your application code here     */

  tPin aPins[7] =
  {
	{mLED0_PORT, mLED0_PIN},
	{mLED1_PORT, mLED1_PIN},
	{mLED2_PORT, mLED2_PIN},
	{mLED3_PORT, mLED3_PIN},
	{mLED4_PORT, mLED4_PIN},
	{mLED5_PORT, mLED5_PIN},
	{mLED6_PORT, mLED6_PIN}
  };

  unsigned int led_num = (int)(sizeof(aPins) / sizeof(aPins[0]));

  for (unsigned int i = 0; i < led_num; ++i){
	  LED_Init(aPins[i].port, aPins[i].pin);
  }

  Button_Init(mPB0_PORT, mPB0_PIN);

  int dir = 1;
  int del = 300;	// slowest speed / max delay
  unsigned int speed = 50; // 50%
  unsigned int ion = 0;
  unsigned int ioff = led_num;

  /* Infinite loop */
  while (1)
  {
	  if (ion < led_num) {
		 if (dir > 0){
			  LED_On(aPins[ion]);
		  } else {
			  LED_On(aPins[led_num - ion - 1]);
		  }
		  ++ion;
		  if (ion == led_num && ioff == led_num) {
			  ioff = 0;
		  }
	  }

	  if (ioff < led_num){
		  if (dir > 0) {
			  LED_Off(aPins[ioff]);
		  } else {
			  LED_Off(aPins[led_num - ioff - 1]);
		  }
		  ++ioff;
		  if (ion == led_num && ioff == led_num) {
			  ion = 0;
	  	  }
	  }

	  for (unsigned int i = 0; i < 10; ++i ) {
		  if (HAL_GPIO_ReadPin(mPB0_PORT, mPB0_PIN) == 0) {
			  DoWhenButtonIsPushed(&ion, &ioff,  &dir,  &speed, aPins, &led_num);
		  }
		  HAL_Delay((del - del * ((float)speed) / 100) / 10);
	  }
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

/**
  * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
  * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
  *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;
  
  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
