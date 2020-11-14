#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"

void snakeStateMachine()
{
  static u_int row = 0;
  static u_int col = 60;
  static u_int length = 8;
  static u_int colorBGR = COLOR_GREEN;
  static u_int state = 0;

  if(row >= 160){
    row = 0;
    col = 60;
    state = 0;
    colorBGR = (colorBGR == COLOR_GREEN) ? COLOR_BLUE: COLOR_GREEN;
  }

  switch(state){
  case 0:
    drawRightDiagnol(row, col, length, colorBGR);
    row += length;
    col += length;
    state++;
    break;
  case 1:
    drawLeftDiagnol(row, col, length, colorBGR);
    row += length;
    col -= length;
  default:
    state = 0;
    break;
  }
}


void christmasStateMachine()
{
  static u_int state = 0;
  static u_int colorBGR = COLOR_GREEN;

  switch(state){
  case 0:
    drawRectFromCenter(10, 25, 60, 120, COLOR_BROWN);
    state++;
    break;
  case 1:
    drawTriangle(60, 25, 20, colorBGR);
    state++;
    break;
  case 2:
    drawTriangle(60, 40, 35, colorBGR);
    state++;
    break;
  case 3:
    drawTriangle(60, 50, 60, colorBGR);
  default:
    state = 1;
    colorBGR = (colorBGR == COLOR_GREEN) ? COLOR_RED : COLOR_GREEN;
    break;
  }
    
}

void spiderStateMachine()
{
  drawPixel(5,5,COLOR_BLACK);
}
