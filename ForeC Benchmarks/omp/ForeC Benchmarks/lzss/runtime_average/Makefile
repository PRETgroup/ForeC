ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g -lrt
else ifeq ($(shell uname), Darwin)
	CC			= clang -lrt
	CFLAGS		= -pthread -g
else
	CC			= gcc
endif

forec:
	forecc Lzss_runtime.forec Lzss.4.foreh

c:
	$(CC) Lzss_runtime.c $(CFLAGS) -Wall -o Lzss_runtime

compress:
	./Lzss_runtime -c result.lzs data.txt
	
decompress:
	./Lzss_runtime -d result.lzs

dot:
	dot -T pdf Lzss.dot -o Lzss.pdf

clean:
	rm -f Lzss_runtime *.exe *.dot *.c *.lzs result_data.txt debug.txt *.pdf *.xml

