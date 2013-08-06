
#include "msp430_local.h"
#include "sm.h"

void main(void) {

	LEDDIR &= 0x00;
	LEDOUT &= 0x00;

	LEDDIR |= LED0 + LED1;

	sm_init();

	/* enable interrupts */
	_BIS_SR(LPM0_bits + GIE);

	for(;;);
}