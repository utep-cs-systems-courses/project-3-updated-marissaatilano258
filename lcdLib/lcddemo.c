#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


/** Initializes everything, clears the screen, draws "hello" and a square */
int main()
{

configureClocks();
lcd_init();

clearScreen(COLOR_WHITE);
      
u_char width = screenWidth, height = screenHeight;
  
drawString5x7(20,20,"hello", COLOR_BLACK, COLOR_YELLOW);

drawString8x12(50,50, "hello",COLOR_BLACK, COLOR_YELLOW);

drawString11x16(20,80, "hello", COLOR_BLACK, COLOR_YELLOW);
}
