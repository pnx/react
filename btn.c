/*  btn.c
 *
 *   Copyright (C) 2013       Henrik Hautakoski <henrik.hautakoski@gmail.com>
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

int btn_pressed(void) {

	/* Button is pressed if direction 
	   is set to output */
	return BTNDIR & BTN0;
}

void btn_register_intr(void) {

	/* Set button to input. */
	BTNDIR &= ~BTN0;

	/* Interrupt on high -> low edge. */
	BTNIES |= BTN0;
	
	/* Enable interrupt and
	   clear interrupt flag */
	BTNIE  |= BTN0;
	BTNIFG &= ~BTN0;
}

#pragma vector=PORT1_VECTOR
__interrupt void __BTN_ISR(void) {

	/* Flag for button press by setting 
	   direction to output. */
	BTNDIR |= BTN0;

	/* Disable interrupt and 
	   clear interrupt flag */
	BTNIE  &= ~BTN0;
	BTNIFG &= ~BTN0;
}
