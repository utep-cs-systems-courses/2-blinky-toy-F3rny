#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void green_on(){
  P1OUT &= ~LED_RED;
  P1OUT |= LED_GREEN;
}
