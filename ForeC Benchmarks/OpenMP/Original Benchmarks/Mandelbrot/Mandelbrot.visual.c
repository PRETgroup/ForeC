//#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
//#include <unistd.h>
//#include <pthread.h>
//#include <err.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

/* X11 data */
static Display *dpy;
static Window win;
static XImage *bitmap;
static Atom wmDeleteMessage;
static GC gc;

/* Image size */
const int ASIZE = 1000;

#define MAX_ITER_VALUE	(1 << 14)
const int MAX_ITER = MAX_ITER_VALUE;
unsigned cols[MAX_ITER_VALUE + 1];

unsigned mandel_double(double cr, double ci);
void display_double(int size, double xmin, double xmax, double ymin, double ymax);
void init_colours(void);
void init_x11(int size);
void exit_x11(void);


int main(void) {
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	//- - - -

	double xmin = -2;
	double xmax = 1.0;
	double ymin = -1.5;
	double ymax = 1.5;
	
	/* Make a window! */
	init_x11(ASIZE);
	
	init_colours();
	
	display_double(ASIZE, xmin, xmax, ymin, ymax);
	
	/* Done! */
	exit_x11();
	
	//- - - -
	gettimeofday(&endTime,0);
	long seconds = endTime.tv_sec - startTime.tv_sec;
	int microseconds = endTime.tv_usec - startTime.tv_usec;
	if (microseconds < 0) {
		microseconds += 1000000;
		seconds--;
	}
	
	printf("Runtime: %ld.%.6d\r\n", seconds, microseconds);
	
	return 0;
}

/* The Inner Loop */
unsigned mandel_double(double cr, double ci) {
	double zr = cr, zi = ci;
	double tmp;
	
	unsigned i;
	
	for (i = 0; i < MAX_ITER; i++)
	{
		tmp = zr * zr - zi * zi + cr;
		zi *= 2 * zr;
		zi += ci;
		zr = tmp;
		
		if (zr * zr + zi * zi > 4.0) break;
	}
	
	return i;
}

/* For each point, evaluate its colour */
void display_double(int size, double xmin, double xmax, double ymin, double ymax) {
	int x, y;
	
	double cr, ci;
	
	double xscal = (xmax - xmin) / size;
	double yscal = (ymax - ymin) / size;
	
	unsigned counts;
	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++) {
			cr = xmin + x * xscal;
			ci = ymin + y * yscal;
			
			counts = mandel_double(cr, ci);
			
			((unsigned *) bitmap->data)[x + y*size] = cols[counts];
		}
		
		/* Display it line-by-line for speed */
		XPutImage(dpy, win, gc, bitmap, 0, y, 0, y, size, 1);
	}
	
	XFlush(dpy);
}

void init_colours(void) {
	int i;
	
	for (i = 0; i < MAX_ITER; i++) {
		char r = (rand() & 0xff) * MAX_ITER / (i + MAX_ITER + 1);
		char g = (rand() & 0xff) * MAX_ITER / (i + MAX_ITER + 1);
		char b = (rand() & 0xff) * MAX_ITER / (i + MAX_ITER + 1);
		
		cols[i] = b + 256 * g + 256 * 256 * r;
	}
	
	cols[MAX_ITER] = 0;
}

void init_x11(int size) {
	int bytes_per_pixel;
	
	/* Attempt to open the display */
	dpy = XOpenDisplay(NULL);
	
	/* Failure */
	if (!dpy) exit(0);
	
	unsigned long white = WhitePixel(dpy,DefaultScreen(dpy));
	unsigned long black = BlackPixel(dpy,DefaultScreen(dpy));
	
	
	win = XCreateSimpleWindow(dpy,
							  DefaultRootWindow(dpy),
							  0, 0,
							  size, size,
							  0, black,
							  white);
	
	/* We want to be notified when the window appears */
	XSelectInput(dpy, win, StructureNotifyMask);
	
	/* Make it appear */
	XMapWindow(dpy, win);
	
	while (1) {
		XEvent e;
		XNextEvent(dpy, &e);
		if (e.type == MapNotify) break;
	}
	
	XTextProperty tp;
	char name[128] = "Mandelbrot";
	char *n = name;
	Status st = XStringListToTextProperty(&n, 1, &tp);
	if (st) XSetWMName(dpy, win, &tp);
	
	/* Wait for the MapNotify event */
	XFlush(dpy);
	
	int ii, jj;
	int depth = DefaultDepth(dpy, DefaultScreen(dpy));
	Visual *visual = DefaultVisual(dpy, DefaultScreen(dpy));
	int total;
	
	/* Determine total bytes needed for image */
	ii = 1;
	jj = (depth - 1) >> 2;
	while (jj >>= 1) ii <<= 1;
	
	/* Pad the scanline to a multiple of 4 bytes */
	total = size * ii;
	total = (total + 3) & ~3;
	total *= size;
	bytes_per_pixel = ii;
	
	if (bytes_per_pixel != 4) {
		printf("Need 32bit colour screen!");
		
	}
	
	/* Make bitmap */
	bitmap = XCreateImage(dpy, visual, depth,
						  ZPixmap, 0, malloc(total),
						  size, size, 32, 0);
	
	/* Init GC */
	gc = XCreateGC(dpy, win, 0, NULL);
	XSetForeground(dpy, gc, black);
	
	if (bytes_per_pixel != 4) {
		printf("Need 32bit colour screen!\n");
		exit_x11();
		exit(0);
	}
	
	XSelectInput(dpy, win, ExposureMask | KeyPressMask | StructureNotifyMask);
	
	wmDeleteMessage = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dpy, win, &wmDeleteMessage, 1);
}

void exit_x11(void) {
	XDestroyImage(bitmap);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}


