//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;       /* Sets LEDS to pin 1 *very important* */
  
  P1OUT &= ~LED_GREEN; /* turn off Green LED */
  P1OUT |= LED_RED;    /* turn on Red LED */

  //P1OUT &= ~LED_RED;   /* turn off red and torun on green */
  //P1OUT |= LED_GREEN;

  //P1OUT |= LED_GREEN;  /* turn both on */
  //P1OUT |= LED_RED;

  P1OUT |= LEDS;       /* ALt. for turning both on */

  //P1OUT &= ~LED_RED;   /* turn both off LED*/ 
  //P1OUT &= ~LED_GREEN;
  
  P1OUT &= ~LEDS;      /* ALt. turn both off LED */
  
  or_sr(0x18);		/* CPU off, GIE on */
}
