CC = clang

CFLAGS = -Xclang -fopenmp
LDFLAGS = -lomp

SRC = test.c
BIN = test

all: 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(BIN)

clean:
	rm $(BIN)