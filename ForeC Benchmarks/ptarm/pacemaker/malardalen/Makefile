# Determine best C compiler to use
ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

CFLAGS	= -O0 -Wall

SOURCES	= $(wildcard *.c)
PROGS = $(patsubst %.c, %, $(SOURCES))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(SOURCES:.c=)