#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 4
double f(double x) {
    return 4.0 / (1 + x * x);
}
void main() {
    long long n = 100000000;
    double dx = 1.0 / n;
    double pi = 0.0;
    double sum[NUM_THREADS];
    double start_time, end_time;

    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        sum[id] = 0;
        #pragma omp for //for循环制导
        for (int i = 1; i <= n; ++i) {
            sum[id] += f((i - 0.5) * dx);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++)
        pi += sum[i] * dx;
    end_time = omp_get_wtime();
    printf("Time:%fs\n", end_time - start_time);
    printf("%0.8f\n", pi);
}
