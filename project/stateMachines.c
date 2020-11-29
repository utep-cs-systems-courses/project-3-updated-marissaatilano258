#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "scaleSongSM.h"
#include "led.h"

char button_state = 0;
static char scale_state = -1;
static char snake_state = -1;
static char snake_song_state = -1;
static char christmas_state = -1;
static char christmas_song_state = -1;
static char spider_state = -1;
static char spider_song_state = -1;
static char dim_state = 0;

void changeButtonState(char button_pushed)
{
  button_state = button_pushed;
  scale_state = -1;
  snake_state = -1;
  snake_song_state = -1;
  christmas_state = -1;
  christmas_song_state = -1;
  spider_state = -1;
  spider_song_state = -1;
  buzzer_set_period(0);
}

short convertNote(short note)
{
  return 2000000/note;
}

void scaleStateMachine()            /*Displays scale on LCD screen*/
{
  static int row = 145;
  static int col = 0;
  short note = 0;

  switch(scale_state){
  case 0:
    drawString11x16(col, row, "Do", COLOR_BLACK, COLOR_RED);
    break;
  case 1:
    drawString11x16(col, row, "Re", COLOR_BLACK, COLOR_ORANGE);
    break;
  case 2:
    drawString11x16(col, row, "Mi", COLOR_BLACK, COLOR_YELLOW);
    break;
  case 3:
    drawString11x16(col, row, "Fa", COLOR_BLACK, COLOR_GREEN);
    break;
  case 4:
    drawString11x16(col, row, "So", COLOR_BLACK, COLOR_BLUE);
    break;
  case 5:
    drawString11x16(col, row, "La", COLOR_BLACK, COLOR_AQUAMARINE);
    break;
  case 6:
    drawString11x16(col, row, "Ti", COLOR_BLACK, COLOR_PURPLE);
    break;
  case 7:
    drawString11x16(col, row, "Do", COLOR_BLACK, COLOR_VIOLET);
    break;
  default:                           /*Clears screen and resets row, col, and state*/
    clearScreen(COLOR_WHITE);
    scale_state = -1;
    col = -15;
    row = 165;
    break;
  }
  col+=15;
  row-=20;
  note = scaleSongStateMachine(scale_state);     /* Gets value of the converted note to correspond with the scale state*/
  buzzer_set_period(note);
  scale_state++;
}

void snakeSongStateMachine()
{
  short note = 0;

  switch(snake_song_state){
  case 0:
    note = 440;     /*A*/
    break;
  case 1:
    note = 494;     /*B*/
    break;
  case 2:
  case 3:
    note = 523;     /*C*/
    break;
  case 4:
  case 5:
    note = 494;     /*B*/
    break;
  case 6:
    note = 440;     /*A*/
    break;
  case 7:
    note = 0;     
    break;
  case 8:
    note = 440;     /*A*/
    break;
  case 9:
    note = 494;     /*B*/
    break;
  case 10:
    note = 523;     /*C*/
    break;
  case 11:
    note = 659;     /*E*/
    break;
  case 12:
    note = 494;     /*B*/
    break;
  case 13:
    note = 523;     /*C*/
    break;
  case 14:
    note = 440;     /*A*/
    break;
  default:          /*Silent note and resets the state machine*/
    note = 0;
    snake_song_state = -1;
    break;
  }
  snake_song_state++;
  buzzer_set_period(convertNote(note));
}

void snakeStateMachine()
{
  static u_int row = 0;
  static u_int col = 60;
  static u_int snake_colorBGR = COLOR_GREEN;
  u_int length = 8;                           /*Length of the diagnol line*/
  u_int col_offset = 40;                      /*Column offset between snakes*/
  u_int thickness = 5;                        /*Thickness of the snake*/

  /*Resets the row, col, and changes the snake color when the bottom of the screen is reached*/
    if(row >= 160){
    row = 0;
    col = 60;
    snake_state = 0;
    snake_colorBGR = (snake_colorBGR == COLOR_GREEN) ? COLOR_RED: COLOR_GREEN;
  }

  switch(snake_state){
  case 0:
    for(u_int i = 0; i < thickness; i++){
      drawRightDiagnol(row, col+i, length, snake_colorBGR);
      drawRightDiagnol(row, col+i+col_offset, length, snake_colorBGR);
      drawRightDiagnol(row, col+i-col_offset, length, snake_colorBGR);
    }
    row += length;          /*Moves row and column to the end of the drawn line*/
    col += length;
    snake_state++;
    break;
  case 1:
    for(u_int i = 0; i < thickness; i++){
      drawLeftDiagnol(row, col+i, length, snake_colorBGR);
      drawLeftDiagnol(row, col+i+col_offset, length, snake_colorBGR);
      drawLeftDiagnol(row, col+i-col_offset, length, snake_colorBGR);
    }
    row += length;
    col -= length;
    snake_state = 0;
    break;
  default:    /*Clears the screen and resets the static variables*/
    row = 0;
    col = 60;
    snake_colorBGR = COLOR_GREEN;
    clearScreen(COLOR_RED);
    snake_state = 0;
    break;
  }
  snakeSongStateMachine(); /*Plays song to correspond with this state machine*/
}

char on_on_off()
{
  static char state = 0;
  char changed = 0;

  switch(state){
  case 0:
    green_on = 0;
    state++;
    changed = 1;
    break;
  case 1:
    green_on = 1;
    state++;
    changed = 1;
    break;
  case 2:
    green_on = 1;
    state = 0;
    changed = 0;
    break;
  }
  return changed;
}

char off_off_on()
{
  static char state = 0;
  char changed = 0;

  switch(state){
  case 0:
    green_on = 1;
    state++;
    changed = 1;
    break;
  case 1:
    green_on = 0;
    state++;
    changed = 1;
    break;
  case 2:
    green_on = 0;
    state = 0;
    changed = 0;
    break;
  }
  return changed;
}

void dimStateMachine()
{
  switch(dim_state){
  case 0:
    green_on = 1;
    led_changed = 1;
    led_update();
    break;
  case 1:
    led_changed = on_on_off();
    led_update();
    break;
  case 2:
    led_changed = off_off_on();
    led_update();
    break;
  default:
    dim_state = 0;
    break;
  }
}
   
void christmasSongStateMachine()
{
  short note = 0;

  switch(christmas_song_state){
  case 0:
  case 1:
  case 2:
    note = 494;     /*B*/
    break;
  case 3:
    note = 523;     /*C*/
    break;
  case 4:
    note = 494;     /*B*/
    break;
  case 5:
    note = 466;     /*A#*/
    break;
  case 6:
    note =494;      /*B*/
    break;
  case 7:
  case 8:
    note = 523;     /*C*/
    break;
  case 9:
    note = 554;     /*C#*/
    break;
  case 10:
    note = 587;     /*D*/
    break;
  case 11:
    note = 0;
    break;
  default:          /*Silent note and resets the state machine*/
    christmas_song_state = -1;
    note = 0;
    break;
  }
  
  christmas_song_state++;
  buzzer_set_period(convertNote(note));
    
}

void christmasStateMachine()
{
  static u_int tree_colorBGR = COLOR_GREEN;

  switch(christmas_state){
  case 0:
    drawRectFromCenter(10, 25, 60, 120, COLOR_BROWN);     /*Draws tree trunk*/
    christmas_state++;
    break;
  case 1:
    drawTriangle(60, 25, 20, tree_colorBGR);              /*Top Triangle*/
    christmas_state++;
    break;
  case 2:
    drawTriangle(60, 40, 35, tree_colorBGR);              /*Middle Triangle*/
    christmas_state++;
    break;
  case 3:
    drawTriangle(60, 50, 60, tree_colorBGR);              /*Bottom Triangle*/
    christmas_state = 1;
    tree_colorBGR = (tree_colorBGR == COLOR_GREEN) ? COLOR_RED : COLOR_GREEN; /*Alternates the color of the tree*/
    break;
  default:     /*Clears the screen and resets the state machine*/
    christmas_state = 0;
    tree_colorBGR = COLOR_GREEN;
    clearScreen(COLOR_LIGHT_BLUE);
    break;
  }

  christmasSongStateMachine();     /*Plays the song in correspondence with the state machine*/
}

void spiderSongStateMachine()
{
  short note = 0;

  switch(spider_song_state){
  case 0:
    note = 392;     /*G*/
    break;
  case 1:
  case 2:
  case 3:
    note = 523;     /*C*/
    break;
  case 4:
    note = 587;     /*D*/
    break;
  case 5:
  case 6:
    note = 659;     /*E*/
    break;
  case 7:
    note = 0;
    break;
  case 8:
    note = 659;     /*E*/
    break;
  case 9:
    note = 587;     /*D*/
    break;
  case 10:
    note = 523;     /*C*/
    break;
  case 11:
    note = 587;     /*D*/
    break;
  case 12:
    note = 659;     /*E*/
    break;
  case 13:
    note = 523;     /*C*/
    break;
  default:          /*Resets song*/
    spider_song_state = -1;
    note = 0;
    break;
  }
  spider_song_state++;
  buzzer_set_period(convertNote(note));
    
}

void spiderStateMachine()
{
  static u_int row = 80;       /*Row to begin drawing the spider*/
  static u_int prev_row = 80;  /*Row where the previous spider was drawn*/
 
  switch(spider_state){
  case 0:
  case 1:
  case 2:
  case 3:
    row = row + 10;
    spider_state++;
    break;
  case 4:
  case 5:
  case 6:
    row = row - 10;
    spider_state++;
    break;
  case 7:
    row = row - 10;
    spider_state = 0;
    break;
  default:                      /*Resets screen, row, and prev_row*/
    row = 80;
    prev_row = 80;
    clearScreen(COLOR_BLACK);
    spider_state = 0;
  }

  drawSpider(prev_row, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);     /*Erase the previous spider*/
  drawSpider(row, COLOR_PURPLE, COLOR_MEDIUM_PURPLE, COLOR_WHITE); /*Draws the new spider*/
  prev_row = row;

  spiderSongStateMachine();     /*Plays the song in correspondence with this state machine*/
  dim_state++;
}
