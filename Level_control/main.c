#include <msp430.h> 

int gSTART;
int gSPEED;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;

	//LED 1, 6 on
	P1DIR = BIT0 | BIT6;

	///DEBUG
	
	//LED RED ON
	P1OUT = BIT0;

	//delay 5s for start
	__delay_cycles(5000000);

	gSTART = 1;
	P1OUT = ~BIT0;

	///DEBUG
	
    	P1REN = BIT3;
    	P1IE = BIT3;
    	P1IES = BIT3;
    	P1IFG = 0x00;

        _enable_interrupts();

        while (gSTART) {
       	    if (speed < 10) {
            gSPEED++;
	    // delay 0.5s
            __delay_cycles(1000000);

            P1OUT ^= BIT6;
        }

            else {
            P1OUT ^= BIT6;
	    // delay 0.25s
            __delay_cycles(250000);
        }

    }

    P1OUT = ~BIT6;
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
    gSTART = 0;
    gSPEED = 0;
    P1OUT = ~BIT6 & BIT0;
    P1IFG = 0x00;
}
