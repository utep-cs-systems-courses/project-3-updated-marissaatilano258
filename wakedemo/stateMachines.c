#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state = 0;
static char scale_state = -1;
static char snake_state = -1;
static char christmas_state = -1;
static char spider_state = -1;

void changeButtonState(char button_pushed)
{
  button_state = button_pushed;
  scale_state = -1;
  christmas_state = -1;
  snake_state = -1;
  spider_state = -1;
  buzzer_set_period(0);
}

void scaleStateMachine()
{
  short note = 0;
  static int row = 145;
  static int col = 0;

  switch(scale_state){
  case 0:
    note = 261;
    drawString11x16(col, row, "Do", COLOR_BLACK, COLOR_RED);
    break;
  case 1:
    note = 294;
    drawString11x16(col, row, "Re", COLOR_BLACK, COLOR_ORANGE);
    break;
  case 2:
    note = 330;
    drawString11x16(col, row, "Mi", COLOR_BLACK, COLOR_YELLOW);
    break;
  case 3:
    note = 349;
    drawString11x16(col, row, "Fa", COLOR_BLACK, COLOR_GREEN);
    break;
  case 4:
    note = 392;
    drawString11x16(col, row, "So", COLOR_BLACK, COLOR_BLUE);
    break;
  case 5:
    note = 440;
    drawString11x16(col, row, "La", COLOR_BLACK, COLOR_AQUAMARINE);
    break;
  case 6:
    note = 494;
    drawString11x16(col, row, "Ti", COLOR_BLACK, COLOR_PURPLE);
    break;
  case 7:
    note = 523;
    drawString11x16(col, row, "Do", COLOR_BLACK, COLOR_VIOLET);
    break;
  default:
    clearScreen(COLOR_WHITE);
    scale_state = -1;
    note = 0;
    col = -15;
    row = 165;
    break;
  }
  col+=15;
  row-=20;
  scale_state++;
  buzzer_set_period(2000000/note);
}

  

void snakeStateMachine(u_int col_offset, u_int thickness)
{
  static u_int row = 0;
  static u_int col = 60;
  static u_int snake_colorBGR = COLOR_GREEN;
  u_int length = 8;

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
    row += length;
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
  default:
    row = 0;
    col = 60;
    snake_colorBGR = COLOR_GREEN;
    clearScreen(COLOR_RED);
    snake_state = 0;
    break;
  }
}

void christmasSongStateMachine()
{
  static char christmas_song_state = 0;
  short note = 0;

  switch(christmas_song_state){
  case 0:
  case 1:
    note = 587;
    break;
  case 2:
  case 3:
    note = 659;   /*E*/
    break;
  case 4:
  case 5:
    note = 587;
    break;
  case 6:
  case 7:
    note = 494;
    break;
  case 8:
  case 9:
    note = 784;
    break;
  case 10:
  case 11:
    note = 659;
    break;
  case 12:
  case 13:
  case 14:
  case 15:
    note = 587;
    break;
  case 16:
    note = 0;
    break;
  case 17:
  case 18:
    note = 587;
    break;
  case 19:
    note = 659;
    break;
  case 20:
    note = 587;
    break;
  case 21:
    note = 659;
    break;
  case 22:
    note = 587;
    break;
  case 23:
    note = 784;
    break;
  case 24:
  case 25:
  case 26:
  case 27:
    note = 698;
    break;
  default:
    christmas_song_state = -1;
    note = 0;
    break;
  }
  
  christmas_song_state++;
  buzzer_set_period(2000000/note);
    
}

void christmasStateMachine()
{
  static u_int tree_colorBGR = COLOR_GREEN;

  switch(christmas_state){
  case 0:
    drawRectFromCenter(10, 25, 60, 120, COLOR_BROWN);
    christmas_state++;
    break;
  case 1:
    drawTriangle(60, 25, 20, tree_colorBGR);
    christmas_state++;
    break;
  case 2:
    drawTriangle(60, 40, 35, tree_colorBGR);
    christmas_state++;
    break;
  case 3:
    drawTriangle(60, 50, 60, tree_colorBGR);
    christmas_state = 1;
    tree_colorBGR = (tree_colorBGR == COLOR_GREEN) ? COLOR_RED : COLOR_GREEN;
    break;
  default:
    christmas_state = 0;
    tree_colorBGR = COLOR_GREEN;
    clearScreen(COLOR_WHITE);
    break;
  }

  christmasSongStateMachine();
    
}

void drawSpider(u_int row, u_int body_colorBGR, u_int head_colorBGR, u_int string_colorBGR){
  u_int col = 60;
  u_int square_length = 20;
  u_int line_length = 15;
  
  drawDownwardLine(col, row-square_length, string_colorBGR);
  drawRectFromCenter(square_length, square_length, col, row, body_colorBGR);
  drawRectFromCenter(square_length/2, square_length/2, col, row, head_colorBGR);
  for(int j = 0; j < 48; j+=12){
    for(int i = 0; i < 3; i++){
      u_int leg_row = row-square_length-line_length+j+i;
      u_int left_leg_col = col-square_length-line_length;
      u_int right_leg_col = col+square_length+line_length;
      drawLeftDiagnol(leg_row, right_leg_col, line_length, body_colorBGR);
      drawLeftDiagnol(leg_row, left_leg_col, line_length, body_colorBGR);
      drawRightDiagnol(leg_row, right_leg_col, line_length, body_colorBGR);
      drawRightDiagnol(leg_row, left_leg_col, line_length, body_colorBGR);
    }
  }
}


void spiderStateMachine()
{
  static u_int row = 80;
  static u_int prev_row = 80;
 
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
    row = row -10;
    spider_state++;
    break;
  case 7:
    row = row - 10;
    spider_state = 0;
    break;
  default:
    row = 80;
    prev_row = 80;
    clearScreen(COLOR_BLACK);
    spider_state = 0;
  }

  drawSpider(prev_row, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
  drawSpider(row, COLOR_PURPLE, COLOR_MEDIUM_PURPLE, COLOR_WHITE);
  prev_row = row;
}
