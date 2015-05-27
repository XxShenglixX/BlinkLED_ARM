#include "LED.h"
#include "Times.h"

#define _120ms 120
#define _100ms 100
#define _200ms 200
#define _1s 1000

void turnOffLED(int LED)
{
	if (LED == LED3)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	else if (LED == LED4)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
}

void turnOnLED(int LED)
{
	if (LED == LED3)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
	else if (LED == LED4)
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
}

void SM_LED(State *state,int LED,int *Time)
{
	static int currentTime[4] = {} ;
	static int counter = 0, triggered = 0 ;
	GPIO_PinState UserInput = 0;

	switch(*state)
	{
			case START :
							turnOffLED(LED);
							if (LED == LED3)
								*state = LED_OFF ; //LED3 doesn;t have to care about button
							else
								*state = CHECK_BUTTON ;
							break ;

			case CHECK_BUTTON :
							UserInput = readUserInput(); //for LED4 and LED5 only
							if(UserInput == 1)
							{
								triggered = 1 ; //set triggered to 1 to remember that the user had already pressed the button

								*state = BUTTON_PRESSED ; //
							}
							else
								*state = BUTTON_NOT_PRESSED ;
							break ;

			case LED_ON :
							turnOnLED(LED);
							if (getCurrentTime() - currentTime[LED] >= *Time)
							{
								currentTime[LED] = getCurrentTime();
								turnOffLED(LED);

								if (LED == LED3)
									*state = LED_OFF ; //LED3 doesn;t have to care about button
								else
									*state = CHECK_BUTTON ;

								if (LED == LED5)
									counter ++ ;
							}

							break ;

			case LED_OFF:
							turnOffLED(LED);
							if (getCurrentTime() - currentTime[LED] >= *Time)
							{
								currentTime[LED] = getCurrentTime();
								turnOnLED(LED);
								*state = LED_ON ;
							}

							break ;

			case BUTTON_PRESSED:
							if (LED == LED4)
								*Time = _100ms;
							else if (LED == LED5)
							{
								if (counter == 5) // LED5 blinked 5 times
								{
									*state = START ;
									break ;
								}
							}
							*state = LED_OFF ;
							break ;
			case BUTTON_NOT_PRESSED :

							if (LED == LED4) //restore LED4 to original blinking rate
								*Time = _1s ;
							else if (LED == LED5)
								{
									if (triggered) // button was pressed
									{
										if (counter == 5 ) // check if LED5 had blinked 5 times
										{
											triggered  = 0 ;
											counter = 0 ;
										}
										else //if not will force LED5 to blink till 5 times
										{
											*state = LED_OFF ;
											break;
										}

									}

									*state = CHECK_BUTTON ; // button was not pressed previously and go and check it again
									break ;
								}

							*state = LED_OFF ;
							break ;
	}
}
