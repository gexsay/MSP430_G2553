#include <msp430.h> 
#include <stdbool.h>

bool start;
int speed = 0;

int main(void){

	WDTCTL = WDTPW | WDTHOLD;
	
	P1DIR = BIT0 | BIT6;                    //LED 1,6 on

	//DEBUG

	P1OUT = BIT0;                           //LED red on

	__delay_cycles(5000000);                //delay 5s for start

	start = 1;
	P1OUT = ~BIT0;

	//DEBUG

    P1REN = BIT3;

    P1IE = BIT3;
    P1IES = BIT3;
    P1IFG = 0x00;

    _enable_interrupts();

    while(start){

        if (speed < 10){

            speed++;
            __delay_cycles(1000000);        // delay 0.5s

            P1OUT ^= BIT6;

        }
            else{

                P1OUT ^= BIT6;
                __delay_cycles(250000);     // delay 0.25s
            }

    }

    P1OUT = ~BIT6;

}


#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void){

    start = 0;
    speed = 0;
    P1OUT = ~BIT6 & BIT0;

    P1IFG = 0x00;
}
