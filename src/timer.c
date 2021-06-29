#include "timer.h"
#include "RCC.h"

const struct Timer TIM6 = {
	.hw = &TIM6_BASE,
	.busEnr = &RCC_BASE->APB1ENR,
	.__vt = &basTimVT,
	.type = Timer_Basic,
	.enrPos = 4
};

void Timer_enable(const struct Timer *tm, bool state)
{
	if(state)
	{
		*tm->busEnr |= (1 << tm->enrPos);
		void (*init)(void*) = tm->__vt->init;
		if(init)
			init(tm->hw);
	}
	else
	{
		void (*uninit)(void*) = tm->__vt->uninit;
		if(uninit)
			uninit(tm->hw);
		*tm->busEnr &= ~(1 << tm->enrPos);
	}
}
