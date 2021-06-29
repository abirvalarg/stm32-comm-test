#pragma once
#include "type.h"

struct TimerVTable
{
	void (*init)(void*);
	void (*uninit)(void*);
	void (*set_prescaler)(void*, Word);
	void (*start)(void*);
};

enum TimerType {Timer_Basic};

struct Timer
{
	const struct TimerVTable *__vt;
	void *hw;
	volatile Word *busEnr;
	enum TimerType type;
	Byte enrPos;
};

struct BasicTimerReg
{
	volatile Word CR1;
	volatile Word CR2;
	volatile Word _reserved0;
	volatile Word DIER;
	volatile Word SR;
	volatile Word EGR;
	volatile Word _reserved1;
	volatile Word _reserved2;
	volatile Word _reserved3;
	volatile Word CNT;
	volatile Word PSC;
	volatile Word ARR;
};

extern Word TIM6_BASE, TIM7_BASE;
extern const struct TimerVTable basTimVT;
extern const struct Timer TIM6, TIM7;

void Timer_enable(const struct Timer *tm, bool state);
void Timer_set_prescaler(const struct Timer *tm, Word psc);
void Timer_update(const struct Timer *tm);
void Timer_set_reload(const struct Timer *tm, Word arr);
