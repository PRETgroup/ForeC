ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -Wall -O0 -pthread
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -Wall -O0 -pthread
else
	CC			= gcc
endif

forec:
	forecc FlyByWire.forec FlyByWire.4.foreh

c:
	$(CC) $(CFLAGS) FlyByWire.c -o FlyByWire

dot:
	dot -T pdf FlyByWire.dot -o FlyByWire.pdf

diff:
	- diff output.txt original/output.txt

clean:
	rm -f FlyByWire *.exe *.dot *.c *.txt *.pdf *.xml

