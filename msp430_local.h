/*  msp430_local.h
 *
 *   Copyright (C) 2013       Henrik Hautakoski <henrik@fiktivkod.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *   MA 02110-1301, USA.
 */
#ifndef MSP430_LOCAL_H
#define MSP430_LOCAL_H

#include <msp430.h>

/*
 * Buttons
 */

/* Button is connected to pin 1. */
#define BTNDIR  P1DIR
#define BTNOUT  P1OUT
#define BTNIN   P1IN
#define BTNIES  P1IES /* Edge select */
#define BTNIE   P1IE  /* Interrupt enable */
#define BTNIFG  P1IFG /* Interrupt flag */

/* Define what bit in the register the button is. */
#define BTN0    BIT3

/*
 * LEDS
 */

/* The LEDs is connected to pin 1. */
#define LEDDIR	P1DIR
#define LEDOUT	P1OUT

/* Define what bits in the register each LED is. */
#define LED0	BIT0
#define LED1	BIT6

/*
 * TIMERS
 */

#define TIMER_VEC TIMERA0_VECTOR

#endif /* MSP430_LOCAL_H */
