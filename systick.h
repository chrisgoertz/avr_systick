/*
 * systick.h
 *
 * Created: 06.10.2024 00:06:30
 *  Author: chris
 */ 
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

void systick_init();
uint32_t systick_getTicks();


#endif /* SYSTICK_H_ */