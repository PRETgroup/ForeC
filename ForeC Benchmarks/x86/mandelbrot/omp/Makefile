CC			= clang
LDFLAGS		= -lomp -latomic

ifeq ($(shell uname), Linux)
	CFLAGS		= -fopenmp
else ifeq ($(shell uname), Darwin)
	CFLAGS		= -Xclang -fopenmp
else
	CC			= gcc
endif

.c:
	$(CC) $(CFLAGS) $(LDFLAGS) -O0 -Wall $< -o $*

clean:
	rm -f Mandelbrot *.exe

