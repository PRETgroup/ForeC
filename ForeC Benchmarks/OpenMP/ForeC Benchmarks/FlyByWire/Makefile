ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g
else
	CC			= gcc
endif

forec:
	forecc FlyByWire.forec FlyByWire.4.foreh

c:
	$(CC) $(CFLAGS) -Wall FlyByWire.c -o FlyByWire

dot:
	dot -T pdf FlyByWire.dot -o FlyByWire.pdf

clean:
	rm -f FlyByWire *.exe *.dot *.c *.txt *.pdf

