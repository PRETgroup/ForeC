ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g -lrt
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g
else
	CC			= gcc
endif

forec:
	forecc FmRadio_runtime.forec FmRadio.4.foreh

c:
	$(CC) FmRadio_runtime.c $(CFLAGS) -Wall -o FmRadio_runtime -lm

dot:
	dot -T pdf FmRadio.dot -o FmRadio.pdf

diff:
	- diff FmRadio.txt ../original/FmRadio.txt

all:
	make forec; make c; ./FmRadio; make diff

clean:
	rm -f FmRadio_runtime *.exe *.dot *.txt *.raw *.c *.pdf *.xml

