//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state var to count tim
int secondCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount >= 500) { 	/* once each 2 secs... */
                                /* 500 should slow it down by half*/
    secondCount = 0;	       
    P1OUT ^= LED_GREEN;		/* toggle LEDs alternativly red to green vice-versa */
    P1OUT ^= LED_RED;
  }
} 

