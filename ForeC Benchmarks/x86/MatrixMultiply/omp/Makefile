ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -Xclang -fopenmp
	LDFLAGS		= -lomp
else
	CC			= gcc
endif

.c:
	$(CC) $(CFLAGS) $(LDFLAGS) -Wall $< -o $*

clean:
	rm -f MatrixMultiply *.exe

