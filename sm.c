/*  sm.c
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
#include "msp430_local.h"
#include "rand.h"

#define INIT_TIMEOUT 200
#define MAX_CNT 150
#define MIN_CNT 20

void sm_init() {

	/* Disable watchdog */
	WDTCTL = WDTPW + WDTHOLD;

	/* Setup Timer interrupt */
	CCTL0 = CCIE;
  	TACCR0 = 62500;

  	/* Configure clock to use.
  	 *
  	 * TASSEL: Clock source select.
  	 * MC: Mode control (count up or down)
  	 * ID: Input divider.
  	 */

  	/* SMCLK count up to TACCR0 */
  	TACTL = TASSEL_2 + MC_1;
}

/* Define states. */
typedef enum {
	STATE_RESET,
	STATE_PRE_REACT,
	STATE_REACT,
	STATE_WIN,
} state_t;

#pragma vector=TIMER_VEC
__interrupt void __TIMER_ISR(void) {

	static state_t state = STATE_RESET;
	static unsigned cnt = 0;
	static unsigned timeout;

	switch(state) {
	case STATE_RESET :

		if (cnt-- < 1) {
			/* Lit Green LED */
			LEDOUT &= ~LED0;
			LEDOUT |= LED1;
			cnt = 50;
			timeout = INIT_TIMEOUT;
			state = STATE_PRE_REACT;
		}
		break;
	case STATE_PRE_REACT :

		if (cnt-- < 1) {
			state = STATE_REACT;
			cnt = 0;
			/* turn off both LEDs */
			LEDOUT &= ~(LED0 | LED1);
			btn_register_intr();
		}
		break;
	case STATE_REACT :

		if (cnt++ > timeout) {
			cnt = 50;
			state = STATE_RESET;
			LEDOUT |= LED0;
		} else if (btn_pressed()) {
			cnt = 50;
			state = STATE_WIN;
			LEDOUT |= LED1;
		}
		break;
	case STATE_WIN :
		if (cnt-- < 1) {
			timeout = timeout / 2;
			cnt = rand_interval(MIN_CNT, MAX_CNT);
			state = STATE_PRE_REACT;
		}
		break;
	}
}
