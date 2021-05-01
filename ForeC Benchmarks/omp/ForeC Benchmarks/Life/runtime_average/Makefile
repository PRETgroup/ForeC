ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g -lrt
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g -lrt
	LDFLAGS		= -L/usr/X11R6/lib
else
	CC			= gcc
endif

forec:
	forecc Life_runtime.forec Life.4.foreh

c:
	$(CC) Life_runtime.c $(CFLAGS) -Wall -o Life_runtime

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

