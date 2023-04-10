# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: buzzer-c.elf buzzer-s.elf

#additional rules for files
buzzer-c.elf: ${COMMON_OBJECTS} buzzer.o buzzerMain.o controlRed-c.o controlGreen-c.o state_advance-c.o
	${CC} ${CFLAGS} -o $@ $^ ../lib/libTimer.a
buzzer-s.elf: ${COMMON_OBJECTS} buzzer.o buzzerMain.o controlRed-s.o controlGreen-s.o state_advance-s.o
	${CC} ${CFLAGS} -o $@ $^ ../lib/libTimer.a

load-c: buzzer-c.elf
	msp430loader.sh  $^
load-s: buzzer-s.elf
	msp430loader.sh $^
clean: 
	rm -f *.o *.elf

buzzer.c: buzzer.h
buzzerMain.c: buzzer.h
controlRed-c.o: buzzer.h
controlGreen-c.o: buzzer.h
state_advance-c.o: buzzer.h
