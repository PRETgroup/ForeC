ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g
else
	CC			= gcc
	CFLAGS		= -pthread -g
endif

forec:
	forecc MatrixMultiply.forec MatrixMultiply.1.foreh

c:
	$(CC) $(CFLAGS) MatrixMultiply.c -o MatrixMultiply

dot:
	dot -T pdf MatrixMultiply.dot -o MatrixMultiply.pdf

clean:
	rm -f MatrixMultiply *.exe *.dot *.c *.txt *.xml *.pdf

