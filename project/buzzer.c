#include <msp430.h>

#include "libTimer.h"

#include "buzzer.h"

static int counterForSong1 = 0;

void buzzer_init(){

  timerAUpmode();

  P2SEL2 &= ~(BIT6 | BIT7);

  P2SEL &= ~BIT7;

  P2SEL |= BIT6;

  P2DIR = BIT6;

}



void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */

{

  CCR0 = cycles;
  
  CCR1 = cycles >> 1;/* one half cycle */

}
void song1(){
  switch(counterForSong1){

  case 0:

  case 1:

  case 2:

  case 3:

  case 4:

  case 6:

  case 8: buzzer_set_period(950); counterForSong1++; break; //C note

  case 5:

  case 7: buzzer_set_period(1130); counterForSong1++; break; //A note

  case 9:

  case 10:

  case 11:

  case 12:

  case 13:

  case 15:

  case 17: buzzer_set_period(1000); if(counterForSong1==17){counterForSong1 = 0;} else{counterForSong1++;}; break; //B

  case 14:

  case 16: buzzer_set_period(1270); counterForSong1++; break; //G note

  }
}

