// http://qt-project.org/doc/qt-4.8/threads-mandelbrot.html

// Hardware counter connected via a direct FSL bus.
#include "counter_dfsl.h"
Counter counter;
#define FSL_COUNTER_ID			2

#include <stdio.h>
#include <float.h>

const int ColormapSize = 128;
const int problemSize = 10;
const float centerX = -0.637011f;
const float centerY = -0.0395159f;
const float pixmapScale = 0.00403897f;
const int resultWidth = 220;
const int resultHeight = 160;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

unsigned colormap[128];
Pixel image[160][220];

void compute(void);
void init(void);
void calculate(int x, int y);
unsigned rgbFromWaveLength(float wave);
Pixel uintToRgb(unsigned rgb);

float fs_pow(float x, float y);
float fs_fmod(float x, float y);
float fs_exp(float x);
float fs_log(float x);
float fs_sqrt(float x);

int main(int argc, char **argv) {
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	counterStart(counter, FSL_COUNTER_ID);
	
	init();
	compute();

	// Stop counting the elapsed cycles for the current reaction.
	counterStop(FSL_COUNTER_ID);
	counterRead(counter, FSL_COUNTER_ID);
	counterDifference(counter);
	counterMaximum(counter);
	counterMinimum(counter);
	counterAccumulate(counter);
	counterAverage(counter);
	xil_printf("Total time: %d cycles\r\n", counter.total);
	xil_printf("Program termination\r\n");
	
	asm volatile (".long 0x80000001\r\n");
	return 0;
}

void compute(void) {
	int y;
	for (y = 0; y < resultHeight; ++y) {
		int x;
        for (x = 0; x < resultWidth; ++x) {
			calculate(x, 0);		// Bug in the compiled Esterel code where "y" isn't emitted.
		}
	}
}

void init(void) {
	int i;
	for (i = 0; i < ColormapSize; ++i) {
    	colormap[i] = rgbFromWaveLength(380.0 + (i * 400.0 / ColormapSize));
    }
}

void calculate(int x, int y) {
    const int halfWidth = resultWidth / 2;
    const int halfHeight = resultHeight / 2;
    const int pass = problemSize - 1;
    const int MaxIterations = (1 << (2 * pass + 6)) + 32;
    const int Limit = 4;

    const int mod_x = x - halfWidth;
    const int mod_y = y - halfHeight;
    const float ay = centerY + (mod_y * pixmapScale);
    const float ax = centerX + (mod_x * pixmapScale);
    float a1 = ax;
    float b1 = ay;
    int numIterations = 0;

    do {
        ++numIterations;
        float a2 = (a1 * a1) - (b1 * b1) + ax;
        float b2 = (2 * a1 * b1) + ay;
        if ((a2 * a2) + (b2 * b2) > Limit) {
            break;
        }
        ++numIterations;
        a1 = (a2 * a2) - (b2 * b2) + ax;
        b1 = (2 * a2 * b2) + ay;
        if ((a1 * a1) + (b1 * b1) > Limit) {
            break;
        }
    } while (numIterations < MaxIterations);

    if (numIterations < MaxIterations) {
        image[y][x] = uintToRgb(colormap[numIterations % ColormapSize]);
    } else {
        image[y][x] = uintToRgb(0);
    }
}

unsigned rgbFromWaveLength(float wave) {
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
    if (wave > 700.0) {
        s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);
    } else if (wave <  420.0) {
        s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);
    }

    r = fs_pow(r * s, 0.8);
    g = fs_pow(g * s, 0.8);
    b = fs_pow(b * s, 0.8);
    rr = (r * 255);
    gg = (g * 255);
    bb = (b * 255);

    return 0xFF000000 + (rr << 16) + (gg << 8) + bb;
}

Pixel uintToRgb(unsigned rgb) {
    Pixel p = {0, 0, 0};
    if (rgb != 0) {
        p.r = (rgb & 0x00FF0000) >> 16;
        p.g = (rgb & 0x0000FF00) >> 8;
        p.b = (rgb & 0x000000FF);
    }
    return p;
}

float fs_pow(float x, float y) {
    float p = 0;

    if (0 > x && fs_fmod(y, 1) == 0) {
        if (fs_fmod(y, 2) == 0) {
            p =  fs_exp(fs_log(-x) * y);
        } else {
            p = -fs_exp(fs_log(-x) * y);
        }
    } else {
        if (x != 0 || 0 >= y) {
            p =  fs_exp(fs_log( x) * y);
        }
    }
    return p;
}

float fs_fmod(float x, float y) {
    float a, b;
    const float c = x;

    if (0 > c) {
        x = -x;
    }
    if (0 > y) {
        y = -y;
    }
    if (y != 0 && FLT_MAX >= y && FLT_MAX >= x) {
        while (x >= y) {
            a = x / 2;
            b = y;
            while (a >= b) {
                b *= 2;
            }
            x -= b;
        }
    } else {
        x = 0;
    }
    return 0 > c ? -x : x;
}

float fs_exp(float x) {
    unsigned n, square; 
    float b, e;
    static float x_max, x_min, epsilon;
    static int initialized;

    if (!initialized) {
        initialized = 1;
        x_max = fs_log(FLT_MAX);
        x_min = fs_log(FLT_MIN);
        epsilon = FLT_EPSILON / 4;
    }
    if (x_max >= x && x >= x_min) {
        for (square = 0; x > 1; x /= 2) {
            ++square;
        }
        while (-1 > x) {
            ++square;
            x /= 2;
        }
        e = b = n = 1;
        do {
            b /= n++;
            b *= x;
            e += b;
            b /= n++;
            b *= x;
            e += b;
        } while (b > epsilon);
        while (square-- != 0) {
            e *= e;
        }
    } else {
        e = x > 0 ? FLT_MAX : 0;
    }
    return e;
}

float fs_log(float x) {
    int n;
    float a, b, c, epsilon;
    static float A, B, C;
    static int initialized;
    
    if (x > 0 && FLT_MAX >= x) {
        if (!initialized) {
            initialized = 1;
            A = fs_sqrt(2);
            B = A / 2;             
            C = fs_log(A);
        }
        for (n = 0; x > A; x /= 2) {
            ++n;
        }
        while (B > x) {
            --n;
            x *= 2;
        }
        a = (x - 1) / (x + 1);
        x = C * n + a;
        c = a * a;
        n = 1;
        epsilon = FLT_EPSILON * x;
        if (0 > a) {
            if (epsilon > 0) {
                epsilon = -epsilon;
            }
            do {
                n += 2;
                a *= c;
                b = a / n;
                x += b;
            } while (epsilon > b);
        } else {
            if (0 > epsilon) {
                epsilon = -epsilon;
            }
            do {
                n += 2;
                a *= c;
                b = a / n;
                x += b;
            } while (b > epsilon);
        }
        x *= 2;
    } else {
        x = -FLT_MAX;
    }
    return x;
}

float fs_sqrt(float x) {
    int n;
    float a, b;
    
    if (x > 0 && FLT_MAX >= x) {
        for (n = 0; x > 2; x /= 4) {
            ++n;
        }
        while (0.5 > x) {
            --n;
            x *= 4;
        }
        a = x;
        b = (1 + x) / 2;
        do {
            x = b;
            b = (a / x + x) / 2;
        } while (x > b);
        while (n > 0) {
            x *= 2;
            --n;
        }
        while (0 > n) {
            x /= 2;
            ++n;        
        }
    } else {
        if (x != 0) {
            x = FLT_MAX;
        }
    }
    return x;
}

