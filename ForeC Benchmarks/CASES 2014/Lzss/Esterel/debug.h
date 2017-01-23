#ifndef DEBUG_H
#define DEBUG_H

#ifndef DEBUG

#include <stdio.h>

#  define debug(...)
#  define debug_add_trace_0(...)
#  define debug_add_trace_1(...)
#  define debug_print_trace(...)
#  define debug_clear_trace(...)

#else // DEBUG

#define printff(...) \
do { \
    xil_printf(__VA_ARGS__); \
    fflush(stdout); \
} while (0);

#define debug printff

#define DEBUG_ARRAY_ADDR_0 0x8F000000;
#define DEBUG_ARRAY_ADDR_1 0x8FF00000;

int *debug_array_0 = (int*) DEBUG_ARRAY_ADDR_0;
int debug_array_i_0;
int *debug_array_1 = (int*) DEBUG_ARRAY_ADDR_1;
int debug_array_i_1;
int printed = 0;

void debug_add_trace_0(int line)
{
    debug_array_0[(debug_array_i_0)++] = line;
}

void debug_add_trace_1(int line)
{
    debug_array_1[(debug_array_i_1)++] = line;
}

void debug_clear_trace()
{
    debug_array_i_0 = 0;
    debug_array_i_1 = 0;
    printed = 0;
}

void debug_print_trace()
{
    int i;
    xil_printf("CPU 0: trace (%d):\n", debug_array_i_0);
    for (i = 0; i < debug_array_i_0; i++) {
        xil_printf("%d ", debug_array_0[i]);
    }
    print("\n");
    xil_printf("CPU 1: trace (%d):\n", debug_array_i_1);
    for (i= 0; i < debug_array_i_1; i++) {
        xil_printf("%d ", debug_array_1[i]);
    }
    print("\n");
    printed++;
    if (printed > 5) while (1);
}

#endif // DEBUG
#endif
