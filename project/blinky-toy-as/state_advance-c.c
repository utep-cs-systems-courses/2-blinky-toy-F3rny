#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void
state_advance()
{
  switch(soundOn){
    case 0:
      tone += 50;
      if(tone >= 3000){
	soundOn = 1;
	
      }
      buzzer_set_period(tone);
      break;
    case 1:
      tone -= 50;
      if(tone <= 1500){
	soundOn = 0;
      }
      buzzer_set_period(tone);
      break;
  }
}
