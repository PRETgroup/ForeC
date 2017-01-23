#include "fs_math.h"

#include "mandelbrot_data.h"

#define DefaultCenterX -0.637011f
#define DefaultCenterY -0.0395159f
#define DefaultScale 0.00403897f
// #define ColormapSize 512
// #define DefaultResultWidth 550
// #define DefaultResultHeight 400
#define ColormapSize 128
#define DefaultResultWidth 220
#define DefaultResultHeight 160

static float centerX;
static float centerY;
static float pixmapScale;
static int problemSize;

static int resultWidth;
static int resultHeight;

static unsigned colormap[ColormapSize];
static int currentColormapPos;
static Pixel image[DefaultResultHeight][DefaultResultWidth];
static int currentX;
static int currentY;

void init(int p)
{
    problemSize = p;
    currentColormapPos = 0;

    centerX = DefaultCenterX;
    centerY = DefaultCenterY;
    pixmapScale = DefaultScale;
    resultWidth = DefaultResultWidth;
    resultHeight = DefaultResultHeight;
    currentX = 0;
    currentY = 0;
}

void nextColormapPos(unsigned char *hasNext, int *pos)
{
    if (*pos < ColormapSize) {
        *hasNext = 1;
        (*pos)++;
    } else
        *hasNext = 0;
}

void initColormap(int pos)
{
    colormap[pos] = rgbFromWaveLength(380.0 + (pos * 400.0 / ColormapSize));
}

void nextPixel(unsigned char *hasNext, int *x, int *y)
{
    for (; currentY < DefaultResultHeight; currentY++) {
        if (currentX < DefaultResultWidth) {
            *x = currentX++;
            *y = currentY;
            *hasNext = 1;
            return;
        }
        currentX = 0;
    }
    *hasNext = 0;
}

void calculate(int x, int y)
{
    int halfWidth = resultWidth / 2;
    int halfHeight = resultHeight / 2;
    int pass = problemSize - 1;
    const int MaxIterations = (1 << (2 * pass + 6)) + 32;
    const int Limit = 4;

    int mod_x = x - halfWidth;
    int mod_y = y - halfHeight;
    float ay = centerY + (mod_y * pixmapScale);
    float ax = centerX + (mod_x * pixmapScale);
    float a1 = ax;
    float b1 = ay;
    int numIterations = 0;

    do {
        ++numIterations;
        float a2 = (a1 * a1) - (b1 * b1) + ax;
        float b2 = (2 * a1 * b1) + ay;
        if ((a2 * a2) + (b2 * b2) > Limit)
            break;
        ++numIterations;
        a1 = (a2 * a2) - (b2 * b2) + ax;
        b1 = (2 * a2 * b2) + ay;
        if ((a1 * a1) + (b1 * b1) > Limit)
            break;
    } while (numIterations < MaxIterations);

    if (numIterations < MaxIterations)
        image[y][x] = uintToRgb(colormap[numIterations % ColormapSize]);
    else
        image[y][x] = uintToRgb(0);
}


unsigned rgbFromWaveLength(float wave)
{
    unsigned char rr;
    unsigned char gg;
    unsigned char bb;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    if (wave >= 380.0 && wave <= 440.0) {
        r = -1.0 * (wave - 440.0) / (440.0 - 380.0);
        b = 1.0;
    } else if (wave >= 440.0 && wave <= 490.0) {
        g = (wave - 440.0) / (490.0 - 440.0);
        b = 1.0;
    } else if (wave >= 490.0 && wave <= 510.0) {
        g = 1.0;
        b = -1.0 * (wave - 510.0) / (510.0 - 490.0);
    } else if (wave >= 510.0 && wave <= 580.0) {
        r = (wave - 510.0) / (580.0 - 510.0);
        g = 1.0;
    } else if (wave >= 580.0 && wave <= 645.0) {
        r = 1.0;
        g = -1.0 * (wave - 645.0) / (645.0 - 580.0);
    } else if (wave >= 645.0 && wave <= 780.0) {
        r = 1.0;
    }

    float s = 1.0;
    if (wave > 700.0)
        s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);
    else if (wave <  420.0)
        s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);

    r = fs_pow(r * s, 0.8);
    g = fs_pow(g * s, 0.8);
    b = fs_pow(b * s, 0.8);
    rr = (r * 255);
    gg = (g * 255);
    bb = (b * 255);

    return 0xFF000000 + (rr << 16) + (gg << 8) + bb;
}

Pixel uintToRgb(unsigned rgb)
{
    Pixel p = {0, 0, 0};
    if (rgb != 0) {
        p.r = (rgb & 0x00FF0000) >> 16;
        p.g = (rgb & 0x0000FF00) >> 8;
        p.b = (rgb & 0x000000FF);
    }
    return p;
}
