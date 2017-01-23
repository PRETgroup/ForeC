ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread -O3 -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -O3
else
	CC			= gcc
endif

forec:
	forecc FmRadio.forec FmRadio.1.foreh

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

