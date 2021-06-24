#include "pins.h"
#include "GPIO.h"

const struct GPIO_Pin LED1 = {
	.hw = &GPIOB,
	.pin = 6
};

const struct GPIO_Pin LED2 = {
	.hw = &GPIOB,
	.pin = 7
};

const struct GPIO_Pin BTN1 = {
	.hw = &GPIOC,
	.pin = 4
};
