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
	forecc MatrixMultiply_runtime.forec MatrixMultiply.4.foreh

c:
	$(CC) MatrixMultiply_runtime.c $(CFLAGS) -o MatrixMultiply_runtime

dot:
	dot -T pdf MatrixMultiply.dot -o MatrixMultiply.pdf

clean:
	rm -f MatrixMultiply_runtime *.exe *.dot *.c *.txt *.xml *.pdf

