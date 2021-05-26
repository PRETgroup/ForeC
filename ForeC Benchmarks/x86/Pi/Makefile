CC = clang
FORECC = forecc

CFLAGS = -O0 -Wall -Xclang -fopenmp -pthread
LDFLAGS = -lomp -latomic

% :: %.forec %.foreh
	$(FORECC) $*.forec $*.foreh
	$(CC) $(CFLAGS) $(LDFLAGS) $*.c -o $*
	rm -f $*.dot debug.txt information.xml

% :: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f Test BaselineSequential BaselineOpenMP BaselineForeC BaselinePthread