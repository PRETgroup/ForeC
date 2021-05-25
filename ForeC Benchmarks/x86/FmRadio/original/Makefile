ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

.c:
	$(CC) -O0 -Wall $< -o $* -lm

clean:
	rm -f FmRadio *.exe *.raw *.txt

