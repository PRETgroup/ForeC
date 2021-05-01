#
# Laboratory for Scientific Computing
# http://www.lam-mpi.org/tutorials/
# University of Notre Dame
#
# MPI Tutorial
# Sample Makefile
#

ifeq ($(shell uname), Linux)
	CC			= clang
else ifeq ($(shell uname), Darwin)
	CC			= clang
	LDFLAGS		= -L/usr/X11R6/lib
else
	CC			= gcc
endif

c:
	$(CC) $(CFLAGS) -Wall -fopenmp Mandelbrot_omp.c -o Mandelbrot_omp

visual.c:
	$(CC) $(CFLAGS) -Wall -fopenmp Mandelbrot.visual_omp.c -o Mandelbrot.visual $(LDFLAGS) -lX11

clean:
	rm -f Mandelbrot_omp Mandelbrot.visual *.exe

