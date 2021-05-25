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
	$(CC) $(CFLAGS) $(LDFLAGS) -Wall -O0 $< -o $*

diff:
	- diff output.txt ../original/output.txt

clean:
	rm -f FlyByWire *.exe *.txt

