ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g -lrt
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g -lrt
else
	CC			= gcc
endif

forec:
	forecc FlyByWire_runtime.forec FlyByWire.4.foreh

c:
	$(CC) FlyByWire_runtime.c $(CFLAGS) -Wall -o FlyByWire_runtime

dot:
	dot -T pdf FlyByWire.dot -o FlyByWire.pdf

clean:
	rm -f FlyByWire_runtime *.exe *.dot *.c *.txt *.pdf

