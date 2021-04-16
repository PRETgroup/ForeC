ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g
	LDFLAGS		= -L/usr/X11R6/lib
else
	CC			= gcc
endif

forec:
	forecc Mandelbrot.forec Mandelbrot.4.foreh

c:
	$(CC) $(CFLAGS) -Wall Mandelbrot.c -o Mandelbrot

dot:
	dot -T pdf Mandelbrot.dot -o Mandelbrot.pdf

visual.forec:
	forecc Mandelbrot.visual.forec Mandelbrot.visual.foreh

visual.c:
	$(CC) $(CFLAGS) -Wall Mandelbrot.visual.c -o Mandelbrot.visual $(LDFLAGS) -lX11

visual.dot:
	dot -T pdf Mandelbrot.visual.dot -o Mandelbrot.visual.pdf

clean:
	rm -f Mandelbrot Mandelbrot.visual *.exe *.c *.dot *.txt *.xml *.pdf

