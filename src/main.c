#include "GPIO.h"
#include "RCC.h"
#include "pins.h"
#include "timer.h"
#include "NVIC.h"

void start()
{
	// pos 54
	NVIC_ISER[1] = 0b11 << 22;

	GPIO_enable(LED1.hw, true);
	GPIO_Pin_mode(&LED1, GPIO_PinMode_output);

	Timer_enable(&TIM6, true);
	Timer_set_time(&TIM6, 16000, 1000);

	static const struct TimerConfig timCfg = {
		.DMARequest = false,
		.counterOnly = false,
		.interrupt = true,
		.onePulse = false,
		.preload = false,
		.updateDisable = false,
	};
	Timer_config(&TIM6, timCfg);

	Timer_enable(&TIM7, true);
	Timer_set_time(&TIM7, 16000, 100);
	static const struct TimerConfig offTimCfg = {
		.DMARequest = false,
		.counterOnly = false,
		.interrupt = true,
		.onePulse = true,
		.preload = false,
		.updateDisable = false
	};
	Timer_config(&TIM7, offTimCfg);

	Timer_start(&TIM6);
}

void _TIM6_DAC_handler()
{
	Timer_start(&TIM7);
	GPIO_Pin_write(&LED1, true);
	Timer_reset_int(&TIM6);
}

void _TIM7_handler()
{
	GPIO_Pin_write(&LED1, false);
	Timer_reset_int(&TIM7);
}
