#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int main() {
    configureClocks();
 
    buzzer_init();
    buzzer_set_period(7644);	/* start buzzing!!! 2MHz/261.63 = 7.6kHz*/ //C4


    or_sr(0x18);          // CPU off, GIE on
}
