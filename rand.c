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

/* Best random function ever :) 
   this takes up ALOT of space. */
int rand(void) {

	int table[16] = {
		0x7f6a, 0x086d, 0x9164, 0xe663,
        	0x6b6b, 0x1c6c, 0x8565, 0xf262,
        	0x6c06, 0x1b01, 0x8208, 0xf50f,
        	0x65b0, 0x12b7, 0x8bbe, 0xfcb9
	};

	static unsigned char cnt = 0;

	return table[(cnt++) % (sizeof(table) / sizeof(table[0]))];
}
