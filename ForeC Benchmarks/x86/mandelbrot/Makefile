ifeq ($(shell uname), Linux)
	CC			= clang
	CFLAGS		= -pthread
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -O0 -Wall -pthread
	LDFLAGS		= -I/opt/X11/include -L/opt/X11/lib
else
	CC			= gcc
endif

forec:
	forecc Mandelbrot.forec Mandelbrot.1.foreh

c:
	$(CC) $(CFLAGS) Mandelbrot.c -o Mandelbrot

dot:
	dot -T pdf Mandelbrot.dot -o Mandelbrot.pdf

visual.forec:
	forecc Mandelbrot.visual.forec Mandelbrot.visual.foreh

visual.c:
	$(CC) $(CFLAGS) Mandelbrot.visual.c -o Mandelbrot.visual $(LDFLAGS) -lX11

visual.dot:
	dot -T pdf Mandelbrot.visual.dot -o Mandelbrot.visual.pdf

clean:
	rm -f Mandelbrot Mandelbrot.visual *.exe *.c *.dot *.txt *.xml *.pdf

