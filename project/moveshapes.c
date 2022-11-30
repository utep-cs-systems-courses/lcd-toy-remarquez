#include <msp430.h>

#include <libTimer.h>

#include "lcdutils.h"

#include "lcddraw.h"

#include "buzzer.h"

#include "switches.h"

#include "led.h"

#include "moveshapes.h"
// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!

char blue = 31, green = 0, red = 31;

unsigned char step = 0;




int switches = 0;





// axis zero for col, axis 1 for row



short drawPos[2] = {1,100}, controlPos[2] = {1, 100};

short colVelocity = 4, colLimits[2] = {1,screenWidth-35};



void

draw_ball(int col, int row, unsigned short color)

{

  fillRectangle(col, 75,10,10, color);
  fillRectangle(col+15,75,10,10,color);
  fillRectangle(col+30,75,10,10,color);
}





void

screen_update_ball()

{

  for (char axis = 0; axis < 2; axis++)

    if (drawPos[axis] != controlPos[axis]) /* position changed? */

      goto redraw;

  return;/* nothing to do */

 redraw:

  draw_ball(drawPos[0], drawPos[1], COLOR_BLACK); /* erase */

  for (char axis = 0; axis < 2; axis++)
      drawPos[axis] = controlPos[axis];

  draw_ball(drawPos[0]++, drawPos[1], COLOR_PURPLE); /* draw */
 
}

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;



void wdt_c_handler()

{

  int static secCount = 0;

  secCount ++;

  if (secCount >= 15) {/* 10/sec */



    {/* move ball */

      short oldCol = controlPos[0];

      short newCol = oldCol + colVelocity;

      if (newCol <= colLimits[0] || newCol >= colLimits[1])

	colVelocity = -colVelocity;

      else

	controlPos[0] = newCol;

    }



    {

      if (switches & SW3) green = (green + 1) %64;
    

      if (switches & SW2) blue = (blue + 2) % 32;

      if (switches & SW1) red = (red - 3) % 32;

      if (step <= 75)

	step ++;

      else

	step = 0;

      secCount = 0;

    }

    if (switches & SW4) return;

    redrawScreen = 1;

  }
}





void

screen_update_bars()
{

  static unsigned char row = (screenHeight / 2)-15, col = screenWidth / 2;

  static char lastStep = 0;



  if (step == 0 || (lastStep > step)) {

    clearScreen(COLOR_BLACK);

    lastStep = 0;

  } else {

    for (; lastStep <= step; lastStep++) {

      int startCol = lastStep -50;

      int secondCol = 120;

      int endCol = screenWidth;

      int width = 50;



   



      fillRectangle(startCol, row+lastStep, 10, 1, COLOR_PURPLE);

      fillRectangle(secondCol-lastStep, row-lastStep, 10, 1, COLOR_PINK);
      

    }

  }

}

void update_shape()
{

  screen_update_ball();

  screen_update_bars();

}


