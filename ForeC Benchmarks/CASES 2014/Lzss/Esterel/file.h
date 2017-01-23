#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

int mgetc(char **stream);
int mputc(char c, char **stream);
size_t mwrite(const void *ptr, size_t size, size_t nmemb, char **stream);

#endif
