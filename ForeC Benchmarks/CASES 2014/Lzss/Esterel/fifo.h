#ifndef FIFO_H
#define FIFO_H

typedef struct _Fifo {
    char *data;
    unsigned size;
    unsigned written_size;
    int begin;
    int end;
} Fifo;

void Fifo_init(Fifo*, unsigned, char*);

void Fifo_destroy(Fifo*);

int Fifo_push_front(Fifo*, char);

int Fifo_push_back(Fifo*, char);

char Fifo_pop_front(Fifo*);

char Fifo_pop_back(Fifo*);

char Fifo_at(Fifo*, unsigned);

void Fifo_print(Fifo*);

#endif
