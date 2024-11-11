/*
 * systick.h
 *
 * Created: 06.10.2024 00:06:30
 *  Author: chris
 *                    GNU GENERAL PUBLIC LICENSE
 *                       Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
 */ 



#include "systick.h"
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>



// #define SYSTICK_TIMER0
#define SYSTICK_TIMER1
#ifdef SYSTICK_TIMER1
	#define PRESCALER_STOP		~((1<<CS12)|(1<<CS11)|(1<<CS10))
	#define PRESCALER_1 		(1<<CS10)
	#define PRESCALER_8 		(1<<CS11)
	#define PRESCALER_64 		((1<<CS10)|(1<<CS11))
	#define PRESCALER_256		(1<<CS12)
	#define PRESCALER_1024		((1<<CS10)|(1<<CS12))

#elif defined SYSTICK_TIMER0
	#define PRESCALER_STOP		~((1<<CS02)|(1<<CS01)|(1<<CS00));
	#define PRESCALER_1 		(1<<CS00)
	#define PRESCALER_8 		(1<<CS01)
	#define PRESCALER_64 		((1<<CS00)|(1<<CS01))
	#define PRESCALER_256		(1<<CS02)
	#define PRESCALER_1024		((1<<CS00)|(1<<CS02))

#endif
#define SYSTICK_PRESCALER PRESCALER_8

static volatile uint32_t _ticks = 0;

#ifdef SYSTICK_TIMER1
ISR(TIMER1_COMPA_vect)
{
	TCNT1 = 0;
	_ticks++;	
}
#endif

#ifdef SYSTICK_TIMER0
ISR(TIMER0_COMP_vect)
{
	TCNT0 = 0;
	_ticks++;	
}
#endif

void systick_init()
{
#if defined USE_TIMER0
	OCR0 = 144;
	TIMSK |= (1<<OCIE0);
	// Prescaler 1024
	TCCR0 |= (1<<WGM01) | (1<<CS02) | (1<<CS00);
#elif defined SYSTICK_TIMER1
	OCR1A = 2500;			// Load Output Compare Register
	TIMSK1 = (1<<OCIE0A);	// Enable Output Compare A Match Interrupt
	TCCR1A |= (1<<WGM02);	// CTC Mode
	TCCR1B |= PRESCALER_8;	// Prescaler 8
#endif
	sei();
}

/**
*Generate 1ms tick
*/
uint32_t systick_getTicks()
{
	return _ticks;
}

void systick_start()
{
	#ifdef SYSTICK_TIMER1
	TCCR1B |= SYSTICK_PRESCALER;
	#elif defined SYSTICK_TIMER0
	TCCR0 |= SYSTICK_PRESCALER;
	#endif
}

void systick_stop()
{
	#ifdef SYSTICK_TIMER1
	TCCR1B &= PRESCALER_STOP;
	#elif defined SYSTICK_TIMER0
	TCCR0 &= PRESCALER_STOP;
	#endif
}