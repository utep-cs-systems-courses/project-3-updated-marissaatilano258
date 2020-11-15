#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"

void snakeStateMachine(u_int colOffset, u_int thickness)
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
    for(u_int i = 0; i < thickness; i++){
      drawRightDiagnol(row, col+i, length, colorBGR);
      if(colOffset != 0){
	drawRightDiagnol(row, col+i+colOffset, length, colorBGR);
	drawRightDiagnol(row, col+i-colOffset, length, colorBGR);
      }
    }
    row += length;
    col += length;
    state++;
    break;
  case 1:
    for(u_int i = 0; i < thickness; i++){
      drawLeftDiagnol(row, col+i, length, colorBGR);
      if(colOffset != 0){
	drawLeftDiagnol(row, col+i+colOffset, length, colorBGR);
	drawLeftDiagnol(row, col+i-colOffset, length, colorBGR);
      }
    }
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
  static u_int state = -1;
  static u_int row = 80;
  static u_int prevRow = 80;
  u_int col = 60;
  u_int squareLength = 20;
  u_int lineLength = 15;

  switch(state){
  case 0:
  case 1:
  case 2:
  case 3:
    row = row + 10;
    state++;
    break;
  case 4:
  case 5:
  case 6:
    row = row - 10;
    state++;
    break;
  case 7:
    row = row - 10;
    state = 0;
    break;
  default:
    clearScreen(COLOR_BLACK);
    state = 0;
  }

  drawSpider(prevRow, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
  drawSpider(row, COLOR_PURPLE, COLOR_MEDIUM_PURPLE, COLOR_WHITE);
  prevRow = row;
}

void drawSpider(u_int row, u_int bodyColorBGR, u_int headColorBGR, u_int stringColorBGR){
  u_int col = 60;
  u_int squareLength = 20;
  u_int lineLength = 15;
  
  drawDownwardLine(col, row-squareLength, stringColorBGR);
  drawRectFromCenter(squareLength, squareLength, col, row, bodyColorBGR);
  drawRectFromCenter(squareLength/2, squareLength/2, col, row, headColorBGR);
  for(int j = 0; j < 48; j+=12){
    for(int i = 0; i < 3; i++){
      u_int legRow = row-squareLength-lineLength+j+i;
      u_int leftLegCol = col-squareLength-lineLength;
      u_int rightLegCol = col+squareLength+lineLength;
      drawLeftDiagnol(legRow, rightLegCol, lineLength, bodyColorBGR);
      drawLeftDiagnol(legRow, leftLegCol, lineLength, bodyColorBGR);
      drawRightDiagnol(legRow, rightLegCol, lineLength, bodyColorBGR);
      drawRightDiagnol(legRow, leftLegCol, lineLength, bodyColorBGR);
    }
  }
}
