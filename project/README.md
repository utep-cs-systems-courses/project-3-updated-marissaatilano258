# Project 3 : Graphical LCD Toy
##Description
This interrupt-driven program produces different sequences based on the button
#that is pushed on the msp430, including displaying images on the LCD screen,
#flashing the LEDs, and buzzing the buzzer.

Press S1 and the program will display the tonal scale and play the
corresponding note

Press S2 and the program will display a christmas tree that changes colors and
play the tune of White Christmas

Press S3 and the program will display snakes crawling down the screen and play
the tune of Snake Charmer

Press S4 and the program will display a bouncing spider and play the tune of
Itsy Bitsy Spider

## Files

The following files are included in this program.
File | Description
----------------| ----------------------------
assembly-c.s    | Defines the state machine for the tonal scale in assembly
assembly-c.h    | Header file containing declarations of methods in assemblyStateMachine.c
buzzer.c        | Initializes the buzzer and sets the period for buzzer cycles
buzzer.h        | Header file containing all declarations of the methods in buzzer.c
led.c           | Initializes leds and defines a function to update the state of each led
led.h           | Header file defining leds and containing all declarations of the methods in led.h
p2switches.c    | Initializes switches and corresponds interrupts to state machines
p2switches.h    | Header file containing all declarations of the methods in p2switches.c
stateMachines.c | Defines state machines used to display LCD screen, flash leds, and play buzzer
stateMachines.h | Header file containing all declarations of the methods instateMachines.c
toyMain.c       | Initializes components, controls interrupts, and redraws screen
wdt_handler.s   | Controls CPU OFF and handles interrupts 

##Compile and Run
You can compile this program by using the following commands
*   $make clean
*   $make

Next plug in the MSP430 to Linux

The following command runs the program
*   $make load

Use the buttons on the green board of the MSP430 to control the program
