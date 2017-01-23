#include "fifo.h"
// #include <stdlib.h>
// #include <stdio.h>

void Fifo_init(Fifo *fifo, unsigned size, char *buf) {
    fifo->begin = 0;
    fifo->end = 0;
    fifo->size = size;
    fifo->written_size = 0;
    fifo->data = buf;

//     if (!fifo->data) {
//         fputs("Fifo: out of memory\n", stderr);
//         exit(1);
//     }
}

void Fifo_destroy(Fifo *fifo) {
//     free(fifo->data);
}

int Fifo_push_front(Fifo *fifo, char c) {
    if (fifo->written_size == 0)
        Fifo_push_back(fifo, c);
    else if (fifo->written_size >= fifo->size)
        return -1;

    fifo->begin--;
    if (fifo->begin < 0)
        fifo->begin = fifo->size - 1;
    fifo->data[fifo->begin] = c;
    fifo->written_size++;
    
    return 0;
}

int Fifo_push_back(Fifo *fifo, char c) {
    if (fifo->written_size >= fifo->size)
        return -1;

    fifo->written_size++;
    fifo->data[fifo->end] = c;
    fifo->end++;
    if (fifo->end == fifo->size)
        fifo->end = 0;
        
    return 0;
}

char Fifo_pop_front(Fifo *fifo) {
    if (fifo->written_size == 0)
        return -1;

    char c = fifo->data[fifo->begin];
    fifo->written_size--;
    fifo->begin++;
    if (fifo->begin == fifo->size)
        fifo->begin = 0;
    return c;
}

char Fifo_pop_back(Fifo *fifo) {
    if (fifo->written_size == 0)
        return -1;

    fifo->written_size--;
    fifo->end--;
    if (fifo->end < 0)
        fifo->end = fifo->size - 1;
    return fifo->data[fifo->end];
}

char Fifo_at(Fifo *fifo, unsigned i) {
    if (i < fifo->written_size) {
        return fifo->data[(fifo->begin + i) % fifo->size];
    } else {
        return -1;
    }
}

void Fifo_print(Fifo *fifo) {
    int i, j;
    for (i = fifo->begin, j = 0; j < fifo->written_size; i++, j++) {
        if (i == fifo->size)
            i = 0;
//         putchar(fifo->data[i]);
    }
}
