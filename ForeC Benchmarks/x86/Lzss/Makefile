ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -O0 -Wall -pthread
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -O0 -Wall -pthread
else
	CC			= gcc
endif

forec:
	forecc lzss.forec lzss.4.foreh

c:
	$(CC) $(CFLAGS) lzss.c -o lzss

compress:
	./lzss -c result.lzs data.txt
	
decompress:
	./lzss -d result.lzs

dot:
	dot -T pdf lzss.dot -o lzss.pdf

clean:
	rm -f lzss *.exe *.dot *.c *.lzs result_data.txt debug.txt *.pdf *.xml

