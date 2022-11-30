#ifndef switches_included

#define switches_included



#define SW1 BIT1

#define SW2 BIT2

#define SW3 BIT4

#define SW4 BIT8



#define SWITCHES (SW1 | SW2 | SW3 |SW4)



void switch_init();

void switch_interrupt_handler();



extern char switch_state_down, switch_state_changed, tempo;



#endif
