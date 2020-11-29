#include <msp430.h>
#include "led.h"

unsigned char green_on = 0;
unsigned char led_changed = 0;

static char greenVal[] = {0, LED_GREEN};


void led_init()
{
  P1DIR |= LED_GREEN;                         /*bits attached to leds are output*/
  led_changed = 1;
  led_update();
}

void led_update()
{
  if(led_changed){
    char ledFlags = greenVal[green_on];
    P1OUT &= (0xff^LED_GREEN) | ledFlags;     /*clear bit for off leds*/
    P1OUT |= ledFlags;                   /*set bit for on leds*/
    led_changed = 0;
  }
}
