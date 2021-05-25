#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *calculatePi(void *threadIdPtr);

const int THREADS = 4;
const int RANGE = 1000000000;
const int SUBRANGE = RANGE/THREADS;

int main(int argc, char **argv) {
    pthread_t cores[4];
    pthread_attr_t thread0, thread1, thread2, thread3;
    
    pthread_attr_init(&thread0);
    pthread_attr_init(&thread1);
    pthread_attr_init(&thread2);
    pthread_attr_init(&thread3);
    pthread_attr_setdetachstate(&thread0, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&thread1, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&thread2, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&thread3, PTHREAD_CREATE_JOINABLE);

    struct timeval startTime, endTime;
    gettimeofday(&startTime, 0);
    //- - - -

    long double pi = 0;
    pthread_create(&cores[0], NULL, calculatePi, (void *)0);
    pthread_create(&cores[1], NULL, calculatePi, (void *)1);
    pthread_create(&cores[2], NULL, calculatePi, (void *)2);
    pthread_create(&cores[3], NULL, calculatePi, (void *)3);
    
    long double pi0, pi1, pi2, pi3;
    pthread_join(cores[0], (void *)&pi0);
    pthread_join(cores[1], (void *)&pi1);
    pthread_join(cores[2], (void *)&pi2);
    pthread_join(cores[3], (void *)&pi3);

    //- - - -
    gettimeofday(&endTime, 0);
    long seconds = endTime.tv_sec - startTime.tv_sec;
    int microseconds = endTime.tv_usec - startTime.tv_usec;
    if (microseconds < 0) {
        microseconds += 1000000;
        seconds--;
    }
    printf("Runtime: %ld.%.6d seconds\r\n", seconds, microseconds);
    
    printf("Approximation of pi: %.21Lg\r\n", pi);

    return 0;
}

void *calculatePi(void *threadIdPtr) {
    long threadId = (long)threadIdPtr;
    long double result = 0.0;
    long double denominator = 0.0;
    long double numerator = -1;
    
    const int startIndex = SUBRANGE*threadId;
    const int endIndex = SUBRANGE*(threadId + 1);
    
    for (int i = startIndex; i < endIndex; ++i) {
        numerator = numerator * -1;
        denominator = 2*i + 1;
        result += 4*(numerator/denominator);
    }

    long double *resultPtr = malloc(sizeof(result));
    *resultPtr = result;
    return (void *)resultPtr;
}
