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
	LDFLAGS		= -I/usr/X11R6/include -L/usr/X11R6/lib
else
	CC			= gcc
endif

c:
	$(CC) $(CFLAGS) -O0 -Wall Life.c -o Life

visual.c:
	$(CC) $(CFLAGS) -O0 -Wall Life.visual.c -o Life.visual $(LDFLAGS) -lX11

clean:
	rm -f Life *.exe Life.visual

