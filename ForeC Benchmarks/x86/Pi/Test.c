#include <omp.h>
#include <stdio.h>

int main(int argc, char **argv) {
    
    #pragma omp parallel
    {
        #pragma omp single
        printf("%d threads in parallel\n", omp_get_num_threads());

        printf("  Hello from thread %d\n", omp_get_thread_num());
        printf("    Goodbye from thread %d\n", omp_get_thread_num());
    }

    printf("\n");
    
    #pragma omp parallel num_threads(2)
    {
        #pragma omp single
        printf("%d threads in section\n", omp_get_num_threads());
        
        #pragma omp sections
        {
            #pragma omp section
            printf("  Greetings from section A by thread %d\n", omp_get_thread_num());

            #pragma omp section
            printf("  Greetings from section B by thread %d\n", omp_get_thread_num());

            #pragma omp section
            printf("  Greetings from section C by thread %d\n", omp_get_thread_num());
        }
    }
    
    printf("\n");
    
    int sum = 0;
    #pragma omp parallel default(none) shared(sum)
    {
        #pragma omp single
        printf("%d threads in for-loop\n", omp_get_num_threads());

        int iterationCount = 0;
        
        #pragma omp for schedule(runtime)
        for (int i = 0; i < 100; i++) {
            #pragma omp cancellation point for

            #pragma omp atomic update
            sum++;

            iterationCount++;
            #pragma omp cancel for
        }
        
        printf("  Thread %d executed %d iterations\n", omp_get_thread_num(), iterationCount);
    }
    printf("Sum: %d\n", sum);
    
    printf("\n");

    printf("Reduction\n");
    int result = 10;
    #pragma omp parallel for ordered reduction(+: result)
    for (int i = 0; i < 15; i++) {
        result++;
        
        #pragma omp ordered
        printf("  %d\n", i);
    }
    printf("Result: %d\n", result);

    return 0;
}
