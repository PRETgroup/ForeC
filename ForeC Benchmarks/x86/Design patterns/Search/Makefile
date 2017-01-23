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
	forecc Search.forec Search.foreh
	
c:
	$(CC) $(CFLAGS) -Wall Search.c -o Search -pthread
	
clean:
	rm -f Search *.exe *.dot *.c *.txt *.pdf *.xml
