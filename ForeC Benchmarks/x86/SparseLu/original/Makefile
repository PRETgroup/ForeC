ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif


.c:
	$(CC) -Wall $< -o $*

clean:
	rm -f SparseLu *.exe
