#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define BSW BIT3
#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define BSWITCH   SW1
#define SWITCHES  ( SW1 | SW2 | SW3 | SW4)
#define SWITCHES1 SW1
#define SWITCHES2 SW2
#define SWITCHES3 SW3
#define SWITCHES4 SW4


int main() {
  configureClocks();

  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */

  buzzer_init();
  enableWDTInterrupts();


  or_sr(0x18);          // CPU off, GIE on
}
int soundOn = 0;
int tone = 1500;
void buzzer_song(){
  buzzer_set_period(tone); 
  
}
void state_advance()
{
  switch(soundOn){
    case 0:
      tone += 50;
      if(tone >= 3000){
	soundOn = 1;
      }
      break;
    case 1:
      tone -= 50;
      if(tone <= 1500){
	soundOn = 0;
      }
      
      break;
  }
}
void
switch_interrupt_handler()
{
  char p2val = P2IN; /* switch is in P2*/
  
  P2IES |= (p2val & SWITCHES);	
  P2IES &= (p2val | ~SWITCHES);

  if (!(p2val & SW1)) {
    buzzer_song();
  }
  else if(!(p2val & SW2)){
   	/* start buzzing!!! 2MHz/349.23 = 5.7kHz*/ //F4
  }
  else if(!(p2val & SW3)){
    buzzer_set_period(7644);	/* start buzzing!!! 2MHz/261.63 = 7.6kHz*/ //C4
  }
  else if(!(p2val & SW4)){
    buzzer_set_period(5727);	/* start buzzing!!! 2MHz/249.23 = 5.7kHz*/ //F4
  } else{
    
  }
  
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

int count = 0;
void
__interrupt_vec(WDT_VECTOR) WDT() 
{
  count++;
  state_advance();
  if(count >= 1000){
    count = 0;
    buzzer_off();
  }
  
} 

