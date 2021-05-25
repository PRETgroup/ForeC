ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
else
	CC			= gcc
endif

.c:
	$(CC) -O0 -Wall $< -o $*

compress:
	./Lzss -c result.lzs data.txt
	
decompress:
	./Lzss -d result.lzs

clean:
	rm -f Lzss *.exe *.lzs result_data.txt

