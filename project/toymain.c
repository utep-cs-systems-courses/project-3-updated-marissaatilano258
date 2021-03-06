#include <msp430.h>
#include <libTimer.h>
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"

/*#define LED_GREEN BIT6           // P1.6*/

short redrawScreen = 1;
char curr_state_machine = 0;

void wdt_c_handler()
{
  static int secCount = 0;
  
  secCount++;
  switch(curr_state_machine){
  case 0:
    if(secCount == 200){
      secCount = 0;
      redrawScreen = 1;
    }
    break;
  case 4:
    if(secCount %2 == 0){
      dimStateMachine();
    }
    if(secCount == 150){
      secCount = 0;
      redrawScreen = 1;
    }
    break;
  case 1:
  case 3:
    if(secCount == 75){
      secCount = 0;
      redrawScreen = 1;
    }
    break;
  case 2:
    if(secCount == 150){
      secCount = 0;
      redrawScreen = 1;
    }
    break;
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
  led_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_PURPLE);  /*Displays a start screen*/
  drawString11x16(36,40,"Press", COLOR_YELLOW,COLOR_PURPLE);
  drawString11x16(30,60,"Button", COLOR_YELLOW, COLOR_PURPLE);
  drawString11x16(52,80,"To", COLOR_YELLOW, COLOR_PURPLE);
  drawString11x16(36,100,"Start", COLOR_YELLOW, COLOR_PURPLE);
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      curr_state_machine = button_state;
      switch(button_state){    /*Calls the state machine corresponding to the button state*/
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
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    


