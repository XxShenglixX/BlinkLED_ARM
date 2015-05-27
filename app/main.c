#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "configuration.h"
#include "Times.h"
#include "LED.h"

#define _120ms 120
#define _100ms 100
#define _200ms 200
#define _1s 1000



int main(void)
{
	int Time_LED3 = _120ms ,
		Time_LED4 = _1s ,
		Time_LED5 = _200ms ;


	State state_1 = START , state_2 = START, state_3 = START;
	initLED();
	configButton();



    while(1)
    {
    	SM_LED(&state_1,LED3,&Time_LED3);
    	SM_LED(&state_2,LED4,&Time_LED4);
    	SM_LED(&state_3,LED5,&Time_LED5);

    }
}
