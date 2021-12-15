CC			= clang
LDFLAGS		= -lomp -lm

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
	- diff FmRadio.txt ../original/FmRadio.txt

clean:
	rm -f FmRadio *.exe *.raw *.txt

