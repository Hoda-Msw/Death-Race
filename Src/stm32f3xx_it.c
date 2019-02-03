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

char map[18][4];
int lap;
int startFlag;
int startMove=0;
int scale;
int moveC;
int time=0;
int enemies[10]={-1};
int itCounter=0;
int adcFlag=0;
int turboCounter=0;
int turboCharge=0;
int turboFlag=0;
int buttonFlag=0;
int turboDeCharge=1;
int itTimer=0;
int chance=8;
int score=0;
int accidentTime=0;
int itTimeCounter=0;
int lapItCounter=0;
int x=0,x1=0,x2=0,y=0;
int col=-1;
int pirCounter=0;
char upid[10]={"-"};
char NUMS[4][4]={{'1','5','9','A'},
				 {'2','6','0','B'},
				 {'3','7','*','C'},
				 {'4','8','#','D'}};

typedef unsigned char byte;
									
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc4;

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim16;

//Game & Car map
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
//Counting 1-2-3
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
	0x1F,
};

byte HalfDown[8] = {		
	0x00,
	0x00,
	0x00,
	0x00,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
};

byte DownTriangleR[8] = {	
	0x00,
	0x00,
	0x00,
	0x00,
	0x03,
	0x07,
	0x0F,
	0x1F,
};


byte UpTriangleL[8] = {		
	0x1F,
	0x1E,
	0x1C,
	0x10,
	0x00,
	0x00,
	0x00,
	0x00,
};

byte DownTriangleL[8] = {	
	0x00,
	0x00,
	0x00,
	0x00,
	0x18,
	0x1C,
	0x1E,
	0x1F,
};

byte Middle21[8] = {		
	0x1F,
	0x1F,
	0x0F,
	0x0F,
	0x0E,
	0x1C,
	0x18,
	0x10,
};


byte Middle22[8] = {		
	0x01,
	0x03,
	0x07,
	0x0F,
	0x1F,
	0x1F,
	0x1E,
	0x1C,
};

byte Down21[8] = {
	0x01,
	0x03,
	0x07,
	0x0F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
};

byte Down22[8] = {
	0x1F,
	0x1E,
	0x1C,
	0x18,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
};

byte Up31[8] = {
	0x01,
	0x03,
	0x07,
	0x0F,
	0x1C,
	0x18,
	0x00,
	0x00,
};

byte Up32[8] = {
	0x00,
	0x00,
	0x00,
	0x03,
	0x07,
	0x0E,
	0x1C,
	0x18,
};

byte UpTriangleR[8] = {
	0x1F,
	0x0F,
	0x07,
	0x03,
	0x00,
	0x00,
	0x00,
	0x00,
};

byte Middle31[8] = {
	0x10,
	0x18,
	0x1E,
	0x1F,
	0x03,
	0x01,
	0x00,
	0x00,
};

byte Middle32[8] = {
	0x00,
	0x00,
	0x00,
	0x10,
	0x18,
	0x1E,
	0x07,
	0x03,
};

byte Down3[8] = {

	0x03,
	0x03,
	0x03,
	0x07,
	0x1E,
	0x1C,
	0x1C,
	0x18,
};
//Counting 1-2-3 befor game starts
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
//saving game on server
void Save(){
		//printf("upid\n",);
	printf("score\n%d\n",score);
	printf("heart\n%d\n",chance);
	printf("level\n%d\n",lap);
	//printf("time\n%d\n",time);
	//printf("date\n%d\n",date);
	printf("turbo\n%d\n",turboCharge);
	//printf("speed\n%d\n",speed);
	printf("gsec\n%d\n",time);
	//printf("mcp\n%d\n",mcp);
	//printf("ecp\n%d\n",ecp);
	printf("save\n");
}
//drawing the map for a new game
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
//manage game map array while the game
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
						print("GAME OVER !");
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
						print("GAME OVER !");
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
						print("GAME OVER !");
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
//calculate score of the game
void SetScore(){
	char array[4];
	int x=0;
	score=((lap+1)*lap)*(time-accidentTime);
//	x=score/100;
//	setCursor(18,1);
//	sprintf(array,"%d",x);
//	print(array);
}
//create enemys randomly
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
//manage time of creating new enemys and number of them
int EnemyRandomTime(int maxNumber){
	int r=0;
	r=rand()%maxNumber;
	return r;
}
//starting a new game from the menu
void NewGame(){
    
	SetMapForFirstTime();
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
	
	
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
	HAL_ADC_Start_IT(&hadc4);
	
//	int i=1;
//	while(1){
////		if(startFlag==1){
////		i=SetMap();
////		SetScore();
////		}
//	}
//		if(startFlag==2){
//		clear();
//		startFlag=0;
//		while(startFlag==0){
//			setCursor(5,0);
//			print("YOU WIN");
//			setCursor(5,1);
//			print("CONTINUE?");
//			char arr[5];
//			sprintf(arr,"%d",score);
//			setCursor(5,2);
//			print(arr);
//			display();
//			HAL_Delay(300);
//			noDisplay();
//			HAL_Delay(300);
//		}
//		NewGame();
//	}

//	HAL_TIM_Base_Stop_IT(&htim6);
//	HAL_TIM_Base_Stop_IT(&htim7);
//	HAL_ADC_Stop_IT(&hadc1);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,0);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,0);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,0);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,0);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,0);
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);
//	
//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,0);
//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14,0);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
	
//	while(1){
//	setCursor(4,1);
//	print("GAME OVER");
//	display();
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8);
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_9);
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_12);
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_13);
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_14);
//	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_15);
//		
////	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8);
//		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_8);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_9);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_11);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_12);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_13);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_14);
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_15);
	
//	HAL_Delay(500);
//	noDisplay();
//	HAL_Delay(300);
//	}
}
//load game from server o the menu
void LoadGame(){}
//about part on the menu
void About(){
	clear();
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
		
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_8);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_9);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_11);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_12);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_13);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_14);
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_15);
	HAL_Delay(500);
	noDisplay();
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_Delay(300);
	}
}

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart4;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void){
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void){
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
void MemManage_Handler(void){
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
void BusFault_Handler(void){
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
void UsageFault_Handler(void){
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
void SVC_Handler(void){
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void){
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void){
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void){
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
void EXTI0_IRQHandler(void){
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
* @brief This function handles EXTI line1 interrupt.
*/
void EXTI1_IRQHandler(void){
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
* @brief This function handles ADC1 and ADC2 interrupts.
*/
//volume code for moving the car
void ADC1_2_IRQHandler(void){
  /* USER CODE BEGIN ADC1_2_IRQn 0 */
	//clear();
	int i=0;
	adcFlag++;
	
	if(adcFlag==3){
		adcFlag=0;
		i=HAL_ADC_GetValue(&hadc1);
		scale=i*14/63 +1;
		moveC=1;
		SetMap();
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
//7-segment code :|
void TIM1_UP_TIM16_IRQHandler(void){
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
* @brief This function handles EXTI line[15:10] interrupts.
*/
//keypad code :((( 
void EXTI15_10_IRQHandler(void){
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
		for(int row=0;row<4;row++){
			col=-1;
			switch(row){
				case 0:
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,0);
					break;
				case 1:
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,0);
					break;
				case 2:
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,0);
					break;
				case 3:
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,0);
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);
					break;
			}
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)){
				col=0;
				while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11));
			}
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)){
				col=1;
				while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13));
			}
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)){
				col=2;
				while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14));
			}
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)){
				col=3;
				while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15));
			}
	
//			if(col==0)
//				HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_8);
//			if(col==1)
//				HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_9);
//			if(col==2)
//				HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
//			if(col==3)
//				HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);
			//print("hiiiiiiiiiiiiiiiiiiiiiiiii");
			if(col!=-1){
//				setCursor(0,0);
//				write(NUMS[row][col]);
				if(startFlag ==0){
					if(NUMS[row][col]=='1'){
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);
						startFlag=1;
						NewGame();
					}
					if(NUMS[row][col]=='2'){
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);
						LoadGame();
					}
					if(NUMS[row][col]=='3'){
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);
						About();
					}
				}
				
				if(startFlag==3){
					//print("hiiiiiiiiiii");
					int i=0;
					while(NUMS[row][col]!='#'){
						upid[i]=NUMS[row][col];
						setCursor(i,0);
						write(upid[i]);
						i++;
					}
				}
				
			}
		}

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
* @brief This function handles ADC3 global interrupt.
*/
//PIR sensore code 
void ADC3_IRQHandler(void){
  /* USER CODE BEGIN ADC3_IRQn 0 */
	int pir=0;
	pirCounter++;
	pir = HAL_ADC_GetValue(&hadc3);
	if(pir==51 && pirCounter==10){
		clear();
		HAL_TIM_Base_Stop_IT(&htim6);
		HAL_TIM_Base_Stop_IT(&htim7);
		HAL_TIM_Base_Stop_IT(&htim16);
		HAL_ADC_Stop_IT(&hadc1);
		HAL_ADC_Stop_IT(&hadc4);
		pirCounter=0;
	}
	HAL_ADC_Start_IT(&hadc3);

  /* USER CODE END ADC3_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc3);
  /* USER CODE BEGIN ADC3_IRQn 1 */

  /* USER CODE END ADC3_IRQn 1 */
}

/**
* @brief This function handles UART4 global interrupt / UART4 wake-up interrupt through EXTI line 34.
*/
//
void UART4_IRQHandler(void){
  /* USER CODE BEGIN UART4_IRQn 0 */

  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

/**
* @brief This function handles Timer 6 interrupt and DAC underrun interrupts.
*/
//sharge turbo & level LEDs code
void TIM6_DAC_IRQHandler(void){
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
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,1);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,1);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,1);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,1);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13,1);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14,1);
			break;
		case 10:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);
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
//decharge turbo code
void TIM7_IRQHandler(void){
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
