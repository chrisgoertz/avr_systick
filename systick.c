/*
 * systick.c
 *
 * Created: 06.10.2024 00:06:47
 *  Author: chris
 */ 

#include "systick.h"
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define USE_TIMER1

static uint32_t _ticks = 0;

ISR(TIMER1_COMPA_vect)
{
	TCNT1 = 0;
	_ticks++;	
}

ISR(TIMER0_COMP_vect)
{
	TCNT0 = 0;
	_ticks++;	
}

void systick_init()
{
#if defined USE_TIMER0
	OCR0 = 144;
	TIMSK |= (1<<OCIE0);
	// Prescaler 1024
	TCCR0 |= (1<<WGM01) | (1<<CS02) | (1<<CS00);
#elif defined USE_TIMER1
	OCR1A = 2500;
	TIMSK1 = (1<<OCIE0A);
	TCCR1A |= (1<<WGM02);
	TCCR1B |= (1<<CS11); // Prescaler 8
#endif
	sei();
}
/**
*Generate 10ms tick
*/
uint32_t systick_getTicks()
{
	
	return _ticks;
}