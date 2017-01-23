ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread
else
	CC			= gcc
endif

forec:
	forecc 1D_CFD.forec 1D_CFD.foreh

c:
	$(CC) $(CFLAGS) 1D_CFD.c -o 1D_CFD

dot:
	dot -T pdf 1D_CFD.dot -o 1D_CFD.pdf

clean:
	rm -f 1D_CFD 1D_CFD.exe *.dot *.c *.txt *.xml

