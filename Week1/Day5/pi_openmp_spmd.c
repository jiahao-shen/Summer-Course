#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 4
double f(double x) {
    return 4 / (1 + x * x);
}
int main(int argc, char** argv) {
    double pi, sum[NUM_THREADS];
    long long n = 100000000;
    double dx = 1.0 / n;
    double start_time, end_time;

    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel 
    {
        int id = omp_get_thread_num();
        sum[id] = 0;
        for (int i = id; i <= n; i += NUM_THREADS) {
            sum[id] += f((i - 0.5) * dx);
        }
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pi += sum[i] * dx;
    }
    end_time = omp_get_wtime();
    printf("Time:%fs\n", end_time - start_time);
    printf("%0.8f\n", pi);
}