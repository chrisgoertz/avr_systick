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
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

/**
 * Define the cpu clock frequency if
 * not done yet...
 */
#ifndef F_CPU
#define F_CPU 20000000UL
#endif

/** Initialize and start the systick generation */
void systick_init();
/** (Re)Start the systick generation */
void systick_start();
/** Stop the systick generation */
void systick_stop();
/** Get systicks */
uint32_t systick_getTicks();


#endif /* SYSTICK_H_ */