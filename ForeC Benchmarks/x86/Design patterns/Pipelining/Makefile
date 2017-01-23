ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread
else
	CC			= gcc
endif

forec:
	forecc Pipelining.forec Pipelining.foreh
	
c:
	$(CC) $(CFLAGS) -Wall Pipelining.c -o Pipelining -pthread
	
clean:
	rm -f Pipelining *.exe *.dot *.c *.txt *.pdf *.xml
