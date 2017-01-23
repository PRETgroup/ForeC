#include "file.h"

int mgetc(char **stream)
{
    char *c = *stream++;
    return *c;
}

int mputc(char c, char **stream)
{
    **stream = c;
    stream++;
    return c;
}

size_t mwrite(const void *ptr, size_t size, size_t nmemb, char **stream)
{
    int n, s, ret = 0;

    for (n = 0; n < nmemb; n++) {
        for (s = 0; s < size; s++) {
            **stream = *((char*) ptr);
            stream++;
            ret++;
        }
    }

    return ret;
}
