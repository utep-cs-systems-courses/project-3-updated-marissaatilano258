#include <msp430.h>
#include <libTimer.h>
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "buzzer.h"

#define LED_GREEN BIT6             // P1.0

short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;
  
  secCount ++;
  if (secCount == 150) {		/* once/sec */
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
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_WHITE);
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      switch(button_state){
      case 1:
	scaleStateMachine();
	break;
      case 2:
	christmasStateMachine();
	break;
      case 3:
	snakeStateMachine();
	break;
      case 4:
	spiderStateMachine();
	break;
      default:
	clearScreen(COLOR_WHITE);
	break;
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    


