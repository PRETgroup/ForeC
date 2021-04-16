#
# Laboratory for Scientific Computing
# http://www.lam-mpi.org/tutorials/
# University of Notre Dame
#
# MPI Tutorial
# Sample Makefile
#

ifeq ($(shell uname), Linux)
	CC			= gcc
else ifeq ($(shell uname), Darwin)
	CC			= clang
	LDFLAGS		= -L/usr/X11R6/lib
else
	CC			= gcc
endif

c:
	$(CC) $(CFLAGS) -Wall Mandelbrot_runtime.c -o Mandelbrot_runtime

visual.c:
	$(CC) $(CFLAGS) -Wall Mandelbrot.visual.c -o Mandelbrot.visual $(LDFLAGS) -lX11

clean:
	rm -f Mandelbrot_runtime Mandelbrot.visual *.exe

