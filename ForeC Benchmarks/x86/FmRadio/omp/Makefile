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

diff:
	- diff FmRadio.txt ../original/FmRadio.txt

clean:
	rm -f FmRadio *.exe *.raw *.txt

