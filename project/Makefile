# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c
AR		= msp430-elf-ar

all:wakedemo.elf

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} led.o buzzer.o stateMachines.o p2switches.o toymain.o wdt_handler.o scaleSongSM.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lp2sw 

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
