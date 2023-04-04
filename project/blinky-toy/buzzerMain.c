#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define BSW BIT3
#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define BSWITCH   BSW
#define SWITCHES  ( SW1 | SW2 | SW3 | SW4)

char button_pressed = 0;
char soundOn = 0;
int tone = 1500;


int main() {
  configureClocks();

  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;               /* leds initially off */

  P1REN |= BSWITCH;             /* enables resistors for switches */
  P1IE |= BSWITCH;              /* enable interrupts from switches */
  P1OUT |= BSWITCH;             /* pull-ups for switches */
  P1DIR &= ~BSWITCH;            /* set switches' bits for input */
  
  buzzer_init();
  enableWDTInterrupts();
  
  or_sr(0x18);          // CPU off, GIE on
}

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
void state_machine(){
  if(button_pressed == 1){
    state_advance();
  }
  else if(button_pressed == 2){
    buzzer_set_period(5727);	/* start buzzing!!! 2MHz/249.23 = 5.7kHz*/ //F4
  }
  else if(button_pressed == 3){
    buzzer_set_period(4545);    /* start buzzing!!! 2MHz/440.00 = 4.5kHz*/ //A4
  }
  else if(button_pressed == 4){
    buzzer_set_period(7644);	/* start buzzing!!! 2MHz/261.63 = 7.6kHz*/ //C4
  }
  else{
    button_pressed = 0;
  }
}   
    
void red_on(){
  P1OUT |= LED_RED;
  P1OUT &= ~LED_GREEN;
}
void green_on(){
  P1OUT &= ~LED_RED;
  P1OUT |= LED_GREEN;
}

void
switch_interrupt_handler()
{
  char p2val = P2IN; /* switch is in P2*/
  char p1val = P1IN;
  
  P2IES |= (p2val & SWITCHES);	
  P2IES &= (p2val | ~SWITCHES);

  P1IES |= (p1val & BSWITCH);/* IF SWITCH UP, SENSE DOWN */
  P1IES &= (p1val | ~BSWITCH);/* IF SWITCH DOWN, SENSE UP */

  if (!(p2val & SW1)) {
    button_pressed = 1;
    red_on();
  }
  else if(!(p2val & SW2)){
    button_pressed = 2;
    green_on();
  }
  else if(!(p2val & SW3)){
    button_pressed = 3;
    red_on();
  }
  else if(!(p2val & SW4)){
    button_pressed = 4;
    green_on();
  }
  else{
    
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & BSWITCH) {
    P1IFG &= ~BSWITCH;
    switch_interrupt_handler();
  }
}


int count = 0;
void
__interrupt_vec(WDT_VECTOR) WDT() 
{
  count++;
  if(count >= 1000){
    count = 0;
    buzzer_off();
    button_pressed = 0;
  }
  state_machine();
} 
