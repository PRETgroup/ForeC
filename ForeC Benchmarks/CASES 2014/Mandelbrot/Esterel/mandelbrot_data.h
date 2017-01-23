#ifndef MANDELBROT_DATA_H
#define MANDELBROT_DATA_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

void init(int p);
void nextColormapPos(unsigned char *hasNext, int *pos);
void initColormap(int pos);
void nextPixel(unsigned char *hasNext, int *x, int *y);
void calculate(int x, int y);
unsigned rgbFromWaveLength(float wave);
Pixel uintToRgb(unsigned rgb);

#endif
