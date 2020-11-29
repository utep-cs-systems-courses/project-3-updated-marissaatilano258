#ifndef led_included
#define led_included

#define LED_GREEN BIT6     /*P1.6*/

extern unsigned char green_on;
extern unsigned char led_changed;

void led_init();
void led_update();

#endif                     /*included*/
