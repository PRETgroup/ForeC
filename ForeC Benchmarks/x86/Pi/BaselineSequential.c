#include <sys/time.h>
#include <stdio.h>

long double calculatePi(const int range, int threadId);

int main(int argc, char **argv) {
    const int THREADS = 4;
    
    struct timeval startTime, endTime;
    gettimeofday(&startTime, 0);
    //- - - -
    
    const int RANGE = 1000000000;
    const int SUBRANGE = RANGE/THREADS;
    
    long double pi = 0;
    pi += calculatePi(SUBRANGE, 0);
    pi += calculatePi(SUBRANGE, 1);
    pi += calculatePi(SUBRANGE, 2);
    pi += calculatePi(SUBRANGE, 3);
    
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

long double calculatePi(const int range, int threadId) {
    long double result = 0.0;
    long double denominator = 0.0;
    long double numerator = -1;
    
    const int startIndex = range*threadId;
    const int endIndex = range*(threadId + 1);
    
    for (int i = startIndex; i < endIndex; ++i) {
        numerator = numerator * -1;
        denominator = 2*i + 1;
        result += 4*(numerator/denominator);
    }
    
    return result;
}
