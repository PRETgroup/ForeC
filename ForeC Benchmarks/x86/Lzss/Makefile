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
	forecc Lzss.forec Lzss.1.foreh

c:
	$(CC) $(CFLAGS) Lzss.c -o Lzss

compress:
	./Lzss -c result.lzs data.txt
	
decompress:
	./Lzss -d result.lzs

dot:
	dot -T pdf Lzss.dot -o Lzss.pdf

clean:
	rm -f Lzss *.exe *.dot *.c *.lzs result_data.txt debug.txt *.pdf *.xml

