ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -g -Wall -pthread
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -O0 -Wall -pthread
	LDFLAGS		= -I/usr/local/include/X11 -L/usr/local/include/X11
else
	CC			= gcc
endif

forec:
	forecc Life.forec Life.1.foreh

c:
	$(CC) $(CFLAGS) Life.c -o Life

dot:
	dot -T pdf Life.dot -o Life.pdf

visual.forec:
	forecc Life.visual.forec Life.visual.foreh

visual.c:
	$(CC) $(CFLAGS) Life.visual.c -o Life.visual $(LDFLAGS) -lX11

visual.dot:
	dot -T pdf Life.visual.dot -o Life.visual.pdf

clean:
	rm -f Life Life.visual *.exe *.c *.dot *.txt *.xml *.pdf

