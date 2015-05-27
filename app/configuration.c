#include "configuration.h"




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
