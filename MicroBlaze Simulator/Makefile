# MicroBlaze Simulator Makefile.

# Determine best C++ compiler to use
ifeq ($(shell uname), Linux)
	CC					= clang++
else ifeq ($(shell uname), Darwin)
	CC					= clang++
	LIB_ELF_INTERNAL	= -D __LIBELF_INTERNAL__
	HOMEBREW_INCLUDES	= -I $(HOMEBREW_PREFIX)/include/libelf
	LIBS				= -L $(HOMEBREW_PREFIX)/lib
else
	CC					= g++
endif

CFLAGS	= -Wall -O3 $(HOMEBREW_INCLUDES) $(LIB_ELF_INTERNAL)
LDFLAGS	= -lelf $(LIBS)
OBJS	= MicroBlaze.o System.o MicroBlazeElf.o Counter.o MutexEsterel.o MutexForeC.o Uart.o PrivateMemoryBus.o SharedMemoryBus.o ThreadQueue.o
BIN		= mb-sim

all: Main

MicroBlaze.o: MicroBlaze.cpp MicroBlaze_autogen.py
	python3 MicroBlaze_autogen.py
	$(CC) -c MicroBlaze.cpp $(CFLAGS)

Main: Main.o $(OBJS)
	$(CC) -o $(BIN) Main.o $(OBJS) $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o MicroBlaze_autogen.cpp Simulator *.tex *.elf $(BIN)

rcs: clean
	ci -l *.c *.h *.py Makefile 

