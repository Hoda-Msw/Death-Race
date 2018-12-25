
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "stm32f3xx_hal.h"
#include "LiquidCrystal.h"
#include "stdlib.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char map[18][4];
int lap;
int score;
int chance;
int enemyCounter;
typedef unsigned char byte;

byte leftSideOfMap[8] = {
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
};

byte rightSideOfMap[8] = {
  0x03,
  0x03,
  0x03,
  0x03,
  0x03,
  0x03,
  0x03,
  0x03,
};

byte downSideOfMap[8] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1F,
  0x1F,
};

byte rightCornerOfMap[8] = {
  0x03,
  0x03,
  0x03,
  0x03,
  0x03,
  0x03,
  0x1F,
  0x1F,
};

byte leftCornerOfMap[8] = {
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x1F,
  0x1F,
};

byte enemy[8] = {
  0x1B,
  0x1B,
  0x04,
  0x0E,
  0x04,
  0x1F,
  0x0E,
  0x04,
};

byte rightSideOfCar[8] = {
  0x13,
  0x1F,
  0x1B,
  0x18,
  0x18,
  0x1B,
  0x1F,
  0x03,
};

byte leftSideOfCar[8] = {
  0x19,
  0x1F,
  0x1B,
  0x03,
  0x03,
  0x1B,
  0x1F,
  0x18,
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void Welcome(){
	for(int i=0;i<5;i++){
	setCursor(5,0);
	print("DEATH RACE");
	setCursor(5,2);
	print("@hoda_msw");
	setCursor(5,3);
	print("@sogandDVR");
	display();
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_9);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_12);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_13);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_14);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_15);
	HAL_Delay(500);
	noDisplay();
	HAL_Delay(300);
	}
	display();
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);
}

void MakeNewEnemy(){
	int r=0;
	r=rand()%15 +1;
	if(map[r][0]=='-'){
	map[r][0]='E';
	setCursor(r,0);
	write(5);
	}
	else MakeNewEnemy();
	HAL_Delay(700);
}

void SetMapForFirstTime(){
	for(int i=0;i<18;i++){
		for(int j=0;j<4;j++){
			map[i][j]='-';
		}
	}
	for(int i=0;i<3;i++){
		map[0][i]='L';
	}
	for(int i=0;i<3;i++){
		map[17][i]='R';
	}
	for(int i=0;i<17;i++){
		map[i][3]='D';
	}
	map[0][3]='c';	//LeftCorner
	map[17][3]='C';	//RightCorner
	MakeNewEnemy();
	enemyCounter++;
	map[8][3]='M';
	map[9][3]='N';
}


void DrawMap(){
	noDisplay();
	createChar(0, leftSideOfMap);
	createChar(1, rightSideOfMap);
	createChar(2, downSideOfMap);
	createChar(3, leftCornerOfMap);
	createChar(4, rightCornerOfMap);
	createChar(5, enemy);
	createChar(6, leftSideOfCar);
	createChar(7, rightSideOfCar);
	
	for(int i=0;i<18;i++){
		for(int j=0;j<4;j++){
			setCursor(i,j);
			switch(map[i][j]){
				case '-':
					print(" ");
					break;
				case 'R':
					write(1);
					break;
				case 'L':
					write(0);
					break;
				case 'D':
					write(2);
					break;
				case 'c':
					write(3);
					break;
				case 'C':
					write(4);
					break;
				case 'E':
					write(5);
					break;
				case 'M':
					write(6);
					break;
				case 'N':
					write(7);
					break;
			}
		}
	}
	display();
}

void SetMap(int maxOfEnemyCounter){
	for(int i=0;i<18;i++){
		if(map[i][3]=='E'){
			map[i][3]='-';
			setCursor(i,3);
			write(2);
			MakeNewEnemy();
		}
	}
	for(int i=0;i<16;i++){
		for(int j=0;j<4;j++){
			if(map[i][j]=='E'){
				map[i][j]='-';
//				if(map[i][j+1]=='M'||map[i][j+1]=='N'){
//					clear();
//					setCursor(8,1);
//					print("End");
//					break;
//				}
					
				map[i][j+1]='E';
				setCursor(i,j);
				print(" ");
				setCursor(i,j+1);
				write(5);
				while(enemyCounter<=maxOfEnemyCounter){
					MakeNewEnemy();
					enemyCounter++;
				}
				break;
			}
		}
	}
	HAL_Delay(500);
	//DrawMap();
}

void GameController(){
	switch(lap){
		case 1:
			SetMap(2);
			break;
		case 2:
			SetMap(3);
			break;
		case 3:
			SetMap(4);
			break;
		case 4:
			SetMap(5);
			break;
		case 5:
			SetMap(6);
			break;
		case 6:
			SetMap(7);
			break;
		case 7:
			SetMap(8);
			break;
		case 8:
			SetMap(10);
			break;
	}
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
	LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
	
	begin(20,4);
	Welcome();
	SetMapForFirstTime();
	DrawMap();
	lap=1;
	HAL_TIM_Base_Start_IT(&htim6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */
		GameController();
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM6 init function */
static void MX_TIM6_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 47999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 14999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE8 PE9 PE10 PE11 
                           PE12 PE13 PE14 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
