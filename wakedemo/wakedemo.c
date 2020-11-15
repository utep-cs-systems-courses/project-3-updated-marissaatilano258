#include <msp430.h>
#include <libTimer.h>
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

#define LED_GREEN BIT6             // P1.0


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;


void wdt_c_handler()
{
  static int secCount = 0;
  
  secCount ++;
  if (secCount == 2) {		/* once/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_WHITE);
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      //drawString8x12(25,25,"Hello", COLOR_BLACK, COLOR_PURPLE);
      //drawString5x7(10,10,"!", COLOR_RED, COLOR_BLUE);
      //spiderStateMachine();
      //u_int switches = p2sw_read();
      //u_int button1 = (switches & (0x1)) ? 0 : 1;
      //if(button1){
      //christmasStateMachine();
      //}
    }
    u_int switches = p2sw_read();
    u_int button1 = (switches & 0x1) ? 0: 1;
    if(button1){
      //christmasStateMachine();
      //spiderStateMachine();
      snakeStateMachine(10,3);
      button1 = 0;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    


