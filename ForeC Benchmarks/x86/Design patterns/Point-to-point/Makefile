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
	forecc Point-to-point.forec Point-to-point.foreh
	
c:
	$(CC) $(CFLAGS) -Wall Point-to-point.c -o Point-to-point -pthread
	
clean:
	rm -f Point-to-point *.exe *.dot *.c *.txt *.pdf *.xml
