#ifndef stateMachine_included
#define stateMachine_included

extern char button_state;

void changeButtonState(char button_pushed);

short convertNote(short note);

void scaleStateMachine();

void snakeStateMachine();

void dimStateMachine();

void christmasStateMachine();

void spiderStateMachine();

#endif //included
