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
    #pragma omp parallel private(sum)   //sum作为private只能在并行域中进行操作
    {
        int id = omp_get_thread_num();
        sum = 0.0;
        //求解每个线程的sum
        for (int i = id + 1; i <= n; i += NUM_THREADS) {
            sum += f((i - 0.5) * dx);
        }
        #pragma omp critical    //critical制导
        {
            pi += sum * dx; //将每次的结果累加到pi上
        }
    }
    end_time = omp_get_wtime();
    printf("Time:%fs\n", end_time - start_time);
    printf("%0.8f\n", pi);
}