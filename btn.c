
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
