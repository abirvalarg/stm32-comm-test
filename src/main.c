#include "GPIO.h"
#include "RCC.h"
#include "pins.h"

void led_switch();

void main()
{
	GPIO_enable(LED1.hw, true);
	GPIO_Pin_mode(&LED1, GPIO_PinMode_output);

	GPIO_enable(LED2.hw, true);
	GPIO_Pin_mode(&LED2, GPIO_PinMode_output);

	GPIO_enable(BTN1.hw, true);
	GPIO_Pin_mode(&BTN1, GPIO_PinMode_input);
	GPIO_Pin_write(&LED2, GPIO_Pin_read(&BTN1));

	while(1)
	{
		led_switch();
		for(int i = 0; i < 1000000; i++);
	}
}

void led_switch()
{
	static bool state = 0;
	state = !state;
	GPIO_Pin_write(&LED1, state);
}
