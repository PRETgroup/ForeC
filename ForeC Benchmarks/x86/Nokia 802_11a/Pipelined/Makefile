ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -O3
else
	CC			= gcc
endif

forec:
	forecc 802_11a.forec 802_11a.01.foreh

c:
	$(CC) $(CFLAGS) -Wall 802_11a.c -o 802_11a
	mkdir -p plainC_SimOutput

dot:
	dot -T pdf 802_11a.dot -o 802_11a.pdf

diff:
	- diff plainC_SimOutput/CHC_out_I.am ../Original/plainC_SimOutput/CHC_out_I.am
	- diff plainC_SimOutput/CHC_out_Q.am ../Original/plainC_SimOutput/CHC_out_Q.am

all:
	make forec; make c; ./802_11a; make diff

clean:
	rm -f 802_11a *.exe *.dot *.txt plainC_SimOutput/* *.pdf *.xml

