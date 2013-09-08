/*  rand.c
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
#include "rand.h"
#include <msp430.h>

#define RTACCTL TACCTL0
#define RTACCR  TACCR0

/*
 * True random number generator using hardware clocks (VLO and DCC)
 *
 * TI SLAA338 Algorithm: http://www.ti.com/sc/docs/psheets/abstract/apps/slaa338.htm
 */
int rand(void) {

	int i, j;
	unsigned _ctl, _cctl, _ccr, r = 0;

	/* Save old Timer A control state. */
	_ctl = TACTL;
	_cctl = RTACCTL;
	_ccr = RTACCR;

	RTACCTL = CAP | CM_1 | CCIS_1;	/* Capture mode */
	TACTL 	= TASSEL_2 | MC_2; 	/* SMCLK (submain), continuous mode */

	/* Fetch all 16 bits individually
	   from hardware clock. */
	for(i=0; i < 16; i++) {
		unsigned char cnt = 0;

		for(j=0; j < 5; j++) {

			/* Wait for interrupt */
			while(!(CCIFG & RTACCTL));

			RTACCTL &= ~CCIFG;

			if (RTACCR & 0x1)
				cnt++;
		}

		/* Shift result and set MSB */
		r >>= 0x1;
		if (cnt > 2)
			r |= 0x8000;
	}

	/* Restore state */
	TACTL = _ctl;
	RTACCTL = _cctl;
	RTACCR = _ccr;

	return r;
}
