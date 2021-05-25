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

compress:
	./Lzss -c result.lzs data.txt
	
decompress:
	./Lzss -d result.lzs

clean:
	rm -f Lzss *.exe *.lzs result_data.txt

