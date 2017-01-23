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
	forecc Broadcast.forec Broadcast.foreh
	
c:
	$(CC) $(CFLAGS) -Wall Broadcast.c -o Broadcast -pthread
	
clean:
	rm -f Broadcast *.exe *.dot *.c *.txt *.pdf *.xml
