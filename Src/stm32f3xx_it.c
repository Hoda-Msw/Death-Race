/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
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
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

/* USER CODE BEGIN 0 */
#include "LiquidCrystal.h"
#include "stdlib.h"

extern char map[18][4];
extern int lap;
extern int startFlag;
extern int startMove;
extern int scale;
extern int moveC;
extern int time;
int enemies[10]={-1};
int itCounter=0;
int adcFlag=0;
int turboCounter=0;
int turboCharge=0;
int turboFlag=0;
int buttonFlag=0;
int turboDeCharge=1;
int itTimer=0;
int itTimeCounter=0;
extern int lapItCounter;
int x=0,x1=0,x2=0,y=0;


void MakeNewEnemy(){
	int r=0;
	r=rand()%15 +1;
	if(map[r][0]=='-'){
	map[r][0]='E';
	setCursor(r,0);
	write(5);
	}
	else MakeNewEnemy();
	HAL_Delay(500);
}

int EnemyRandomTime(int maxNumber){
	int r=0;
	r=rand()%maxNumber;
	return r;
}


/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim16;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles EXTI line0 interrupt.
*/
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
			if(startFlag==1){
				//while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
					buttonFlag=1;
				//}
				//buttonFlag=0;
			}
			startFlag=1;
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
	
		
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
* @brief This function handles ADC1 and ADC2 interrupts.
*/
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */
	//clear();
	int i=0;
	adcFlag++;
	
	if(adcFlag==3){
		adcFlag=0;
		i=HAL_ADC_GetValue(&hadc1);
		scale=i*14/63 +1;
		moveC=1;
	}
	HAL_ADC_Start_IT(&hadc1);

  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */
  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
* @brief This function handles TIM1 update and TIM16 interrupts.
*/
void TIM1_UP_TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 0 */
	
  /* USER CODE END TIM1_UP_TIM16_IRQn 0 */
  HAL_TIM_IRQHandler(&htim16);
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 1 */
	itTimeCounter++;
	if(1){
			
			x=time%10;
			y=time/10;
			x1=y%10;
			y=y/10;
			x2=y%10;
			y=y/10;
			
			if(itTimeCounter==1){
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
			
			
			//show numbers
		switch(x){
				case 0:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 1:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 2:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 3:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 4:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 5:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 6:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 7:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 8:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
				case 9:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
			}
		}
			if(itTimeCounter==2){
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
			
			switch(x1){
				case 0:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 1:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 2:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 3:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 4:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 5:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 6:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 7:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 8:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
				case 9:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
			}
		}
			if(itTimeCounter==2){
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
			
			switch(x2){
				case 0:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 1:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 2:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 3:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 4:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 5:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 6:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 7:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 8:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
				case 9:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
			}
		}
			if(itTimeCounter==3){
				itTimeCounter=0;
				itTimer=0;
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);
			
			switch(y){
				case 0:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 1:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 2:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 3:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 4:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 5:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 6:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 7:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
					break;
				case 8:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
				case 9:
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
					break;
			}
		}
	}
  /* USER CODE END TIM1_UP_TIM16_IRQn 1 */
}

/**
* @brief This function handles Timer 6 interrupt and DAC underrun interrupts.
*/
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	time++;
	itTimer=1;
	
	lapItCounter++;
	turboCounter++;
	if(turboCounter==5){
		turboCounter=0;
		if(turboCharge<10)
			turboCharge++;
	}
	
	switch(turboCharge){
		case 1:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,1);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,1);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,1);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,1);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,1);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,1);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,1);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,1);
			break;
		case 10:
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,1);
			break;
	}
	
	if(lap==1){
		for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap;i++)
				enemies[i]=EnemyRandomTime(10);
	}
  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */
	if(lapItCounter==15){
	if(lap==8){
		lap=0;
		startFlag=2;
	}
	lap++;
	switch(lap){
		case 1 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(10);
			break;
		case 2 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_9);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(10);
			break;
		case 3 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(10);
			break;
		case 4 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(10);
			break;
		case 5 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_12);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(12);
			break;
		case 6 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_13);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(12);
			break;
		case 7 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_14);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(14);
			break;
		case 8 :
			HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_15);
			for(int i=0;i<10;i++)
				enemies[i]=-1;
			for(int i=0;i<=lap+1;i++)
				enemies[i]=EnemyRandomTime(14);
			break;
	}
	lapItCounter=0;
}

	for(int i=0;i<10;i++){
		if(enemies[i]==lapItCounter)
			MakeNewEnemy();
	}

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
* @brief This function handles TIM7 global interrupt.
*/
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
	//int turboDecherg=0;
	if(buttonFlag!=0){
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
		turboFlag++;
		}
	}
	
	if(turboFlag>8){
		turboDeCharge++;
		turboCharge--;
		turboFlag=0;
	}
	itCounter++;
	switch(lap){
		case 1:
			if(itCounter==12-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
		case 2:
			if(itCounter==11-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
		case 3:
			if(itCounter==10-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
		case 4:
			if(itCounter==9-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
		case 5:
			if(itCounter==8-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
		case 6:
			if(itCounter==7-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
		case 7:
			if(itCounter==6-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
		case 8:
			if(itCounter==5-turboDeCharge){
				startMove=1;
				itCounter=0;
			}
			break;
	}
  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
