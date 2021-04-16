ifeq ($(shell uname), Linux)
	CC			= gcc
	CFLAGS		= -pthread -g -lrt
else ifeq ($(shell uname), Darwin)
	CC			= clang
	CFLAGS		= -pthread -g -lrt
	LDFLAGS		= -L/usr/X11R6/lib
else
	CC			= gcc
endif

forec:
	forecc Mandelbrot_runtime.forec Mandelbrot.4.foreh

c:
	$(CC) Mandelbrot_runtime.c $(CFLAGS) -Wall -o Mandelbrot_runtime

dot:
	dot -T pdf Mandelbrot.dot -o Mandelbrot.pdf

visual.forec:
	forecc Mandelbrot.visual.forec Mandelbrot.visual.foreh

visual.c:
	$(CC) $(CFLAGS) -Wall Mandelbrot.visual.c -o Mandelbrot.visual $(LDFLAGS) -lX11

visual.dot:
	dot -T pdf Mandelbrot.visual.dot -o Mandelbrot.visual.pdf

clean:
	rm -f Mandelbrot_runtime Mandelbrot.visual *.exe *.c *.dot *.txt *.xml *.pdf

