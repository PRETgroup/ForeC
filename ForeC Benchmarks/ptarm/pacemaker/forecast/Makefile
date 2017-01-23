ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

CFLAGS		= -pthread -g -O0

forec:
	forecc pacemaker.forec pacemaker.foreh

c:
	$(CC) $(CFLAGS) -Wall pacemaker.c -o pacemaker

dot:
	dot -T pdf pacemaker.dot -o pacemaker.pdf

clean:
	rm -f pacemaker *.exe *.c *.dot *.txt *.xml *.pdf

