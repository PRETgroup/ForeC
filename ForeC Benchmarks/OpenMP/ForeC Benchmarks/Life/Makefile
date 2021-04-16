ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g
	LDFLAGS		= -L/usr/X11R6/lib
else
	CC			= gcc
endif

forec:
	forecc Life.forec Life.4.foreh

c:
	$(CC) $(CFLAGS) -Wall Life.c -o Life

dot:
	dot -T pdf Life.dot -o Life.pdf

visual.forec:
	forecc Life.visual.forec Life.visual.foreh

visual.c:
	$(CC) $(CFLAGS) -Wall Life.visual.c -o Life.visual $(LDFLAGS) -lX11

visual.dot:
	dot -T pdf Life.visual.dot -o Life.visual.pdf

clean:
	rm -f Life Life.visual *.exe *.c *.dot *.txt *.xml *.pdf

