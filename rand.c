/*  rand.c
 *
 *   Copyright (C) 2013       Henrik Hautakoski <henrik@fiktivkod.org>
 *
 *   Psuedo-number-generator derived from glibc.
 *   Copyright (C) 1995-2013 Free Software Foundation, Inc.
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

/* Keep track of the psedo random state. */
static int state = 0;

void srand(unsigned int seed) {

	state = seed;
}

int rand(void) {

	/* LCG implementation derived from glibc's random_r.c */
	state = (1103515245 * state) + 12345;
	return state;
}
