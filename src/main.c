#include "GPIO.h"
#include "RCC.h"
#include "pins.h"
#include "timer.h"
#include "NVIC.h"

void led_on(const struct Timer *_);
void led_off(const struct Timer *_);

void start()
{
	// pos 54
	NVIC_ISER[1] = 0b11 << 22;

	GPIO_enable(LED1.hw, true);
	GPIO_Pin_mode(&LED1, GPIO_PinMode_output);
	GPIO_Pin_mode(&LED2, GPIO_PinMode_output);

	GPIO_enable(BTN1.hw, true);

	Timer_enable(&TIM6, true);
	Timer_set_time(&TIM6, 16000, 1000);
	Timer_on_update(&TIM6, led_on);
	Timer_trigger(&TIM6);
	static const struct TimerConfig timCfg = {
		.DMARequest = false,
		.counterOnly = false,
		.interrupt = true,
		.onePulse = false,
		.preload = false,
		.updateDisable = false,
	};

	Timer_enable(&TIM7, true);
	Timer_set_time(&TIM7, 16000, 100);
	Timer_on_update(&TIM7, led_off);
	Timer_trigger(&TIM7);
	static const struct TimerConfig offTimCfg = {
		.DMARequest = false,
		.counterOnly = false,
		.interrupt = true,
		.onePulse = true,
		.preload = false,
		.updateDisable = false
	};

	while(!Timer_reset_int(&TIM6));
	while(!Timer_reset_int(&TIM7));

	Timer_config(&TIM6, timCfg);
	Timer_config(&TIM7, offTimCfg);

	Timer_start(&TIM6);

	while(true)
		GPIO_Pin_write(&LED2, GPIO_Pin_read(&BTN1));
}

void led_on(const struct Timer *_)
{
	Timer_start(&TIM7);
	GPIO_Pin_write(&LED1, true);
}

void led_off(const struct Timer *_)
{
	GPIO_Pin_write(&LED1, false);
}
