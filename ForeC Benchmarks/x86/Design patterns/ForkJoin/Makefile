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
	forecc ForkJoin.forec ForkJoin.foreh
	
c:
	$(CC) $(CFLAGS) -Wall ForkJoin.c -o ForkJoin -pthread
	
clean:
	rm -f ForkJoin *.exe *.dot *.c *.txt *.pdf *.xml
