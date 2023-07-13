/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "LiquidCrystal.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
typedef struct
{
    uint16_t frequency;
    uint16_t duration;
} Tone;
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))

const Tone super_mario_bros[] = {
	{2637,306}, // E7 x2
	{   0,153}, // x3 <-- Silence
	{2637,153}, // E7
	{   0,153}, // x3
	{2093,153}, // C7
	{2637,153}, // E7
	{   0,153}, // x3
	{3136,153}, // G7
	{   0,459}, // x3
	{1586,153}, // G6
	{   0,459}, // x3

	{2093,153}, // C7
	{   0,306}, // x2
	{1586,153}, // G6
	{   0,306}, // x2
	{1319,153}, // E6
	{   0,306}, // x2
	{1760,153}, // A6
	{   0,153}, // x1
	{1976,153}, // B6
	{   0,153}, // x1
	{1865,153}, // AS6
	{1760,153}, // A6
	{   0,153}, // x1

	{1586,204}, // G6
	{2637,204}, // E7
	{3136,204}, // G7
	{3520,153}, // A7
	{   0,153}, // x1
	{2794,153}, // F7
	{3136,153}, // G7
	{   0,153}, // x1
	{2637,153}, // E7
	{   0,153}, // x1
	{2093,153}, // C7
	{2349,153}, // D7
	{1976,153}, // B6
	{   0,306}, // x2

	{2093,153}, // C7
	{   0,306}, // x2
	{1586,153}, // G6
	{   0,306}, // x2
	{1319,153}, // E6
	{   0,306}, // x2
	{1760,153}, // A6
	{   0,153}, // x1
	{1976,153}, // B6
	{   0,153}, // x1
	{1865,153}, // AS6
	{1760,153}, // A6
	{   0,153}, // x1

	{1586,204}, // G6
	{2637,204}, // E7
	{3136,204}, // G7
	{3520,153}, // A7
	{   0,153}, // x1
	{2794,153}, // F7
	{3136,153}, // G7
	{   0,153}, // x1
	{2637,153}, // E7
	{   0,153}, // x1
	{2093,153}, // C7
	{2349,153}, // D7
	{1976,153}, // B6

	{   0,  0}	// <-- Disable PWM
};

const Tone hedwig_theme[] = {
		// 1 -> 1666 			\		-1666 -> 2499 			\	1660 -> 1494, 2499 -> 2249
		// 2 -> 833     ---------\		-833 -> 1249    ---------\	833 -> 750, 1249 -> 1124
		// 4 -> 416     ---------/		-416 -> 624     ---------/	416 -> 374, 624 -> 561
		// 8 -> 208			    /		-208 -> 312			    /	208 -> 187, 312 -> 281

	{REST, 750},
	{NOTE_D4, 374},
	{NOTE_G4, 561},
	{NOTE_AS4, 187},
	{NOTE_A4, 374},
	{NOTE_G4, 750},
	{NOTE_D5, 374},
	{NOTE_C5, 1124},
	{NOTE_A4, 1124},
	{NOTE_G4, 561},
	{NOTE_AS4, 187},
	{NOTE_A4, 374},
	{NOTE_F4, 750},
	{NOTE_GS4, 374},
	{NOTE_D4, 2249},
	{NOTE_D4, 374},

	{NOTE_G4, 561},
	{NOTE_AS4, 187},
	{NOTE_A4, 374},
	{NOTE_G4, 750},
	{NOTE_D5, 374},
	{NOTE_F5, 750},
	{NOTE_E5, 374},
	{NOTE_DS5, 750},
	{NOTE_B4, 374},
	{NOTE_DS5, 561},
	{NOTE_D5, 187},
	{NOTE_CS5, 374},
	{NOTE_CS4, 750},
	{NOTE_B4, 374},
	{NOTE_G4, 2249},
	{NOTE_AS4, 374},

	{NOTE_D5, 750},
	{NOTE_AS4, 374},
	{NOTE_D5, 750},
	{NOTE_AS4, 374},
	{NOTE_DS5, 750},
	{NOTE_D5, 374},
	{NOTE_CS5, 750},
	{NOTE_A4, 374},
	{NOTE_AS4, 561},
	{NOTE_D5, 187},
	{NOTE_CS5, 374},
	{NOTE_CS4, 750},
	{NOTE_D4, 374},
	{NOTE_D5, 1700},
	{REST, 150},
	{NOTE_AS4, 374},

	{NOTE_D5, 750},
	{NOTE_AS4, 374},
	{NOTE_D5, 750},
	{NOTE_AS4, 374},
	{NOTE_F5, 750},
	{NOTE_E5, 374},
	{NOTE_DS5, 750},
	{NOTE_B4, 374},
	{NOTE_DS5, 561},
	{NOTE_D5, 187},
	{NOTE_CS5, 374},
	{NOTE_CS4, 750},
	{NOTE_AS4, 374},
	{NOTE_G4, 2249},

	{      0,    0}
};

const Tone pacman[] = {
	// 32 -> 71             \                              \	71 -> 64
	// 16 -> 142 	---------)		-142 -> 213    ---------)	142 -> 128, 213 -> 192
	// 8 -> 285             /                              /	285 -> 256

	{NOTE_B4, 128},
	{NOTE_B5, 128},
	{NOTE_FS5, 128},
	{NOTE_DS5, 128},

	{NOTE_B5, 64},
	{NOTE_FS5, 192},
	{NOTE_DS5, 256},
	{NOTE_C5, 128},

	{NOTE_C6, 128},
	{NOTE_G6, 128},
	{NOTE_E6, 128},
	{NOTE_C6, 64},
	{NOTE_G6, 192},
	{NOTE_E6, 256},

	{NOTE_B4, 128},
	{NOTE_B5, 128},
	{NOTE_FS5, 128},
	{NOTE_DS5, 128},
	{NOTE_B5, 64},

	{NOTE_FS5, 192},
	{NOTE_DS5, 256},
	{NOTE_DS5, 64},
	{NOTE_E5, 64},
	{NOTE_F5, 64},

	{NOTE_F5, 64},
	{NOTE_FS5, 64},
	{NOTE_G5, 64},
	{NOTE_G5, 64},
	{NOTE_GS5, 64},
	{NOTE_A5, 128},
	{NOTE_B5, 256},
	{0,0}
};

const Tone pink_panther[] = {

	// 1 -> 2000 			\		-500 -> 750 (-4)	       \	2000 -> 1800 			(1)
	// 2 -> 1000    ---------\		-250 -> 375 (-8)   ---------\	1000 -> 900 			(2)
	// 4 -> 500     ---------/		-125 -> 187 (-16)  ---------/	500 -> 450, 750 -> 675 	(4), (-4)
	// 8 -> 250			    /		        			       /	250 -> 225, 375 -> 337 	(8), (-8)
	// 16 -> 125		   			 								125 -> 112, 187 -> 168 	(16), (-16)

  {REST, 900},
  {REST, 450},
  {REST, 225},
  {NOTE_DS4, 225},
  {NOTE_E4, 675},
  {REST, 225},
  {NOTE_FS4, 225},
  {NOTE_G4, 675},
  {REST, 225},
  {NOTE_DS4, 225},
  {NOTE_E4, 337},
  {NOTE_FS4, 225},
  {NOTE_G4, 337},
  {NOTE_C5, 225},
  {NOTE_B4, 337},
  {NOTE_B4, 225},
  {NOTE_G4, 337},
  {NOTE_B4, 225},
  {NOTE_AS4, 900},
  {NOTE_A4, 168},
  {NOTE_G4, 168},
  {NOTE_E4, 168},
  {NOTE_D4, 168},
  {NOTE_E4, 900},
  {REST, 450},
  {REST, 225},
  {NOTE_DS4, 450},



  {NOTE_E4, 675},
  {REST, 225},
  {NOTE_FS4, 225},
  {NOTE_G4, 675},
  {REST, 225},
  {NOTE_DS4, 225},
  {NOTE_E4, 337},
  {NOTE_FS4, 225},
  {NOTE_G4, 337},
  {NOTE_C5, 225},
  {NOTE_B4, 337},
  {NOTE_G4, 225},
  {NOTE_B4, 337},
  {NOTE_E5, 225},
  {NOTE_DS5, 1800},
  {NOTE_D5, 900},
  {REST, 450},
  {REST, 225},
  {NOTE_DS4, 225},
  {NOTE_E4, 750},
  {REST, 225},
  {NOTE_FS4, 225},
  {NOTE_G4, 750},
  {REST, 225},
  {NOTE_DS4, 225},
  {NOTE_E4, 337},
  {NOTE_FS4, 225},
  {NOTE_G4, 337},
  {NOTE_C5, 225},
  {NOTE_B4, 337},
  {NOTE_E4, 225},
  {NOTE_G4, 337},
  {NOTE_B4, 225},



  {NOTE_AS4, 900},
  {NOTE_A4, 168},
  {NOTE_G4, 168},
  {NOTE_E4, 168},
  {NOTE_D4, 168},
  {NOTE_E4, 675},
  {REST, 450},
  {REST, 450},
  {NOTE_E5, 337},
  {NOTE_D5, 225},
  {NOTE_B4, 337},
  {NOTE_A4, 225},
  {NOTE_G4, 337},
  {NOTE_E4, 337},
  {NOTE_AS4, 112},
  {NOTE_A4, 337},
  {NOTE_AS4, 112},
  {NOTE_A4, 337},
  {NOTE_AS4, 112},
  {NOTE_A4, 337},
  {NOTE_AS4, 112},
  {NOTE_A4, 337},
  {NOTE_G4, 168},
  {NOTE_E4, 168},
  {NOTE_D4, 168},
  {NOTE_E4, 112},
  {NOTE_E4, 112},
  {NOTE_E4, 900},
  {		 0,   0}

};

extern TIM_HandleTypeDef htim2;
TIM_HandleTypeDef *pwm_timer = &htim2;	// Point to PWM Timer configured in CubeMX
uint32_t pwm_channel = TIM_CHANNEL_1;   // Select configured PWM channel number

const Tone *volatile melody_ptr;
volatile uint16_t melody_tone_count;
volatile uint16_t current_tone_number;
volatile uint32_t current_tone_end;
volatile uint16_t volume = 50;          // (0 - 1000)
volatile uint32_t last_button_press;


extern void PWM_Start() {
    HAL_TIM_PWM_Start(pwm_timer, pwm_channel);
}

void PWM_Change_Tone(uint16_t pwm_freq, uint16_t volume) { // pwm_freq (1 - 20000), volume (0 - 1000)
    if (pwm_freq == 0 || pwm_freq > 20000) {
        __HAL_TIM_SET_COMPARE(pwm_timer, pwm_channel, 0);
    }
    else {
        const uint32_t internal_clock_freq = HAL_RCC_GetSysClockFreq();
        const uint16_t prescaler = 1 + internal_clock_freq / pwm_freq / 60000;
        const uint32_t timer_clock = internal_clock_freq / prescaler;
        const uint32_t period_cycles = timer_clock / pwm_freq;
        const uint32_t pulse_width = volume * period_cycles / 1000 / 2;

        pwm_timer->Instance->PSC = prescaler - 1;
        pwm_timer->Instance->ARR = period_cycles - 1;
        pwm_timer->Instance->EGR = TIM_EGR_UG;
        __HAL_TIM_SET_COMPARE(pwm_timer, pwm_channel, pulse_width); // pwm_timer->Instance->CCR2 = pulse_width;
    }
}

void Change_Melody(const Tone *melody, uint16_t tone_count) {
    melody_ptr = melody;
    melody_tone_count = tone_count;
    current_tone_number = 0;
    PWM_Start();
}

void Update_Melody() {
    if ((HAL_GetTick() > current_tone_end) && (current_tone_number < melody_tone_count)) {
        const Tone active_tone = *(melody_ptr + current_tone_number);
        PWM_Change_Tone(active_tone.frequency, volume);
        current_tone_end = HAL_GetTick() + active_tone.duration;
        current_tone_number++;
    }
}
// Input pull down rising edge trigger interrupt pins:
// Row1 PD3, Row2 PD5, Row3 PD7, Row4 PB4
typedef unsigned char byte;
TIM_HandleTypeDef *buzzerPwmTimer;
uint32_t buzzerPwmChannel;
GPIO_TypeDef *const Row_ports[] = {GPIOD, GPIOD, GPIOD, GPIOD};
const uint16_t Row_pins[] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4};
// Output pins: Column1 PD4, Column2 PD6, Column3 PB3, Column4 PB5
GPIO_TypeDef *const Column_ports[] = {GPIOD, GPIOD, GPIOD, GPIOD};
const uint16_t Column_pins[] = {GPIO_PIN_0, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
volatile uint32_t last_gpio_exti;
int menuState=-1, tempTresh=40, sw1=0, ones, tens, buzzerForTemp=0, sw2=0, input=0, sw0=0, sw_1=0, pirIsOn=0, buzzerForPir=0, sw3=0, sw4=0;
char str[40];
//char* hiInput = "amir";
//char* byeTemp = "ali";
char substring[20] = "";
char hiTemp[20] = "amir";
char byeTemp[20] = "ali";
char byeSub[20] = "";
byte onLed[] = {0x0E, 0x1F, 0x1F, 0x1F, 0x0A, 0x0A, 0x0A, 0x08};
byte offLed[] = {0x0E, 0x11, 0x11, 0x1F, 0x0A, 0x0A, 0x0A, 0x08};
byte rightLove[] = {0x00, 0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x10};
byte leftLove[] = {0x00, 0x0E, 0x11, 0x10, 0x08, 0x04, 0x02, 0x01};
byte sleep[] = {0x07, 0x0E, 0x1C, 0x18, 0x18, 0x1C, 0x0E, 0x07};
int LED1=0, LED2=0, LED3=0, LED4=0, sw5=0, count=0, temp, sw_2=0, sw6=0, sw7=0, currentState=0, sw8=0, swThresh=0, secIsOn=0, sw_3=0, sleepIsOn=0;
int sw9=0, sw10=0, sw11=0, sw12=0, inputHi=0, hiPressed=0, keyState = 0, isBigger = 0, isNewScenario=0, sw14=0, sw13=0, sw15=0, sw16=0, sw18=0;
int sw17=0, sw19=0, isUser=0, isPass=0, v=0;
char in[2], empty[1] = "";

//char *username = "jalil";
//char *pass = "12345";
char uartInput[6];


struct newScenario{
	int isSleep;
	int buzzerForPir;
	int buzzerFortemp;
	int Pir;
	int LED1;
	int LED2;
	int LED3;
	int LED4;
	int tempTresh;
	char hiInput;
	char byeTemp;
	char name;
};

struct newScenario s1;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2){

		if (isUser == 0) {
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
			if ((uartInput[0] == 'j' && uartInput[1] == 'a' && uartInput[2] == 'l' && uartInput[3] == 'i' && uartInput[4] == 'l') || (uartInput[1] == 'j' && uartInput[2] == 'a' && uartInput[3] == 'l' && uartInput[4] == 'i' && uartInput[5] == 'l')) {
				isUser = 1;
				HAL_UART_Transmit(&huart2, "enter your password:\n", 21, 100);
				for(int i=0; i<5; i++) {
					uartInput[i] = '\0';
				}
				HAL_UART_Receive_IT(&huart2, uartInput, 6);
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 1);
			} else {
				HAL_UART_Transmit(&huart2, "your username was not correct\n", 30, 100);
				HAL_UART_Transmit(&huart2, "enter your username:\n", 21, 100);
				HAL_UART_Receive_IT(&huart2, uartInput, 6);
			}
		} else {

			if (isPass == 0) {
				if (uartInput[1] == '1' && uartInput[2] == '2' && uartInput[3] == '3' && uartInput[4] == '4' && uartInput[5] == '5') {
					isPass = 1;
					HAL_UART_Transmit(&huart2, "your password was correct\n", 26, 100);
					HAL_UART_Transmit(&huart2, "1-temp  2-sec  3-LED  4-scenario  5-sleep  6-exit\n", 50, 100);
					HAL_UART_Receive_IT(&huart2, in, 2);
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);
				} else {
					HAL_UART_Transmit(&huart2, "your password was not correct\n", 30, 100);
					HAL_UART_Transmit(&huart2, "enter your password:\n", 21, 100);
					HAL_UART_Receive_IT(&huart2, uartInput, 6);
				}
			} else {
				if (in[1] == '1' && menuState == 0) {
					menuState = 1;
				} else if (in[1] == '1' && menuState == 1) {
					if (buzzerForTemp == 1) {
						buzzerForTemp = 0;
					} else  {
						buzzerForTemp = 1;
					}
				} else if (in[1] == '0' && menuState == 1) {
					menuState = 0;
				} else if (in[1] == '2' && menuState ==0) {
					menuState = 3;
				} else if (in[1] == '1' && menuState == 3) {
					if (buzzerForPir == 1) {
						buzzerForPir = 0;
					} else {
						buzzerForPir = 1;
					}
				} else if (in[1] == '2' && menuState == 3) {
					if (pirIsOn == 1) {
						pirIsOn = 0;
					} else {
						pirIsOn = 1;
					}
				} else if (in[1] == '0' && menuState == 3) {
					menuState = 0;
				}
				if (menuState == 1) {
					if (buzzerForTemp == 0) {
						HAL_UART_Transmit(&huart2, "1-set buzzer off\n", 17, 100);
					} else {
						HAL_UART_Transmit(&huart2, "1-set buzzer on \n", 17, 100);
					}
					HAL_UART_Transmit(&huart2, "2-change threshold\n", 19, 100);
					HAL_UART_Receive_IT(&huart2, in, 2);
				} else if (menuState == 0) {
					HAL_UART_Transmit(&huart2, "1-temp  2-sec  3-LED  4-scenario  5-sleep  6-exit\n", 50, 100);
				} else if (menuState == 3) {
					if (buzzerForPir == 0) {
						HAL_UART_Transmit(&huart2, "1-set buzzer off\n", 17, 100);
					} else {
						HAL_UART_Transmit(&huart2, "1-set buzzer on \n", 17, 100);
					}

					if (pirIsOn == 0) {
						HAL_UART_Transmit(&huart2, "2-set PIR off\n", 14, 100);
					} else {
						HAL_UART_Transmit(&huart2, "2-set PIR on \n", 14, 100);
					}
					HAL_UART_Receive_IT(&huart2, in, 2);
				}

			}
		}
	}
}


void concatenate(char *str1, char *str2) {
    int i = strlen(str1), j = 0;

    for (j=0; j<strlen(str2); j++) {
        str1[i] = str2[j];
        i++;
    }

	if (i == 0) {
	i++;
	}
    str1[i] = '\0';  // declaring the end of the string
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (last_gpio_exti + 200 > HAL_GetTick()) // Simple button debouncing
  {
    return;
  }
  last_gpio_exti = HAL_GetTick();

  int8_t row_number = -1;
  int8_t column_number = -1;

  if (GPIO_Pin == GPIO_PIN_0) {
	  if (menuState != -2 && menuState != -3) {
		  count=0;
	  }
	  if (menuState == -1 && isPass == 1) {
		  menuState = 7;
	  }
    return;
  }

  if (GPIO_Pin == GPIO_PIN_13) {
//	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
	  if (menuState != -1 && menuState != -2 && menuState != 7 && menuState != 6 && menuState != -3 && count>2){
		  if (pirIsOn == 0) {
			  count = 0;
			  currentState = menuState;
			  menuState = -3;
		  }
	  }
      return;
    }

  for (uint8_t row = 0; row < 4; row++) // Loop through Rows
  {
    if (GPIO_Pin == Row_pins[row])
    {
      row_number = row;
    }
  }

  HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 0);
  HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 0);
  HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 0);
  HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 0);

  for (uint8_t col = 0; col < 4; col++) // Loop through Columns
  {
    HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 1);
    if (HAL_GPIO_ReadPin(Row_ports[row_number], Row_pins[row_number]))
    {
      column_number = col;
    }
    HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 0);
  }

  HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 1);
  HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 1);
  HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 1);
  HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 1);

  if (row_number == -1 || column_number == -1)
  {
    return; // Reject invalid scan
  }
  //   C0   C1   C2   C3
  // +----+----+----+----+
  // | 1  | 2  | 3  | 4  |  R0
  // +----+----+----+----+
  // | 5  | 6  | 7  | 8  |  R1
  // +----+----+----+----+
  // | 9  | 10 | 11 | 12 |  R2
  // +----+----+----+----+
  // | 13 | 14 | 15 | 16 |  R3
  // +----+----+----+----+
  const uint8_t button_number = row_number * 4 + column_number + 1;
  switch (button_number)
  {
  case 1:
    /* code */
	  //1
	  if (menuState != -2 && menuState != -3) {
		  count=0;
	  }
	  if (menuState == 0) {
		  menuState = 1;
	  } else if (menuState == 1) {
		  if (buzzerForTemp == 0) {
			  buzzerForTemp = 1;
			  HAL_UART_Transmit(&huart2, "buzzer for temp is off\n", 23, 100);
		  } else {
			  HAL_UART_Transmit(&huart2, "buzzer for temp is on\n", 22, 100);
			  buzzerForTemp = 0;
		  }
	  } else if (menuState == 2 && input == 0) {
		  tens = 1;
		  input = 1;
	  } else if (menuState == 2 && input == 1) {
		  ones = 1;
		  input = 0;
	  } else if (menuState == 3) {
		  if (pirIsOn == 0) {
			  HAL_UART_Transmit(&huart2, "PIR is off\n", 11, 100);
			  HAL_UART_Transmit(&huart2, "buzzer for temp is off\n", 23, 100);
			  pirIsOn = 1;
			  buzzerForPir = 1;
		  } else {
			  HAL_UART_Transmit(&huart2, "PIR is on\n", 10, 100);
			  pirIsOn = 0;
		  }
	  } else if (menuState == 4) {
		  if (LED1 == 0) {
			  HAL_UART_Transmit(&huart2, "LED1 is on\n", 11, 100);
			  LED1 = 1;
		  } else {
			  HAL_UART_Transmit(&huart2, "LED1 is off\n", 12, 100);
			  LED1 = 0;
		  }
	  } else if (menuState == 5) {
		  menuState = 14;
		  isNewScenario = 1;
	  } else if (menuState == 8) {
		  if (sleepIsOn == 0) {
			  HAL_UART_Transmit(&huart2, "sleep is off\n", 13, 100);
			  sleepIsOn = 1;
		  } else {
			  HAL_UART_Transmit(&huart2, "sleep is on\n", 12, 100);
			  sleepIsOn = 0;
		  }
	  } else if (menuState == 11) {
//		  inputHi = 0;
		  for (int i=0; i<20; i++) {
			  hiTemp[i] = '\0';
		  	}
		  menuState = 12;
	  } else if (menuState == 12) {
		  if (keyState == 0) {
			  inputHi++;
			  hiPressed = 0;
			  keyState = 1;
		  }

		  if (keyState == 1) {
			  for (int i=0; i<strlen(substring); i++) {
			  	  substring[i] = '\0';
		  	  }

		  	  if (hiPressed == 0) {
		  		  strncpy(substring,hiTemp,inputHi-1);
			  	  for (int i=0; i<strlen(hiTemp); i++) {
			  	  	  hiTemp[i] = '\0';
			  	  }

			  	  concatenate(hiTemp, substring);
			  	  if (isBigger == 0) {
			  		  concatenate(hiTemp, "a");
			  	  } else {
			  		concatenate(hiTemp, "A");
			  	  }
			  	  hiPressed++;
		  	  } else if (hiPressed == 1) {
			  	  strncpy(substring,hiTemp,inputHi-1);
//			  	hiInput = "";
			  	  for (int i=0; i<strlen(hiTemp); i++) {
				  	  hiTemp[i] = '\0';
			  	  }
			  	  concatenate(hiTemp, substring);
			  	if (isBigger == 0) {
			  				  		  concatenate(hiTemp, "b");
			  				  	  } else {
			  				  		concatenate(hiTemp, "B");
			  				  	  }
			  	  hiPressed++;
		  	  } else if(hiPressed == 2) {
		  		  strncpy(substring, hiTemp, inputHi-1);
		  		  for (int i=0; i<strlen(hiTemp); i++) {
		  			  hiTemp[i] = '\0';
		  		  }
		  		  concatenate(hiTemp, substring);
		  		if (isBigger == 0) {
		  					  		  concatenate(hiTemp, "c");
		  					  	  } else {
		  					  		concatenate(hiTemp, "C");
		  					  	  }
		  		  hiPressed=0;
		  	  }
		  }
	  } else if (menuState == 13) {
		  if (keyState == 0) {
			  inputHi++;
			  hiPressed = 0;
			  keyState = 1;
		  }

		  if (keyState == 1) {
			  for (int i=0; i<strlen(byeSub); i++) {
			  	  byeSub[i] = '\0';
		  	  }

		  	  if (hiPressed == 0) {
		  		  strncpy(byeSub,byeTemp,inputHi-1);
			  	  for (int i=0; i<strlen(byeTemp); i++) {
			  	  	  byeTemp[i] = '\0';
			  	  }

			  	  concatenate(byeTemp, byeSub);
			  	  if (isBigger == 0) {
			  		  concatenate(byeTemp, "a");
			  	  } else {
			  		concatenate(byeTemp, "A");
			  	  }
			  	  hiPressed++;
		  	  } else if (hiPressed == 1) {
			  	  strncpy(byeSub,byeTemp,inputHi-1);
//			  	hiInput = "";
			  	  for (int i=0; i<strlen(byeTemp); i++) {
				  	  byeTemp[i] = '\0';
			  	  }
			  	  concatenate(byeTemp, byeSub);
			  	if (isBigger == 0) {
			  				  		  concatenate(byeTemp, "b");
			  				  	  } else {
			  				  		concatenate(byeTemp, "B");
			  				  	  }
			  	  hiPressed++;
		  	  } else if(hiPressed == 2) {
		  		  strncpy(byeSub, byeTemp, inputHi-1);
		  		  for (int i=0; i<strlen(byeTemp); i++) {
		  			byeTemp[i] = '\0';
		  		  }
		  		  concatenate(byeTemp, byeSub);
		  		if (isBigger == 0) {
		  					  		  concatenate(byeTemp, "c");
		  					  	  } else {
		  					  		concatenate(byeTemp, "C");
		  					  	  }
		  		  hiPressed=0;
		  	  }
		  }
	  } else if (menuState == 14) {
		  s1.isSleep = 0;
		  menuState = 15;
	  } else if (menuState == 15) {
		  s1.buzzerForPir = 0;
		  menuState = 16;
	  } else if (menuState == 16) {
		  s1.buzzerFortemp = 0;
		  menuState = 17;
	  } else if (menuState == 17) {
		  s1.Pir = 0;
		  menuState = 18;
	  } else if (menuState == 18) {
		  if (s1.LED1 == 0) {
			  s1.LED1 = 1;
		  } else {
			  s1.LED1 = 0;
		  }
	  } else if (menuState == 20 && input == 0) {
		  tens = 1;
		  input = 1;
	  } else if (menuState == 20 && input == 1) {
		  ones = 1;
		  input = 0;
	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
    break;
  case 2:
    /* code */
	  //5
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
	  if (menuState == 2 && input == 0) {
	  	tens = 5;
	  	input = 1;
	  } else if (menuState == 2 && input == 1) {
		ones = 5;
		input = 0;
	  } else if (menuState == 20 && input == 0) {
		  	tens = 5;
		  	input = 1;
		  } else if (menuState == 20 && input == 1) {
			ones = 5;
			input = 0;
	  }else if (menuState == 0) {
		  menuState = 8;
	  } else if (menuState == 12) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 5;
		  		  }

		  		  if (keyState == 5) {
		  			  for (int i=0; i<strlen(substring); i++) {
		  			  	  substring[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  			  	  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "m");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "M");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  				  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "n");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "N");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(substring, hiTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(hiTemp); i++) {
		  		  			  hiTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(hiTemp, substring);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(hiTemp, "o");
		  		  					  	  } else {
		  		  					  		concatenate(hiTemp, "O");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  } else if (menuState == 13) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 5;
		  		  }

		  		  if (keyState == 5) {
		  			  for (int i=0; i<strlen(byeSub); i++) {
		  				byeSub[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "m");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "M");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  				  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "n");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "N");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(byeSub, byeTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(byeTemp); i++) {
		  		  			byeTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(byeTemp, byeSub);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(byeTemp, "o");
		  		  					  	  } else {
		  		  					  		concatenate(byeTemp, "O");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  }
    break;
  case 3:
    /* code */
	  //9
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
	  if (menuState == 2 && input == 0) {
	  	tens = 9;
	  	input = 1;
	  } else if (menuState == 2 && input == 1) {
		ones = 9;
		input = 0;
	  }	  else if (menuState == 20 && input == 0) {
		  	tens = 9;
		  	input = 1;
		  } else if (menuState == 20 && input == 1) {
			ones = 9;
			input = 0;
		  } else if (menuState == 12) {
		 		  if (keyState == 0) {
		 		  			  inputHi++;
		 		  			  hiPressed = 0;
		 		  			  keyState = 9;
		 		  		  }

		 		  		  if (keyState == 9) {
		 		  			  for (int i=0; i<strlen(substring); i++) {
		 		  			  	  substring[i] = '\0';
		 		  		  	  }

		 		  		  	  if (hiPressed == 0) {
		 		  		  		  strncpy(substring,hiTemp,inputHi-1);
		 		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		 		  			  	  	  hiTemp[i] = '\0';
		 		  			  	  }
		 		  			  	  concatenate(hiTemp, substring);
		 		  			  	  concatenate(hiTemp, " ");
		 		  			  	  hiPressed++;
		 		  		  	  }
		 		  		  }
		 	  }  else if (menuState == 13) {
		 		  if (keyState == 0) {
		 		  			  inputHi++;
		 		  			  hiPressed = 0;
		 		  			  keyState = 9;
		 		  		  }

		 		  		  if (keyState == 9) {
		 		  			  for (int i=0; i<strlen(byeSub); i++) {
		 		  				byeSub[i] = '\0';
		 		  		  	  }

		 		  		  	  if (hiPressed == 0) {
		 		  		  		  strncpy(byeSub,byeTemp,inputHi-1);
		 		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		 		  			  	  	  hiTemp[i] = '\0';
		 		  			  	  }
		 		  			  	  concatenate(byeTemp, byeSub);
		 		  			  	  concatenate(byeTemp, " ");
		 		  			  	  hiPressed++;
		 		  		  	  }
		 		  		  }
		 	  }
    break;
  case 4:
    /* code */
	  //13
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
    break;
  case 5:
    /* code */
	  //2
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  if (menuState == 0) {
		  menuState = 3;
	  } else if (menuState == 1) {
		  ones=0;
		  tens=0;
		  menuState = 2;
	  } else if (menuState == 2 && input == 0) {
  		  tens = 2;
  		  input = 1;
  	  } else if (menuState == 2 && input == 1) {
  		ones = 2;
  		input = 0;
  	  } else if (menuState == 20 && input == 0) {
  		  tens = 2;
  		  input = 1;
  	  } else if (menuState == 20 && input == 1) {
  		ones = 2;
  		input = 0;
  	  } else if(menuState == 3) {
  		  if (buzzerForPir == 0) {
  			  HAL_UART_Transmit(&huart2, "buzzer for pir is off\n", 22, 100);
  			  buzzerForPir = 1;
  		  } else {
  			HAL_UART_Transmit(&huart2, "buzzer for pir is on\n", 21, 100);
  			  buzzerForPir = 0;
  		  }
  	  } else if (menuState == 4) {
  		  if (LED2 == 0) {
  			HAL_UART_Transmit(&huart2, "LED2 is on\n", 11, 100);
  			  LED2 = 1;
  		  } else {
  			HAL_UART_Transmit(&huart2, "LED2 is off\n", 12, 100);
  			  LED2 = 0;
  		  }
  	  } else if (menuState == 5) {
  		  LED1 = 1;
  		  LED2 = 1;
  		  LED3 = 1;
  		  LED4 = 1;
  		  pirIsOn = 1;
  		  buzzerForPir = 1;
  		  buzzerForTemp = 0;
  		  sleepIsOn = 0;
  		  menuState = 9;
  		  HAL_UART_Transmit(&huart2, "enter scenario runing\n", 22, 100);
  	  } else if (menuState == 11) {
		  for (int i=0; i<20; i++) {
		  	    byeTemp[i] = '\0';
		  }
  		  menuState = 13;
  	  } else if (menuState == 12) {
  		if (keyState == 0) {
  			inputHi++;
  			hiPressed = 0;
  			keyState = 2;
  		}

  		if (keyState == 2) {
  			for (int i=0; i<strlen(substring); i++) {
  				  substring[i] = '\0';
  			}
  			if (hiPressed == 0) {
  				strncpy(substring,hiTemp,inputHi-1);

  				for (int i=0; i<strlen(hiTemp); i++) {
  					  hiTemp[i] = '\0';
  				}

  				concatenate(hiTemp, substring);
  				if (isBigger == 0) {
  							  		  concatenate(hiTemp, "d");
  							  	  } else {
  							  		concatenate(hiTemp, "D");
  							  	  }
  				hiPressed++;
  			} else if (hiPressed == 1) {
  				strncpy(substring, hiTemp, inputHi-1);

  				for (int i=0; i<strlen(hiTemp); i++) {
  					  hiTemp[i] = '\0';
  				}

  				concatenate(hiTemp, substring);
  				if (isBigger == 0) {
  							  		  concatenate(hiTemp, "e");
  							  	  } else {
  							  		concatenate(hiTemp, "E");
  							  	  }
  				hiPressed++;
  			} else if (hiPressed == 2) {
  				strncpy(substring, hiTemp, inputHi-1);
  				for (int i=0; i<strlen(hiTemp); i++) {
  				  	  hiTemp[i] = '\0';
  				 }
  				concatenate(hiTemp, substring);
  				if (isBigger == 0) {
  							  		  concatenate(hiTemp, "f");
  							  	  } else {
  							  		concatenate(hiTemp, "F");
  							  	  }
  				hiPressed=0;
  			}
  		}

  	  } else if (menuState == 13) {
    		if (keyState == 0) {
    			inputHi++;
    			hiPressed = 0;
    			keyState = 2;
    		}

    		if (keyState == 2) {
    			for (int i=0; i<strlen(byeSub); i++) {
    				byeSub[i] = '\0';
    			}
    			if (hiPressed == 0) {
    				strncpy(byeSub,byeTemp,inputHi-1);

    				for (int i=0; i<strlen(byeTemp); i++) {
    					byeTemp[i] = '\0';
    				}

    				concatenate(byeTemp, byeSub);
    				if (isBigger == 0) {
    							  		  concatenate(byeTemp, "d");
    							  	  } else {
    							  		concatenate(byeTemp, "D");
    							  	  }
    				hiPressed++;
    			} else if (hiPressed == 1) {
    				strncpy(byeSub, byeTemp, inputHi-1);

    				for (int i=0; i<strlen(byeTemp); i++) {
    					byeTemp[i] = '\0';
    				}

    				concatenate(byeTemp, byeSub);
    				if (isBigger == 0) {
    							  		  concatenate(byeTemp, "e");
    							  	  } else {
    							  		concatenate(byeTemp, "E");
    							  	  }
    				hiPressed++;
    			} else if (hiPressed == 2) {
    				strncpy(byeSub, byeTemp, inputHi-1);
    				for (int i=0; i<strlen(byeTemp); i++) {
    				  	  hiTemp[i] = '\0';
    				 }
    				concatenate(byeTemp, byeSub);
    				if (isBigger == 0) {
    							  		  concatenate(byeTemp, "f");
    							  	  } else {
    							  		concatenate(byeTemp, "F");
    							  	  }
    				hiPressed=0;
    			}
    		}

    	  } else if (menuState == 14) {
    		  s1.isSleep = 1;
    		  menuState = 15;
    	  } else if (menuState == 15) {
    		  s1.buzzerForPir = 1;
    		  menuState = 16;
    	  } else if (menuState == 16) {
    		  s1.buzzerFortemp = 1;
    		  menuState = 17;
    	  } else if (menuState == 17) {
    		  s1.Pir = 1;
    		  menuState = 18;
    	  } else if (menuState = 18) {
    		  if (s1.LED2 == 0) {
    			  s1.LED2 = 1;
    		  } else {
    			  s1.LED2 = 0;
    		  }
    	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
    break;
  case 6:
	  //6
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
	  if (menuState == 2 && input == 0) {
	  	tens = 6;
	  	input = 1;
	  } else if (menuState == 2 && input == 1) {
		ones = 6;
	  	input = 0;
	  } else if (menuState == 20 && input == 0) {
		  	tens = 6;
		  	input = 1;
	} else if (menuState == 20 && input == 1) {
			ones = 6;
		  	input = 0;
	  } else if (menuState == 0) {
		  currentState = menuState;
		  menuState = 6;
	  } else if (menuState == 12) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 6;
		  		  }

		  		  if (keyState == 6) {
		  			  for (int i=0; i<strlen(substring); i++) {
		  			  	  substring[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  			  	  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "p");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "P");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  				  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "q");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "Q");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(substring, hiTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(hiTemp); i++) {
		  		  			  hiTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(hiTemp, substring);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(hiTemp, "r");
		  		  					  	  } else {
		  		  					  		concatenate(hiTemp, "R");
		  		  					  	  }
		  		  		  hiPressed++;
		  		  	  } else if (hiPressed == 3) {
		  		  		  strncpy(substring, hiTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(hiTemp); i++) {
		  		  			  hiTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(hiTemp, substring);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(hiTemp, "s");
		  		  					  	  } else {
		  		  					  		concatenate(hiTemp, "S");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  } else if (menuState == 13) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 6;
		  		  }

		  		  if (keyState == 6) {
		  			  for (int i=0; i<strlen(byeSub); i++) {
		  				byeSub[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "p");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "P");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "q");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "Q");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(byeSub, byeTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(byeTemp); i++) {
		  		  			byeTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(byeTemp, byeSub);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(byeTemp, "r");
		  		  					  	  } else {
		  		  					  		concatenate(byeTemp, "R");
		  		  					  	  }
		  		  		  hiPressed++;
		  		  	  } else if (hiPressed == 3) {
		  		  		  strncpy(byeSub, byeTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(byeTemp); i++) {
		  		  			byeTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(byeTemp, byeSub);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(byeTemp, "s");
		  		  					  	  } else {
		  		  					  		concatenate(byeTemp, "S");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  }
    /* code */
    break;
  case 7:
	  //10
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  if (menuState == 12) {
	 		  if (keyState == 0) {
	 		  			  keyState = 10;
	 		  		  }

	 		  		  if (keyState == 10) {
	 		  			  if (isBigger == 0) {
	 		  				  isBigger = 1;
	 		  			  } else {
	 		  				  isBigger = 0;
	 		  			  }
	 		  		  }
	 	  } else if (menuState == 13) {
	 		  if (keyState == 0) {
	 		  			  keyState = 10;
	 		  		  }

	 		  		  if (keyState == 10) {
	 		  			  if (isBigger == 0) {
	 		  				  isBigger = 1;
	 		  			  } else {
	 		  				  isBigger = 0;
	 		  			  }
	 		  		  }
	 	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
    /* code */
    break;
  case 8:
	  //14
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);
    /* code */
    break;
  case 9:
    /* code */
	  //3
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  if (menuState == 2 && input == 0) {
	  	tens = 3;
	  	input = 1;
	  } else if (menuState == 2 && input == 1) {
		ones = 3;
		input = 0;
	  } if (menuState == 20 && input == 0) {
		  	tens = 3;
		  	input = 1;
		  } else if (menuState == 20 && input == 1) {
			ones = 3;
			input = 0;
		  } else if (menuState == 0) {
		  menuState = 4;
	  } else if (menuState == 4) {
		  if (LED3 == 0) {
			  HAL_UART_Transmit(&huart2, "LED3 is off\n", 12, 100);
			  LED3 = 1;
		  } else {
			  HAL_UART_Transmit(&huart2, "LED3 is on\n", 11, 100);
			  LED3 = 0;
		  }
	  } else if (menuState == 5) {
  		  LED1 = 0;
  		  LED2 = 0;
  		  LED3 = 0;
  		  LED4 = 0;
  		  pirIsOn = 0;
  		  buzzerForPir = 0;
  		  buzzerForTemp = 0;
  		  sleepIsOn = 1;
  		  menuState = 10;
	  } else if (menuState == 12) {
		  if (keyState == 0) {
			  inputHi++;
			  hiPressed = 0;
			  keyState = 3;
		  }

		  if (keyState == 3) {
			  if (hiPressed == 0) {
				  strncpy(substring, hiTemp, inputHi-1);
				  for (int i=0; i<strlen(hiTemp); i++) {
				    	hiTemp[i] = '\0';
				  }
				  concatenate(hiTemp, substring);
				  if (isBigger == 0) {
				  			  		  concatenate(hiTemp, "g");
				  			  	  } else {
				  			  		concatenate(hiTemp, "G");
				  			  	  }
				  hiPressed++;
			  } else if (hiPressed == 1) {
				  strncpy(substring, hiTemp, inputHi-1);
				  for (int i=0; i<strlen(hiTemp); i++) {
				  		hiTemp[i] = '\0';
				  }
				  concatenate(hiTemp, substring);
				  if (isBigger == 0) {
				  			  		  concatenate(hiTemp, "h");
				  			  	  } else {
				  			  		concatenate(hiTemp, "H");
				  			  	  }
				  hiPressed++;
			  } else if (hiPressed ==  2) {
				  strncpy(substring, hiTemp, inputHi-1);
				  for (int i=0; i<strlen(hiTemp); i++) {
					  	hiTemp[i] = '\0';
				  }
				  concatenate(hiTemp, substring);
				  if (isBigger == 0) {
				  			  		  concatenate(hiTemp, "i");
				  			  	  } else {
				  			  		concatenate(hiTemp, "I");
				  			  	  }
				  hiPressed=0;
			  }
		  }
	  } else if (menuState == 13) {
		  if (keyState == 0) {
			  inputHi++;
			  hiPressed = 0;
			  keyState = 3;
		  }

		  if (keyState == 3) {
			  if (hiPressed == 0) {
				  strncpy(byeSub, byeTemp, inputHi-1);
				  for (int i=0; i<strlen(byeTemp); i++) {
					  byeTemp[i] = '\0';
				  }
				  concatenate(byeTemp, byeSub);
				  if (isBigger == 0) {
				  			  		  concatenate(byeTemp, "g");
				  			  	  } else {
				  			  		concatenate(byeTemp, "G");
				  			  	  }
				  hiPressed++;
			  } else if (hiPressed == 1) {
				  strncpy(byeSub, byeTemp, inputHi-1);
				  for (int i=0; i<strlen(byeTemp); i++) {
					  byeTemp[i] = '\0';
				  }
				  concatenate(byeTemp, byeSub);
				  if (isBigger == 0) {
				  			  		  concatenate(byeTemp, "h");
				  			  	  } else {
				  			  		concatenate(byeTemp, "H");
				  			  	  }
				  hiPressed++;
			  } else if (hiPressed ==  2) {
				  strncpy(byeSub, byeTemp, inputHi-1);
				  for (int i=0; i<strlen(byeTemp); i++) {
					  byeTemp[i] = '\0';
				  }
				  concatenate(byeTemp, byeSub);
				  if (isBigger == 0) {
				  			  		  concatenate(byeTemp, "i");
				  			  	  } else {
				  			  		concatenate(byeTemp, "I");
				  			  	  }
				  hiPressed=0;
			  }
		  }
	  } else if (menuState == 18) {
		  if (s1.LED3 == 0) {
			  s1.LED3 = 1;
		  } else {
			  s1.LED3 = 0;
		  }
	  }
    break;
  case 10:
    /* code */
	  //7
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  if (menuState == 2 && input == 0) {
	  	tens = 7;
	  	input = 1;
	  } else if (menuState == 2 && input == 1) {
		ones = 7;
		input = 0;
	  }if (menuState == 20 && input == 0) {
		  	tens = 7;
		  	input = 1;
	  } else if (menuState == 20 && input == 1) {
			ones = 7;
			input = 0;
	  } if (menuState == 0) {
		menuState = 11;
	  } else if (menuState == 12) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 7;
		  		  }

		  		  if (keyState == 7) {
		  			  for (int i=0; i<strlen(substring); i++) {
		  			  	  substring[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  			  	  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "t");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "T");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  				  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "u");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "U");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(substring, hiTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(hiTemp); i++) {
		  		  			  hiTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(hiTemp, substring);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(hiTemp, "v");
		  		  					  	  } else {
		  		  					  		concatenate(hiTemp, "V");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  } else if (menuState == 13) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 7;
		  		  }

		  		  if (keyState == 7) {
		  			  for (int i=0; i<strlen(byeSub); i++) {
		  				byeSub[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "t");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "T");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "u");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "U");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(byeSub, byeTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(byeTemp); i++) {
		  		  			byeTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(byeTemp, byeSub);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(byeTemp, "v");
		  		  					  	  } else {
		  		  					  		concatenate(byeTemp, "V");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  }
    break;
  case 11:
    /* code */
	  //11
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
    break;
  case 12:
    /* code */
	  //15
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
    break;
  case 13:
    /* code */
	  //4
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  if (menuState == 2 && input == 0) {
	  	tens = 4;
	  	input = 1;
	  } else if (menuState == 2 && input == 1) {
		  ones = 4;
		  input = 0;
	  } if (menuState == 20 && input == 0) {
		  	tens = 4;
		  	input = 1;
		  } else if (menuState == 20 && input == 1) {
			  ones = 4;
			  input = 0;
		  } else if (menuState == 4) {
		  if (LED4 == 0) {
			  HAL_UART_Transmit(&huart2, "LED4 is off\n", 12, 100);
			  LED4 = 1;
		  } else {
			  HAL_UART_Transmit(&huart2, "LED4 is on\n", 11, 100);
			  LED4 = 0;
		  }
	  } else if(menuState == 0) {
		  menuState = 5;
	  } else if (menuState == 12) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 4;
		  		  }

		  		  if (keyState == 4) {
		  			  for (int i=0; i<strlen(substring); i++) {
		  			  	  substring[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  			  	  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "j");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "J");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  				  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "k");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "K");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(substring, hiTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(hiTemp); i++) {
		  		  			  hiTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(hiTemp, substring);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(hiTemp, "l");
		  		  					  	  } else {
		  		  					  		concatenate(hiTemp, "L");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  } else if (menuState == 13) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 4;
		  		  }

		  		  if (keyState == 4) {
		  			  for (int i=0; i<strlen(byeSub); i++) {
		  				byeSub[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "j");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "J");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "k");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "K");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(byeSub, byeTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(byeTemp); i++) {
		  		  			byeTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(byeTemp, byeSub);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(byeTemp, "l");
		  		  					  	  } else {
		  		  					  		concatenate(byeTemp, "L");
		  		  					  	  }
		  		  		  hiPressed=0;
		  		  	  }
		  		  }
	  } else if (menuState == 18) {
		  if (s1.LED4 == 0) {
			  s1.LED4 = 1;
		  } else {
			  s1.LED4 = 0;
		  }
	  } else if (menuState == 5 && isNewScenario == 1) {
		  sleepIsOn = s1.isSleep;
		  buzzerForPir = s1.buzzerForPir;
		  buzzerForTemp = s1.buzzerFortemp;
		  pirIsOn = s1.Pir;
		  LED1 = s1.LED1;
		  LED2 = s1.LED2;
		  LED3 = s1.LED3;
		  LED4 = s1.LED4;
		  menuState = 19;
		  tempTresh = s1.tempTresh;
		  HAL_UART_Transmit(&huart2, "runing new scenario\n", 20, 100);
	  }
    break;
  case 14:
    /* code */
	  //8
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  if (menuState == 2 && input == 0) {
	  	tens = 8;
	  	input = 1;
	  } else if (menuState == 2 && input == 1) {
		  	ones = 8;
			input = 0;
	  } if (menuState == 20 && input == 0) {
		  	tens = 8;
		  	input = 1;
	} else if (menuState == 20 && input == 1) {
			  	ones = 8;
				input = 0;
	  } else if (menuState == 12) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 8;
		  		  }

		  		  if (keyState == 8) {
		  			  for (int i=0; i<strlen(substring); i++) {
		  			  	  substring[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  			  	  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "w");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "W");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(substring,hiTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(hiTemp); i++) {
		  				  	  hiTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(hiTemp, substring);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(hiTemp, "x");
		  			  				  	  } else {
		  			  				  		concatenate(hiTemp, "X");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(substring, hiTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(hiTemp); i++) {
		  		  			  hiTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(hiTemp, substring);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(hiTemp, "y");
		  		  					  	  } else {
		  		  					  		concatenate(hiTemp, "Y");
		  		  					  	  }
		  		  		  hiPressed++;
		  		  	  } else if (hiPressed == 3) {
		  		  		strncpy(substring, hiTemp, inputHi-1);
		  		  		for (int i=0; i<strlen(hiTemp); i++) {
		  		  			  hiTemp[i] = '\0';
		  		  		}
		  		  		concatenate(hiTemp, substring);
		  		  	if (isBigger == 0) {
		  		  				  		  concatenate(hiTemp, "z");
		  		  				  	  } else {
		  		  				  		concatenate(hiTemp, "Z");
		  		  				  	  }
		  		  		hiPressed=0;
		  		  	  }
		  		  }
	  } else if (menuState == 13) {
		  if (keyState == 0) {
		  			  inputHi++;
		  			  hiPressed = 0;
		  			  keyState = 8;
		  		  }

		  		  if (keyState == 8) {
		  			  for (int i=0; i<strlen(byeSub); i++) {
		  				byeSub[i] = '\0';
		  		  	  }

		  		  	  if (hiPressed == 0) {
		  		  		  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "w");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "W");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if (hiPressed == 1) {
		  			  	  strncpy(byeSub,byeTemp,inputHi-1);
		  			  	  for (int i=0; i<strlen(byeTemp); i++) {
		  			  		byeTemp[i] = '\0';
		  			  	  }
		  			  	  concatenate(byeTemp, byeSub);
		  			  	if (isBigger == 0) {
		  			  				  		  concatenate(byeTemp, "x");
		  			  				  	  } else {
		  			  				  		concatenate(byeTemp, "X");
		  			  				  	  }
		  			  	  hiPressed++;
		  		  	  } else if(hiPressed == 2) {
		  		  		  strncpy(byeSub, byeTemp, inputHi-1);
		  		  		  for (int i=0; i<strlen(byeTemp); i++) {
		  		  			byeTemp[i] = '\0';
		  		  		  }
		  		  		  concatenate(byeTemp, byeSub);
		  		  		if (isBigger == 0) {
		  		  					  		  concatenate(byeTemp, "y");
		  		  					  	  } else {
		  		  					  		concatenate(byeTemp, "Y");
		  		  					  	  }
		  		  		  hiPressed++;
		  		  	  } else if (hiPressed == 3) {
		  		  		strncpy(byeSub, byeTemp, inputHi-1);
		  		  		for (int i=0; i<strlen(byeTemp); i++) {
		  		  		byeTemp[i] = '\0';
		  		  		}
		  		  		concatenate(byeTemp, byeSub);
		  		  	if (isBigger == 0) {
		  		  				  		  concatenate(byeTemp, "z");
		  		  				  	  } else {
		  		  				  		concatenate(byeTemp, "Z");
		  		  				  	  }
		  		  		hiPressed=0;
		  		  	  }
		  		  }
	  }
    break;
  case 15:
    /* code */
	  //12
	  if (menuState != -3) {
		  count = 0;
	  }
	  if (menuState != -2) {
		  count=0;
	  } else {
		  tempTresh--;
	  } if (menuState == 2 && input == 0) {
		tens = 0;
		input = 1;
	  } else if (menuState == 2 && input == 1) {
		  ones = 0;
		  input = 0;
	  } if (menuState == 20 && input == 0) {
			tens = 0;
			input = 1;
		  } else if (menuState == 20 && input == 1) {
			  ones = 0;
			  input = 0;
		  }
    break;
  case 16:
	  /* code */
	  //16
	  if (menuState != -2 && menuState != -3) {
	  		  count=0;
	  	  }
	  if (menuState == 2) {
		  menuState = 1;
		  tempTresh = tens*10 + ones;
		  sprintf(str, "temp thresh is hanged to: %d", tempTresh);
		  HAL_UART_Transmit(&huart2, str, strlen(str), 100);
		  HAL_UART_Transmit(&huart2, "\n", 1, 100);
	  } else if (menuState == 1) {
		  menuState = 0;
	  } else if (menuState == 3) {
		  menuState = 0;
	  } else if (menuState == 4) {
		  menuState = 0;
	  } else if (menuState == 5) {
		  menuState = 0;
	  } else if (menuState == -2) {
		  tempTresh++;
	  } else if (menuState == 8) {
		  menuState = 0;
	  } else if (menuState == 12) {
//		  for (int i=0; i<strlen(hiTemp); i++) {
//			  hiInput[i] = hiTemp[i];
//			  hiTemp[i] = 0;
//		  }
//		  sprintf(hiInput, "%s", hiTemp);
//		  hiInput = &hiTemp[0];
		  keyState = 0;
		  hiPressed = 0;
		  inputHi = 0;
		  isBigger = 0;
//		  for (int i=0; i<strlen(hiTemp); i++) {
//			  	hiTemp[i] = '\0';
//		  }
		  sprintf(str, "hi message changed to: %s", hiTemp);
		  HAL_UART_Transmit(&huart2, str, strlen(str), 100);
		  HAL_UART_Transmit(&huart2, "\n", 1, 100);
		  for (int i=0; i<20; i++) {
		  	  substring[i] = '\0';
	  	  }
		  menuState = 11;
	  } else if (menuState == 11) {
		  menuState = 0;
	  } else if (menuState == 13) {
//		  byeTemp = &byeTemp[0];
		  keyState = 0;
		  hiPressed=0;
		  inputHi=0;
		  isBigger=0;
		  sprintf(str, "bye message changed to: %s", byeTemp);
		  HAL_UART_Transmit(&huart2, str, strlen(str), 100);
		  HAL_UART_Transmit(&huart2, "\n", 1, 100);
		  for (int i=0; i<20; i++) {
			  byeSub[i] = '\0';
		  }
		  menuState = 11;
	  } else if (menuState == 18) {
		  tens = 0;
		  ones = 0;
		  menuState = 20;
	  } else if (menuState == 20) {
		  s1.tempTresh = tens*10+ones;
		  menuState = 5;
	  }
    break;
  }
}

void buzzerInit() {
    buzzerPwmTimer = &htim2;
    buzzerPwmChannel = TIM_CHANNEL_1;
    HAL_TIM_PWM_Start(buzzerPwmTimer, buzzerPwmChannel);
}

void buzzerChangeTone(uint16_t freq, uint16_t volume) {
    if (freq == 0 || freq > 20000) {
        __HAL_TIM_SET_COMPARE(buzzerPwmTimer, buzzerPwmChannel, 0);
    } else {
        const uint32_t internalClockFreq = HAL_RCC_GetSysClockFreq();
        const uint32_t prescaler = 1 + internalClockFreq / freq / 60000;
        const uint32_t timerClock = internalClockFreq / prescaler;
        const uint32_t periodCycles = timerClock / freq;
        const uint32_t pulseWidth = volume * periodCycles / 1000 / 2;

        buzzerPwmTimer->Instance->PSC = prescaler - 1;
        buzzerPwmTimer->Instance->ARR = periodCycles - 1;
        buzzerPwmTimer->Instance->EGR = TIM_EGR_UG;

        __HAL_TIM_SET_COMPARE(buzzerPwmTimer, buzzerPwmChannel, pulseWidth);
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {
    	uint32_t y = HAL_ADC_GetValue(&hadc1);
    	temp = (y*3300/40950)/3.5;

    } if (hadc->Instance == ADC2) {
    	uint32_t x = HAL_ADC_GetValue(&hadc2);
    	v = x/4 - 100;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3) {
    	count = count+1;
    	HAL_ADC_Start_IT(&hadc1);
    	HAL_ADC_Start_IT(&hadc2);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, LED1);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, LED2);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, LED3);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, LED4);
    	if (menuState == -1) {
    		if (sw_1 == 0) {
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
      			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw_1 = 1;
    		}
//    		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
    		setCursor(0, 0);
    		print("      sleeping   ");
//    		setCursor(0, 1);
//    		sprintf(str, "volume = %d", v);
    		print(str);
    		//    		scrollDisplayRight();
    		sw1 = 0;
    	} else {
    		sw_1 = 0;
    	}
    	if (menuState == 0) {
//    		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 1);
    		if (sw0 == 0) {
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
      			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw0 = 1;
    		}
    		setCursor(0, 0);
    		print ("1-temp    4-scenario");
    		setCursor(0, 1);
    		print ("2-security   5-sleep");
    		setCursor(0, 2);
    		print ("3-LED        6-exit ");
    		setCursor(0, 3);
    		print("7- change messages");
    		sw1 = 0;
    	} else {
    		sw0 = 0;
    	}
    	if (menuState == 1) {
//    		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 1);
    		if (sw1 == 0) {
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
      			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw1 = 1;
    		}
    		setCursor(0, 0);
    		sprintf(str , "Thresh= %d temp= %d", tempTresh, temp);
    		print(str);
    		setCursor(0, 1);
    		if (buzzerForTemp == 0) {
    			print("buzzer = on ");
    		} else {
    			print("buzzer = off");
    		}
    		setCursor(0, 2);
    		if (buzzerForTemp == 0) {
    			print("1- set buzzer off");
    		} else {
    			print("1- set buzzer on ");
    		}
    		setCursor(0, 3);
    		print("2 - change threshold");

    	} else {
    		sw1 = 0;
    	}

    	if (menuState == 2 ) {

    		if (sw2 == 0) {
    			input = 0;
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
      			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw2 = 1;
    		}

    		setCursor(0, 0);
    		sprintf(str,"tempThresh = %d%d",tens, ones);
    		print(str);
    	} else {
    		sw2 = 0;
    	}

    	if (menuState == 3) {
    		if (sw3 == 0) {
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
      			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw3 = 1;
    		}
    		setCursor(0, 0);
    		if (pirIsOn == 0) {
    			print("PIR = on ");
    		} else {
    			print("PIR = off");
    		}
    		setCursor(0, 1);
    		if (buzzerForPir == 0) {
    			print("buzzer = on ");
    		} else {
    			print("buzzer = off");
    		}
    		setCursor(0, 2);
    		if (pirIsOn == 0) {
    			print("1- set PIR off");
    		} else {
    			print("1- set PIR on ");
    		}
    		setCursor(0, 3);
    		if (buzzerForPir == 0) {
    			print("2- set buzzer off");
    		} else {
    			print("2- set buzzer on ");
    		}
    	} else {
    		sw3 = 0;
    	}

    	if (menuState == 4) {
    		if (sw4 == 0)  {
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
    			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw4 = 1;
    		}
    		setCursor(0, 0);
    		print("LED 1");
    		if (LED1 == 0) {
    			write(0);
    		} else {
    			write(1);
    		}
    		print("      LED 2");
    		if (LED2 == 0) {
    		    write(0);
    		} else {
    			write(1);
    		}
    		setCursor(0, 1);
    		print("LED 3");
    		if (LED3 == 0) {
    			write(0);
    		} else {
    			write(1);
    		}
    		print("      LED 4");
    		if (LED4 == 0) {
    			write(0);
    		} else {
    			write(1);
    		}
    		setCursor(0, 2);
    		if (LED1 == 0) {
    			print("1-LED1 on ");
    		} else {
    			print("1-LED1 off");
    		}

    		if (LED2 == 0) {
    			print("2-LED2 on ");
    		} else {
    			print("2-LED2 off");
    		}

    		setCursor(0, 3);
    		if (LED3 == 0) {
    		    print("3-LED3 on ");
    		} else {
    			print("3-LED3 off");
    		}

    		if (LED4 == 0) {
    		    print("4-LED4 on ");
    		} else {
    			print("4-LED4 off");
    		}
    	} else {
    		sw4 = 0;
    	}

    	if (menuState == 5) {
    		if (sw5 == 0)  {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw5 = 1;
    		 }

    		setCursor(0, 0);
    		if (isNewScenario == 0) {
    			print("1- new scenario     ");
    		} else {
    			print("1- change scenario");
    		}
    		setCursor(0, 1);
    		print("2- enter scenario");
    		setCursor(0, 2);
    		print("3- exit scenario");
    		if (isNewScenario ==  1) {
    			setCursor(0, 3);
    			print("4- new scenario");
    		}
    	} else {
    		sw5 = 0;
    	}

    	if (menuState == 6) {
    		if (sw6 == 0)  {
    			Change_Melody(pink_panther, ARRAY_LENGTH(pink_panther));
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw6 = 1;
    		 }
    		setCursor(0, 0);
    		sprintf(str, "      bye %s", byeTemp);
    		print(str);
    		setCursor(0, 1);
    		print("                    ");
    		setCursor(0, 2);
    		print("                    ");
    		setCursor(0, 3);
    		print("                    ");
    		menuState = -1;
    	} else {
    		sw6 = 0;
    	}

    	if (menuState == 7) {
    		if (sw7 == 0)  {
    			Change_Melody(pacman, ARRAY_LENGTH(pacman));
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw7 = 1;
    		 }
    		setCursor(0, 0);
    		sprintf(str, "      hi %s", hiTemp);
    		print(str);
    		setCursor(0, 1);
//    		sprintf(str, "      hi %s", hiTemp);
//    		print(str);
    		print("                    ");
    		setCursor(0, 2);
    		print("                    ");
    		setCursor(0, 3);
    		print("                    ");
    		menuState = currentState;
    	} else {
    		sw7 = 0;
    	}

    	if (menuState == 8) {
    		if (sw9 == 0)  {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw9 = 1;
    		 }
    		setCursor(0, 0);
    		if (sleepIsOn == 0) {
    			print("sleep = on ");
    		} else {
    			print("sleep = off");
    		}
    		write(4);
    		setCursor(0, 1);
    		if (sleepIsOn == 0) {
    			print("1- set sleep off");
    		} else {
    			print("1- set sleep on ");
    		}
    	} else {
    		sw9 = 0;
    	}

    	if (menuState == 9) {
    		setCursor(0, 0);
    		print("  runing enter sen  ");
		    setCursor(0, 1);
		    print("                    ");
		    setCursor(0, 2);
		    print("                    ");
		    setCursor(0, 3);
		    print("                    ");
		    menuState = 5;
    	}

    	if (menuState == 10) {
    		setCursor(0, 0);
    		print("  runing exit sen   ");
		    setCursor(0, 1);
		    print("                    ");
		    setCursor(0, 2);
		    print("                    ");
		    setCursor(0, 3);
		    print("                    ");
		    menuState = 5;
    	}

    	if (menuState == 11) {
    		if (sw10 == 0)  {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw10 = 1;
    		 }
    		setCursor(0, 0);
    		sprintf(str, "hi  message: %s", hiTemp);
    		print(str);
    		setCursor(0, 1);
    		sprintf(str, "bye message: %s", byeTemp);
    		print(str);
    		setCursor(0, 2);
    		print("1- set hi message");
    		setCursor(0, 3);
    		print ("2- set bye message");
    	} else {
    		sw10 = 0;
    	}

    	if (menuState == 12) {
    		if (sw11 == 0)  {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw11 = 1;
    		 }
    		setCursor(0, 0);
    		sprintf(str, "hi message: %s", hiTemp);
    		print(str);
    		setCursor(0, 1);
//    		print("                    ");
    		sprintf(str, "str = %s", substring);
    		print(str);
    		setCursor(0, 2);
//    		print("                    ");
//    		sprintf(str, "str = %s", hiInput);
//    		print(str);
    	} else {
    		sw11 = 0;
    	}

    	if (menuState == 13) {

        		if (sw12 == 0)  {
        		    setCursor(0, 0);
        		    print("                    ");
        		    setCursor(0, 1);
        		    print("                    ");
        		    setCursor(0, 2);
        		    print("                    ");
        		    setCursor(0, 3);
        		    print("                    ");
        		    sw12 = 1;
        		 }
        		setCursor(0, 0);
        		sprintf(str, "bye message: %s", byeTemp);
        		print(str);
        		setCursor(0, 1);
    //    		print("                    ");
        		sprintf(str, "str = %s", byeSub);
        		print(str);
//        		setCursor(0, 2);
    //    		print("                    ");
    //    		sprintf(str, "str = %s", byeTemp);
    //    		print(str);
    	} else {
    		sw12 = 0;
    	}

    	if (menuState == 14) {
    		if (sw13 == 0) {
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
    			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw13 = 1;
    		}
    		setCursor(0, 0);
    		print ("1- set sleep on ");
    		setCursor(0, 1);
    		print ("2- set sleep off");

    	} else {
    		sw13 = 0;
    	}

    	if (menuState == 15) {
    		if (sw14 == 0) {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw14 = 1;
    		}
    		setCursor(0, 0);
    		print("1-set pir buz on");
    		setCursor(0, 1);
    		print("2-set pir buz off");

    	} else {
    		sw14 = 0;
    	}

    	if (menuState == 16) {
    		if (sw15 == 0) {
    			setCursor(0, 0);
    			print("                    ");
    			setCursor(0, 1);
    			print("                    ");
    			setCursor(0, 2);
    			print("                    ");
    			setCursor(0, 3);
    			print("                    ");
    			sw15 = 1;
    		}
    		setCursor(0, 0);
    		print("1-set temp buz on");
    		setCursor(0, 1);
    		print("2-set temp buz off");
    	} else {
    		sw15 = 1;
    	}

    	if (menuState == 17) {
    		if (sw16 == 0) {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw16 = 1;
    		}
    		setCursor(0, 0);
    		print("1-set pir on");
    		setCursor(0, 1);
    		print("2-set pir off");
    	} else {
    		sw16 = 0;
    	}

    	if (menuState == 18) {
    		if (sw17 == 0) {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw17 = 1;
    		}
    		setCursor(0, 0);
    		if (s1.LED1 == 0)  {
    			print("1- set LED1 on ");
    		} else {
    			print("1- set LED1 off");
    		}
    		setCursor(0, 1);
    		if (s1.LED2 == 0) {
    			print("2- set LED2 on ");
    		} else {
    			print("2- set LED2 off");
    		}
    		setCursor(0, 2);
    		if (s1.LED3 == 0) {
    			print("3- set LED3 on ");
    		} else {
    			print("3- set LED3 off");
    		}
    		setCursor(0, 3);
    		if (s1.LED4 == 0) {
    			print("4- set LED4 on ");
    		} else {
    			print("4- set LED4 off");
    		}
    	} else {
    		sw17 = 1;
    	}

    	if (menuState == 19) {
    		setCursor(0, 0);
    		print("  runing new sen   ");
    		setCursor(0, 1);
    		print("                    ");
    		setCursor(0, 2);
    		print("                    ");
    		setCursor(0, 3);
    		print("                    ");
    		menuState = 5;
    	}

    	if (menuState == 20) {
    		if (sw18 == 0) {
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw18 = 1;
    		}
    		setCursor(0, 0);
    		sprintf(str, "tempTresh = %d%d", tens, ones);
    		print(str);
    	} else {
    		sw18 = 0;
    	}

    	if (menuState == -2) {
    		if (sw_2 == 0)  {

    			count = 0;
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw_2 = 1;
    		}
    		if (buzzerForTemp == 0) {
    		    buzzerChangeTone(v, 100);
    		}
    		if (buzzerForTemp == 0) {
    			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
    		}
    		setCursor(0, 0);
    		print("temperature is high");
    		setCursor(0, 1);
    		sprintf(str , "Thresh=%d temp= %d", tempTresh, temp);
    		print(str);
    		write(2);
    		write(3);
    		setCursor(0, 2);
    		sprintf(str , "count = %d", count);
    		print(str);


    	} else {
    		sw_2 = 0;
    	}

    	if (menuState == -3) {
    		if (sw_3 == 0) {

    			count = 0;
    		    setCursor(0, 0);
    		    print("                    ");
    		    setCursor(0, 1);
    		    print("                    ");
    		    setCursor(0, 2);
    		    print("                    ");
    		    setCursor(0, 3);
    		    print("                    ");
    		    sw_3 = 1;
    		}
    		if (buzzerForPir == 0) {
    			buzzerChangeTone(v, 100);
    		}
    		if (buzzerForPir == 0) {
    			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
    		}
    		setCursor(0, 0);
    		print("    security is on     ");
    		setCursor(0, 1);
    		sprintf(str, "count = %d", count);
    		print(str);
		    setCursor(0, 2);
		    print("                    ");
    	} else {
    		sw_3 = 0;
    	}

    	if (count >= 50 && menuState != -1 && sleepIsOn == 0) {
    		if (menuState != -2 && menuState != -3) {
    			if (sw8 == 0) {
    				currentState = menuState;
    				sw8=1;
    			}

    			menuState = 6;
    		}
    	} else {
    		sw8=0;
    	}

    	if (temp > tempTresh) {
    		if (menuState != -1 && menuState !=-3 && menuState !=  -2) {
    			if (swThresh == 0) {
    				currentState = menuState;
    				swThresh = 1;
    			}
    			menuState = -2;
    		}
    	} else {
    		swThresh = 0;
    	}

    	if (count >= 10 && menuState == -2) {
    		if (temp < tempTresh) {
    			menuState = currentState;
    			count = 0;
    			buzzerChangeTone(0, 0);
    			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
    		}
    	}

    	if (count >= 10 && menuState == -3) {
			menuState = currentState;
			count = 0;
			buzzerChangeTone(0, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
    	}

    	if  (count >= 10) {
    		keyState = 0;
    	}



    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
  buzzerInit();


  LiquidCrystal(GPIOD, GPIO_PIN_8,  GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
  begin(20, 4);
  createChar(0, offLed);
  createChar(1, onLed);
  createChar(2, leftLove);
  createChar(3, rightLove);
  createChar(4, sleep);
//  print("   sleeping   ");
  HAL_TIM_Base_Start_IT(&htim3);
  s1.LED1 = 0;
  s1.LED2 = 0;
  s1.LED3 = 0;
  s1.LED4 = 0;
  HAL_UART_Transmit(&huart2, "enter your username:\n", 21, 100);
  HAL_UART_Receive_IT(&huart2, uartInput, 5);
//  Change_Melody(pink_panther, ARRAY_LENGTH(pink_panther));




//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);
//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 1);
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);

//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 1);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);

//  buzzerChangeTone(100, 100);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
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
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7499;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_0
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 PD0
                           PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_0
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD1 PD2 PD3 PD4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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

#ifdef  USE_FULL_ASSERT
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
