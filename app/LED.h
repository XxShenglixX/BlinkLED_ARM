#ifndef LED_H
#define LED_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define readUserInput() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);

enum {
				LED3 = 0,
				LED4,
				LED5,
				LED6
};

typedef enum {
				START,
				LED_OFF,
				LED_ON,
				CHECK_BUTTON,
				BUTTON_NOT_PRESSED,
				BUTTON_PRESSED
}State;

void turnOffLED(int LED);
void turnOnLED(int LED);
void SM_LED(State *state,int LED,int *Time);


#endif // LED_H
