#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define readUserInput() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
#define Time_LED3 120
#define Time_LED4 500
#define Time_LED5 200
#define Time_LED6 2000

typedef enum {
				START,
				LED_OFF,
				LED_ON,
}State;

enum {
				LED3 = 0,
				LED4,
				LED5,
				LED6
};

uint32_t getCurrentTime();
void delay(uint32_t delayCycle);
void initLED();
void configButton();
void turnOnLED(int LED);
void turnOffLED(int LED);
void SD_LED(State *state,int LED,int Time);


int main(void)
{
	State state_1 = START , state_2 = START, state_3 = START, state_4 = START ;

	initLED();
	configButton();

    while(1)
    {

    	SD_LED(&state_1,LED3,Time_LED3);
    	SD_LED(&state_2,LED4,Time_LED4);
    	SD_LED(&state_3,LED5,Time_LED5);
    	SD_LED(&state_4,LED6,Time_LED6);

    }
}

void initLED()
{
	GPIO_InitTypeDef GpioInfo ;

	__GPIOG_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP ;
	GpioInfo.Pin = GPIO_PIN_13 | GPIO_PIN_14; // Init PG13 and PG14
	GpioInfo.Pull = GPIO_NOPULL ;
	GpioInfo.Speed = GPIO_SPEED_HIGH ;

	//Init LED on PG13 & PG14
		HAL_GPIO_Init(GPIOG,&GpioInfo);

	GpioInfo.Pin = GPIO_PIN_13; // Init PB13
	//Init LED on PB13
	HAL_GPIO_Init(GPIOB,&GpioInfo);

	GpioInfo.Pin = GPIO_PIN_5 ; // Init PC5
	//Init LED on PC5
	HAL_GPIO_Init(GPIOC,&GpioInfo);
}

void configButton()
{
	GPIO_InitTypeDef GpioInfo ;
	__GPIOA_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_INPUT ;
	GpioInfo.Pin = GPIO_PIN_0; // Init PA0
	GpioInfo.Pull = GPIO_NOPULL ;
	GpioInfo.Speed = GPIO_SPEED_HIGH ;

	//Init Pushbutton on PA0
	HAL_GPIO_Init(GPIOA,&GpioInfo);
}

uint32_t getCurrentTime()
{
	static uint32_t counter = 0 ;
	static uint32_t currentTime = 0 ;

	if (counter++ >= 100)
	{
		counter = 0 ;
		currentTime ++ ;
	}

	return currentTime ;
}


void delay(uint32_t delayCycle)
{
	static uint32_t previousTime = 0 ;

	while ( (getCurrentTime() - previousTime) < delayCycle)
		previousTime = getCurrentTime();
}

void SD_LED(State *state,int LED,int Time)
{
	static int currentTime[4] = {} ;
	static int counter = 0;
	GPIO_PinState UserInput ;

	UserInput = readUserInput();

	if (UserInput == 1)
	{
		if (LED == LED4) //increase LED4 blinking rate
			Time = 50 ;
		else if (LED == LED5 && counter == 5) //LED5 will blink 5 times in a second and stop
				return ;
	}
	else
	{
		if (LED == LED4) //restore LED4 to original blinking rate
			Time = 500 ;
		else if (LED == LED5) //make sure LED5 is off and reset its counter
			{
				turnOffLED(LED);
				counter = 0 ;
				return ;
			}
	}

	switch(*state)
	{
			case START :
							turnOffLED(LED);
							*state = LED_OFF ;
							break ;

			case LED_ON :
							if (getCurrentTime() - currentTime[LED] >= Time)
							{
								currentTime[LED] = getCurrentTime();
								turnOffLED(LED);
								*state = LED_OFF ;

								if (UserInput == 1 && LED == LED5)
									counter ++ ;
							}

							break ;

			case LED_OFF:
							if (getCurrentTime() - currentTime[LED] >= Time)
							{
								currentTime[LED] = getCurrentTime();
								turnOnLED(LED);
								*state = LED_ON ;
							}

							break ;
	}
}



void turnOffLED(int LED)
{
	if (LED == LED3)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	else if (LED == LED4)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
	else if (LED == LED5)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
}

void turnOnLED(int LED)
{
	if (LED == LED3)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
	else if (LED == LED4)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
	else if (LED == LED5)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
}


