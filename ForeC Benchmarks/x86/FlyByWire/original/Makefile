ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

.c:
	$(CC) $< -o $*

clean:
	rm -f FlyByWire *.exe *.txt

