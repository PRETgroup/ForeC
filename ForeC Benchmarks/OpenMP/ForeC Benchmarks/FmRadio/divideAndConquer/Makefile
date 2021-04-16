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
	forecc FmRadio.forec FmRadio.4.foreh

c:
	$(CC) $(CFLAGS) -Wall FmRadio.c -o FmRadio -lm

dot:
	dot -T pdf FmRadio.dot -o FmRadio.pdf

diff:
	- diff FmRadio.txt ../original/FmRadio.txt

all:
	make forec; make c; ./FmRadio; make diff

clean:
	rm -f FmRadio *.exe *.dot *.txt *.raw *.c *.pdf *.xml

