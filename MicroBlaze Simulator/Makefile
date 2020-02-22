# MicroBlaze Simulator Makefile.

# Determine best C++ compiler to use
ifeq ($(shell uname), Linux)
	CC					= clang++
else ifeq ($(shell uname), Darwin)
	CC					= clang++
	HOMEBREW_INCLUDES	= -I/usr/local/Cellar/libelf/0.8.13_1/include/libelf
else
	CC					= g++
endif

CFLAGS	= -Wall -O3 $(HOMEBREW_INCLUDES)
LDFLAGS	= -lelf
OBJS	= MicroBlaze.o System.o MicroBlazeElf.o Counter.o MutexEsterel.o MutexForeC.o Uart.o PrivateMemoryBus.o SharedMemoryBus.o ThreadQueue.o
BIN		= mb-sim

all: Main

MicroBlaze.o: MicroBlaze.cpp MicroBlaze_autogen.py
	python MicroBlaze_autogen.py
	$(CC) -c MicroBlaze.cpp $(CFLAGS)

Main: Main.o $(OBJS)
	$(CC) -o $(BIN) Main.o $(OBJS) $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o MicroBlaze_autogen.cpp Simulator *.tex *.elf $(BIN)

rcs: clean
	ci -l *.c *.h *.py Makefile 

