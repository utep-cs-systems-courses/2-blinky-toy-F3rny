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

// global state vars that control blinking
int blinkLimit = 12;  // duty cycle = 1/blinkLimit
int blinkRed = 5;
int blinkCountB = 0;  // cycles 0...blinkLimit-1
int blinkCountR = 0;
int secondCount = 0; // state var representing repeating time 0…1s

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking 
  blinkCountB ++;
  if (blinkCountB >= blinkLimit) { // on for 1 interrupt period
    blinkCountB = 0;
    P1OUT |= LED_GREEN;
  } else{                          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
  }
  
  blinkCountR ++;
  if(blinkCountR >= blinkRed){
    blinkCountR = 0;
    P1OUT |= LED_RED;
  } else{
    P1OUT &= ~LED_RED;
  }

  // measure 2 seconds
  secondCount ++;
  if (secondCount >= 500) {  // once each second // 500 for slower  // 125 for faster
    secondCount = 0;
    blinkLimit --;	     // reduce duty cycle // increase when blinkLimit--;
    if (blinkLimit == 0)
      blinkLimit = 12;
    blinkRed++;
    if(blinkRed >= 8)
      blinkRed = 0;
  }
} 

