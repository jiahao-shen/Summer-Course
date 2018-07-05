#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 2
static long num_steps = 100000;
double step;
int main(int argc, char** argv) {
    double pi = 0.0;
    double sum = 0.0;
    double x = 0.0;
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for reduction(+: sum) private(x)
    for (int i = 1; i <= num_steps; ++i) {
        x = (i - 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi = sum * step;
    printf("%lf", pi);
}