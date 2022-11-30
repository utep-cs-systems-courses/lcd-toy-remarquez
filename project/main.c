


#include <msp430.h>

#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"

#include "buzzer.h"

#include "switches.h"

#include "led.h"

#include "moveshapes.h"

void main()

{
  short redrawScreen = 1;
  configureClocks();

  lcd_init();

  switch_init();
  
  buzzer_init();
  
  led_init();
  
  clearScreen(COLOR_BLACK);

  while (1) {/* forever */

    if (redrawScreen) {

      redrawScreen = 0;

      update_shape();

    }
    green_on = 0;   /* led off */

    led_changed = 1;

    led_update();

    or_sr(0x10);/**< CPU OFF */



    green_on = 1;/* led on */

    led_changed = 1;

    led_update();
  }

    enableWDTInterrupts();      /**< enable periodic interrupt */

  or_sr(0x8);              /**< GIE (enable interrupts) */



}
