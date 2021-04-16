ifeq ($(shell uname), Linux)
	CC			= gcc -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

.c:
	$(CC) $< -o $*

clean:
	rm -f FlyByWire_runtime *.exe *.txt

