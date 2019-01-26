
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
#include "main.h"
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "stm32f3xx_hal.h"
#include "LiquidCrystal.h"
#include "stdlib.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc4;

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim16;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char map[18][4];
int lap;
int chance;
int startFlag;
int startMove;
int lapItCounter;
int scale;
int moveC;
int time;
int score=0;
int accidentTime=0;
typedef unsigned char byte;

byte leftSideOfMap[8] = {
	0x18,
	0x1C,
	0x1E,
	0x1C,
	0x18,
	0x1C,
	0x1C,
	0x18,
};

byte rightSideOfMap[8] = {
  	0x03,
	0x07,
	0x0F,
	0x07,
	0x03,
	0x07,
	0x07,
	0x03,
};

byte downSideOfMap[8] = {
    0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x0A,
	0x1F,
};

byte rightCornerOfMap[8] = {
  	0x01,
	0x07,
	0x0F,
	0x07,
	0x03,
	0x03,
	0x0B,
  0x1F,
};

byte leftCornerOfMap[8] = {
  	0x10,
	0x1C,
	0x1E,
	0x1E,
	0x1C,
	0x18,
	0x1A,
	0x1F,
};

byte enemy[8] = {
      0x04,
	0x0A,
	0x0A,
	0x1F,
	0x11,
	0x1F,
	0x0A,
	0x00,
};

byte rightSideOfCar[8] = {
  0x00,
	0x18,
	0x04,
	0x1A,
	0x1B,
	0x01,
	0x0D,
	0x13,
};

byte leftSideOfCar[8] = {
  0x00,
	0x03,
	0x04,
	0x0B,
	0x1B,
	0x10,
	0x16,
	0x09,
};

byte full[8] = {
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F
};

byte HalfDown[8] = {		
	0x00,
	0x00,
	0x00,
	0x00,
	0x1F,
	0x1F,
	0x1F,
	0x1F
};

byte DownTriangleR[8] = {	
	0x00,
	0x00,
	0x00,
	0x00,
	0x03,
	0x07,
	0x0F,
	0x1F
};


byte UpTriangleL[8] = {		
	0x1F,
	0x1E,
	0x1C,
	0x10,
	0x00,
	0x00,
	0x00,
	0x00
};

byte DownTriangleL[8] = {	
	0x00,
	0x00,
	0x00,
	0x00,
	0x18,
	0x1C,
	0x1E,
	0x1F
};

byte Middle21[8] = {		
	0x1F,
	0x1F,
	0x0F,
	0x0F,
	0x0E,
	0x1C,
	0x18,
	0x10
};


byte Middle22[8] = {		
	0x01,
	0x03,
	0x07,
	0x0F,
	0x1F,
	0x1F,
	0x1E,
	0x1C
};

byte Down21[8] = {
	0x01,
	0x03,
	0x07,
	0x0F,
	0x1F,
	0x1F,
	0x1F,
	0x1F
};

byte Down22[8] = {
	0x1F,
	0x1E,
	0x1C,
	0x18,
	0x1F,
	0x1F,
	0x1F,
	0x1F
};

byte Up31[8] = {
	0x01,
	0x03,
	0x07,
	0x0F,
	0x1C,
	0x18,
	0x00,
	0x00
};

byte Up32[8] = {
	0x00,
	0x00,
	0x00,
	0x03,
	0x07,
	0x0E,
	0x1C,
	0x18
};

byte UpTriangleR[8] = {
	0x1F,
	0x0F,
	0x07,
	0x03,
	0x00,
	0x00,
	0x00,
	0x00
};

byte Middle31[8] = {
	0x10,
	0x18,
	0x1E,
	0x1F,
	0x03,
	0x01,
	0x00,
	0x00
};

byte Middle32[8] = {
	0x00,
	0x00,
	0x00,
	0x10,
	0x18,
	0x1E,
	0x07,
	0x03
};

byte Down3[8] = {
	0x03,
	0x03,
	0x03,
	0x07,
	0x1E,
	0x1C,
	0x1C,
	0x18
};

void counting(){
	createChar(10, full);
	createChar(11, HalfDown);
	createChar(12, DownTriangleR);
	createChar(13, UpTriangleL);
	createChar(14, DownTriangleL);
	createChar(15, Middle21);
	createChar(16, Middle22);
	createChar(17, Down21);
	createChar(18, Down22);
	createChar(19, Up31);
	createChar(20, Up32);
	createChar(21, UpTriangleR);
	createChar(22, Middle31);
	createChar(23, Middle32);
	createChar(24, Down3);
	
	clear();
	setCursor(8,0);
	write(12);
	setCursor(9,0);
	write(11);
	setCursor(9,1);
	write(10);
	setCursor(9,2);
	write(10);
	setCursor(9,3);
	write(10);
	setCursor(8,3);
	write(10);
	setCursor(10,3);
	write(10);
	HAL_Delay(500);
	clear();
	
	setCursor(8,1);
	write(13);
	setCursor(8,0);
	write(12);
	setCursor(9,0);
	write(11);
	setCursor(10,0);
	write(11);
	setCursor(11,0);
	write(11);
	setCursor(12,0);
	write(14);
	setCursor(12,1);
	write(15);
	setCursor(11,1);
	write(12);
	setCursor(11,2);
	write(13);
	setCursor(10,2);
	write(16);
	setCursor(9,2);
	write(12);
	setCursor(8,3);
	write(17);
	setCursor(9,3);
	write(18);
	setCursor(10,3);
	write(11);
	setCursor(11,3);
	write(11);
	setCursor(12,3);
	write(11);
	HAL_Delay(500);
	clear();
	
	setCursor(7,0);
	write(12);
	setCursor(8,0);
	write(11);
	setCursor(9,0);
	write(11);
	setCursor(10,0);
	write(11);
	setCursor(11,0);
	write(14);
	setCursor(11,1);
	write(13);
	setCursor(10,1);
	write(19);
	setCursor(9,1);
	write(20);
	setCursor(8,1);
	write(12);
	setCursor(8,2);
	write(21);
	setCursor(9,2);
	write(22);
	setCursor(10,2);
	write(23);
	setCursor(11,2);
	write(14);
	setCursor(11,3);
	write(13);
	setCursor(10,3);
	write(24);
	setCursor(9,3);
	write(11);
	setCursor(8,3);
	write(11);
	setCursor(7,3);
	write(11);
	HAL_Delay(500);
	clear();
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM16_Init(void);
static void MX_ADC4_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

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
	map[0][3]='c';//LeftCorner
	map[17][3]='C';//RightCorner
	map[8][3]='M';
	map[9][3]='N';
}

void DrawMap(){
	//noDisplay();
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
//	setCursor(18,0);
//	write(8);
//	setCursor(18,2);
//	write(9);
	display();
}


int SetMap(){
	char array[1];
	for(int i=0;i<18;i++){
		if(map[i][3]=='E'){
			map[i][3]='-';
			setCursor(i,3);
			write(2);
		}
	}
	while(startMove==1){
	for(int i=16;i>0;i--){
		for(int j=3;j>=0;j--){
			if(map[i][j]=='E'){
				map[i][j]='-';
				if(map[i][j+1]=='M'||map[i][j+1]=='N'){
					setCursor(i,j+1);
					write(2);
					setCursor(i,j+2);
					write(2);
					setCursor(i,j);
					write(2);
					accidentTime=time;
					chance--;
					setCursor(18,3);
					sprintf(array,"%d",chance);
					print(array);
					if(chance>0){
						lapItCounter=0;
						map[8][3]='M';
						map[9][3]='N';
						setCursor(8,3);
						write(6);
						setCursor(9,3);
						write(7);
						startMove=0;
					}
					else{
						clear();
						setCursor(4,1);
						print("GAME OVER");
						return 0;
					}
				}
					
				map[i][j+1]='E';
				setCursor(i,j);
				print(" ");
				setCursor(i,j+1);
				write(5);		
				break;
			}
		}
	}
	startMove=0;
}
	while(moveC==1){
		for(int i=1;i<18;i++){
			if(map[i][3]=='M'){
				if(i>scale){
					for(;i>scale;i--){
						map[i+1][3]='-';
						map[i][3]='N';
						map[i-1][3]='M';
						setCursor(i,3);
						write(7);
						setCursor(i-1,3);
						write(6);
						setCursor(i+1,3);
						write(2);
						if(map[i-1][3]=='E'||map[i][3]=='E'){
							setCursor(i-1,3);
							write(2);
							setCursor(i,3);
							write(2);
							accidentTime=time;
							chance--;
							setCursor(18,3);
							write(chance);
							if(chance>0){
								lapItCounter=0;
								map[8][3]='M';
								map[9][3]='N';
								setCursor(8,3);
								write(6);
								setCursor(9,3);
								write(7);
								startMove=0;
							}
							else{
						clear();
						setCursor(4,1);
						print("GAME OVER");
						return 0;
					}
						}
			}
					moveC=0;
			}
			else{
				for(;i<scale;i++){
						map[i][3]='-';
						map[i+1][3]='M';
						map[i+2][3]='N';
						setCursor(i+2,3);
						write(7);
						setCursor(i+1,3);
						write(6);
						setCursor(i,3);
						write(2);
					if(map[i+1][3]=='E'||map[i+2][3]=='E'){
							setCursor(i+1,3);
							write(2);
							setCursor(i+2,3);
							write(2);
							accidentTime=time;
							chance--;
							setCursor(18,3);
							write(chance);
							if(chance>0){
								lapItCounter=0;
								map[8][3]='M';
								map[9][3]='N';
								setCursor(8,3);
								write(6);
								setCursor(9,3);
								write(7);
								startMove=0;
							}
							else{
						clear();
						setCursor(4,1);
						print("GAME OVER");
						return 0;
					}
						}
			}
				moveC=0;
		}
	}
	}
}
	return 1;
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

void SetScore(){
	char array[4];
	int x=0;
	score=((lap+1)*lap)*(time-accidentTime);
//	x=score/100;
//	setCursor(18,1);
//	sprintf(array,"%d",x);
//	print(array);
}


void Welcome(){
	while(startFlag==0){
	setCursor(5,0);
	print("DEATH RACE");
	setCursor(5,2);
	print("@hoda_msw");
	setCursor(5,3);
	print("@sogandDVR");
	display();
		
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);
		
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
		
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_9);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_12);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_13);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_14);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_15);
		
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_0);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_1);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_2);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_3);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_4);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_5);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_6);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_7);
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_14);
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_15);
	HAL_Delay(500);
	noDisplay();
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
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
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7,0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,0);
	
	HAL_TIM_Base_Stop_IT(&htim6);
	HAL_TIM_Base_Stop_IT(&htim7);
	
	lap=1;
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8);
	counting();
	DrawMap();
	char array[1];
	sprintf(array,"%d",chance);
	setCursor(18,3);
	print(array);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_Base_Start_IT(&htim16);
	HAL_ADC_Start_IT(&hadc1);
	int i=1;
	while(i==1){
		if(startFlag==1){
		i=SetMap();
		SetScore();
		}
		if(startFlag==2){
		clear();
		startFlag=0;
		while(startFlag==0){
			setCursor(5,0);
			print("YOU WIN");
			setCursor(5,1);
			print("CONTINUE?");
			char arr[5];
			sprintf(arr,"%d",score);
			setCursor(5,2);
			print(arr);
			display();
			HAL_Delay(300);
			noDisplay();
			HAL_Delay(300);
		}
		Welcome();
	}
}
	HAL_TIM_Base_Stop_IT(&htim6);
	HAL_TIM_Base_Stop_IT(&htim7);
	HAL_ADC_Stop_IT(&hadc1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7,0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,0);
	while(1){
	setCursor(4,1);
	print("GAME OVER");
	display();
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_9);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_12);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_13);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_14);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_15);
		
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_0);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_1);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_2);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_3);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_4);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_5);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_6);
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_7);
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_14);
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_15);
	
	HAL_Delay(500);
	noDisplay();
	HAL_Delay(300);
	}
}

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
  MX_TIM7_Init();
  MX_ADC1_Init();
  MX_TIM16_Init();
  MX_ADC4_Init();
  /* USER CODE BEGIN 2 */
	LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
	
	begin(20,4);
	startFlag=0;
	SetMapForFirstTime();
	startMove=0;
	chance=8;
	lapItCounter=0;
	time=0;
	Welcome();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//		GameController();
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12|RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_6B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the ADC multi-mode 
    */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* ADC4 init function */
static void MX_ADC4_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc4.Instance = ADC4;
  hadc4.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc4.Init.Resolution = ADC_RESOLUTION_12B;
  hadc4.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc4.Init.ContinuousConvMode = DISABLE;
  hadc4.Init.DiscontinuousConvMode = DISABLE;
  hadc4.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc4.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc4.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc4.Init.NbrOfConversion = 1;
  hadc4.Init.DMAContinuousRequests = DISABLE;
  hadc4.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc4.Init.LowPowerAutoWait = DISABLE;
  hadc4.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc4, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM6 init function */
static void MX_TIM6_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 35999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1999;
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

/* TIM7 init function */
static void MX_TIM7_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 12499;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 719;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM16 init function */
static void MX_TIM16_Init(void)
{

  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 36999;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 7;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0 
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE4 PE5 
                           PE6 PE8 PE9 PE10 
                           PE11 PE12 PE13 PE14 
                           PE15 PE0 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC13 PC14 PC15 PC0 
                           PC1 PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0 
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 
                           PA10 PA11 PA12 PA13 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

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
