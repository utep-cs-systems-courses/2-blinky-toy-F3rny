#ifndef buzzer_included
#define buzzer_included

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

extern int tone;
extern char soundOn;

void buzzer_init();
void buzzer_set_period(short cycles);
void buzzer_off();
void red_on();
void green_on();
void state_advance();

#endif // included
