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
	forecc Combine.forec Combine.foreh
	
c:
	$(CC) $(CFLAGS) -Wall Combine.c -o Combine -pthread
	
clean:
	rm -f Combine *.exe *.dot *.c *.txt *.pdf *.xml

