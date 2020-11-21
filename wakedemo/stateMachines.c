#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state = 0;
static char snake_state = -1;
static char christmas_state = -1;
static char spider_state = -1;

void changeButtonState(char button_pushed)
{
  button_state = button_pushed;
  christmas_state = -1;
  snake_state = -1;
  spider_state = -1;
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
