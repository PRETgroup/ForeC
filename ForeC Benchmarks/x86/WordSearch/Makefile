ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread -O3
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -O3
else
	CC			= gcc
endif

forec:
	forecc WordSearch.forec WordSearch.1.foreh

c:
	$(CC) $(CFLAGS) WordSearch.c -o WordSearch
	
search:
	./WordSearch the text/file1.txt text/file2.txt

dot:
	dot -T pdf WordSearch.dot -o WordSearch.pdf

clean:
	rm -f WordSearch *.exe *.dot *.c *.txt *.xml *.pdf
