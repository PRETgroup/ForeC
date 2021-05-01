ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g
else
	CC			= gcc
endif

forec:
	forecc Lzss.forec Lzss.4.foreh

c:
	$(CC) $(CFLAGS) -Wall Lzss.c -o Lzss

compress:
	./Lzss -c result.lzs data.txt
	
decompress:
	./Lzss -d result.lzs

dot:
	dot -T pdf Lzss.dot -o Lzss.pdf

clean:
	rm -f Lzss *.exe *.dot *.c *.lzs result_data.txt debug.txt *.pdf *.xml

