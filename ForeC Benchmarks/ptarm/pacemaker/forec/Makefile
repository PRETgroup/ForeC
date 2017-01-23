ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g
else
	CC			= gcc
endif

forec:
	forecc pacemaker_uppaal.forec pacemaker_uppaal.foreh

c:
	$(CC) $(CFLAGS) -Wall pacemaker_uppaal.c -o pacemaker_uppaal

dot:
	dot -T pdf pacemaker_uppaal.dot -o pacemaker_uppaal.pdf

clean:
	rm -f pacemaker_uppaal *.exe *.c *.dot *.txt *.xml *.pdf

