ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread -O3
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -O3
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

