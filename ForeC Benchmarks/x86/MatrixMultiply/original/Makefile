ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

.c:
	$(CC) -O0 -Wall $< -o $*

clean:
	rm -f MatrixMultiply *.exe

