ifeq ($(shell uname), Linux)
	CC			= gcc
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

.c:
	$(CC) -Wall $< -o $*

clean:
	rm -f MatrixMultiply *.exe

