#include <msp430.h>
#include "p2switches.h"
#include "stateMachines.h"

static unsigned char switch_mask;
static unsigned char switches_last_reported;
static unsigned char switches_current;

static void
switch_update_interrupt_sense()
{
  switches_current = P2IN & switch_mask;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (switches_current);  /* if switch up, sense down */
  P2IES &= (switches_current | ~switch_mask); /* if switch down, sense up */
}

void p2sw_init(unsigned char mask)
{
  switch_mask = mask;
  P2REN |= mask;    /* enables resistors for switches */
  P2IE = mask;      /* enable interrupts from switches */
  P2OUT |= mask;    /* pull-ups for switches */
  P2DIR &= ~mask;   /* set switches' bits for input */

  switch_update_interrupt_sense();
}

/* Returns a word where:
 * the high-order byte is the buttons that have changed,
 * the low-order byte is the current state of the buttons
 */
unsigned int 
p2sw_read() {
  unsigned int sw_changed = switches_current ^ switches_last_reported;
  switches_last_reported = switches_current;
  return switches_current | (sw_changed << 8);
}

void switch_interrupt_handler()
{
  char p2val = p2sw_read();
  switch_update_interrupt_sense();
  char sw1_state = (p2val & 0x1) ? 0 : 1; /*0 when switch S1 is up*/
  char sw2_state = (p2val & 0x2) ? 0 : 1; /*0 when switch S2 is up*/
  char sw3_state = (p2val & 0x4) ? 0 : 1; /*0 when switch S3 is up */
  char sw4_state = (p2val & 0x8) ? 0 : 1; /*0 when switch S4 is up*/

  if(sw1_state){
    changeButtonState(1);
  } else if(sw2_state){
    changeButtonState(2);
  } else if(sw3_state){
    changeButtonState(3);
  } else if(sw4_state){
    changeButtonState(4);
  }
}

/*Switch on P2 (S1) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & switch_mask) {   /*did a button cause this interrupt? */
    P2IFG &= ~switch_mask;    /*clear pending sw interrupts */
    switch_interrupt_handler();
  }
}
