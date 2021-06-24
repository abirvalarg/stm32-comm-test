#include "GPIO.h"
#include "RCC.h"

const struct GPIO GPIOA = {
	.regs = &GPIOA_BASE,
	.busEnr = &RCC_BASE->AHB1ENR,
	.enrMask = 0b1
};

const struct GPIO GPIOB = {
	.regs = &GPIOB_BASE,
	.busEnr = &RCC_BASE->AHB1ENR,
	.enrMask = 0b10
};

const struct GPIO GPIOC = {
	.regs = &GPIOC_BASE,
	.busEnr = &RCC_BASE->AHB1ENR,
	.enrMask = 0b100
};

void GPIO_enable(const struct GPIO *hw, bool state)
{
	if(state)
		*hw->busEnr |= hw->enrMask;
	else
		*hw->busEnr &= ~hw->enrMask;
}

void GPIO_Pin_mode(const struct GPIO_Pin *pin, enum GPIO_PinMode mode)
{
	Word tmp = pin->hw->regs->MODER;
	tmp &= ~(0b11 << (pin->pin * 2));
	tmp |= mode << (pin->pin * 2);
	pin->hw->regs->MODER = tmp;
}

void GPIO_Pin_otype(const struct GPIO_Pin *pin, enum GPIO_PinOType mode)
{
	volatile Word *reg = &pin->hw->regs->OTYPER;
	if(mode)
		*reg |= 1 << pin->pin;
	else
		*reg &= ~(1 << pin->pin);
}

void GPIO_Pin_pull(const struct GPIO_Pin *pin, enum GPIO_PinPull mode)
{
	Word tmp = pin->hw->regs->PUPDR;
	tmp &= ~(0b11 << (pin->pin * 2));
	tmp |= mode << (pin->pin * 2);
	pin->hw->regs->PUPDR = tmp;
}

void GPIO_Pin_write(const struct GPIO_Pin *pin, bool val)
{
	volatile Word *reg = &pin->hw->regs->ODR;
	if(val)
		*reg |= 1 << pin->pin;
	else
		*reg &= ~(1 << pin->pin);
}

bool GPIO_Pin_read(const struct GPIO_Pin *pin)
{
	return (pin->hw->regs->IDR >> pin->pin) & 1;
}
