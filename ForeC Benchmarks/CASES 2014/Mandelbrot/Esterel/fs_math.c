/* BEGIN fs_math.c */

#include "fs_math.h"

#include <float.h>
/* 
** pi == (atan(1.0 / 3) + atan(1.0 / 2)) * 4
*/
static float fs_pi(void);

float fs_sqrt(float x)
{
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

float fs_log(float x)
{
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

float fs_log10(float x)
{
    static float log_10;
    static int initialized;
    
    if (!initialized) {
        initialized = 1;
        log_10 = fs_log(10);
    }
    return x > 0 && FLT_MAX >= x ? fs_log(x) / log_10 : fs_log(x);
}

float fs_exp(float x)
{
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

float fs_modf(float value, float *iptr) 
{
    float a, b;
    const float c = value;

    if (0 > c) {
        value = -value;
    }
    if (FLT_MAX >= value) {
        for (*iptr = 0; value >= 1; value -= b) {
            a = value / 2;
            b = 1;
            while (a >= b) {
                b *= 2;
            }
            *iptr += b;
        }
    } else {
        *iptr = value;
        value = 0;
    }
    if (0 > c) {
        *iptr = -*iptr;
        value = -value;
    }
    return value;
}

float fs_fmod(float x, float y) 
{
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

float fs_pow(float x, float y)
{
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

static float fs_pi(void)
{
    unsigned n;
    float a, b, epsilon;
    static float p;
    static int initialized;

    if (!initialized) {
        initialized = 1;
        epsilon = FLT_EPSILON / 4;
        n = 1;
        a = 3;
        do {
            a /= 9;
            b  = a / n;
            n += 2;
            a /= 9;
            b -= a / n;
            n += 2;
            p += b;
        } while (b > epsilon);
        epsilon = FLT_EPSILON / 2;
        n = 1;
        a = 2;
        do {
            a /= 4;
            b  = a / n;
            n += 2;
            a /= 4;
            b -= a / n;
            n += 2;
            p += b;
        } while (b > epsilon);
        p *= 4;
    }
    return p;
}

float fs_cos(float x) 
{
    unsigned n;
    int negative, sine;
    float a, b, c;
    static float pi, two_pi, half_pi, third_pi, epsilon;
    static int initialized;
    
    if (0 > x) {
        x = -x;
    }
    if (FLT_MAX >= x) {
        if (!initialized) {
            initialized = 1;
            pi          = fs_pi();
            two_pi      = 2 * pi;
            half_pi     = pi / 2;
            third_pi    = pi / 3;
            epsilon     = FLT_EPSILON / 2;
        }
        if (x > two_pi) {
            x = fs_fmod(x, two_pi);
        }
        if (x > pi) {
            x = two_pi - x;
        }
        if (x > half_pi) {
            x = pi - x;
            negative = 1;
        } else {
            negative = 0;
        }
        if (x > third_pi) {
            x = half_pi - x;
            sine = 1;
        } else {
            sine = 0;
        }
        c = x * x;
        x = n = 0;
        a = 1;
        do {
            b  = a;
            a *= c;
            a /= ++n;
            a /= ++n;
            b -= a;
            a *= c;
            a /= ++n;
            a /= ++n;
            x += b;
        } while (b > epsilon);
        if (sine) {
            x = fs_sqrt((1 - x) * (1 + x));
        }
        if (negative) {
            x = -x;
        }
    } else {
        x = -FLT_MAX;
    }
    return x;
}

float fs_log2(float x)
{
    static float log_2;
    static int initialized;
    
    if (!initialized) {
        initialized = 1;
        log_2 = fs_log(2);
    }
    return x > 0 && FLT_MAX >= x ? fs_log(x) / log_2 : fs_log(x);
}

float fs_exp2(float x)
{
    static float log_2;
    static int initialized;

    if (!initialized) {
        initialized = 1;
        log_2 = fs_log(2);
    }
    return fs_exp(x * log_2);
}

/* END fs_math.c */

