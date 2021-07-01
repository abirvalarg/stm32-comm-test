#pragma once
#include "type.h"

struct TimerConfig
{
	bool preload : 1;
	bool onePulse : 1;
	bool counterOnly : 1;
	bool updateDisable : 1;
	bool DMARequest : 1;
	bool interrupt : 1;
	enum {TimerMMS_Reset = 0, TimerMMS_Enable, TimerMMS_Update} masterMode : 3;
};

struct TimerVTable
{
	void (*init)(void*);
	void (*uninit)(void*);
	void (*set_psc)(void*, Word);
	void (*set_arr)(void*, Word);
	void (*start)(void*);
	void (*stop)(void*);
	Word (*config)(void*, struct TimerConfig);
	bool (*reset)(void*);
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
extern const struct Timer TIM6, TIM7;

/**
 * @brief turn timer on or off
 * @param tm pointer to Timer structure
 * @param state `true` to turn on, `false` to turn off
 */
void Timer_enable(const struct Timer *tm, bool state);

/**
 * @brief set time configurations
 * @param tm pointer to Timer info struct
 */
void Timer_set_time(const struct Timer *tm, Word psc, Word arr);
// void Timer_set_reload(const struct Timer *tm, Word arr);

/**
 * @brief set timer configurations
 * @param tm pointer to Timer info struct
 * @param cfg struct with configurations
 */
Word Timer_config(const struct Timer *tm, struct TimerConfig cfg);

void Timer_start(const struct Timer *tm);
void Timer_stop(const struct Timer *tm);

/**
 * @brief check and reset pending interrupt flag
 */
bool Timer_reset_int(const struct Timer *tm);
