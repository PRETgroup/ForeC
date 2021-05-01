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
	forecc MatrixMultiply.forec MatrixMultiply.4.foreh

c:
	$(CC) $(CFLAGS) MatrixMultiply.c -o MatrixMultiply

dot:
	dot -T pdf MatrixMultiply.dot -o MatrixMultiply.pdf

clean:
	rm -f MatrixMultiply *.exe *.dot *.c *.txt *.xml *.pdf

