#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 4
double f(double x) {
    return 4.0 / (1 + x * x);
}
void main() {
    long long n = 100000000;
    double dx = 1.0 / n;
    double sum, pi = 0.0;
    double start_time, end_time;

    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel private(sum)
    {
        int id = omp_get_thread_num();
        sum = 0.0;
        for (int i = id + 1; i <= n; i += NUM_THREADS) {
            sum += f((i - 0.5) * dx);
        }
        #pragma omp critical
        {
            pi += sum * dx;
        }
    }
    end_time = omp_get_wtime();
    printf("Time:%fs\n", end_time - start_time);
    printf("%0.8f\n", pi);
}