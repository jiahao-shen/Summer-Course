#include <stdio.h>
#include <omp.h>
#include "mpi.h"
#define NUM_THREADS 4
double f(double x) {
    return 4 / (1 + x * x);
}
int main(int argc, char** argv) {
    double pi;
    int num_process, process_id;
    long long n = 100000000;
    double start_time, end_time;
    double dx = 1.0 / n;

    //MPI初始化
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_process);
    //OpenMP初始化
    omp_set_num_threads(NUM_THREADS);

    start_time = MPI_Wtime();

    double sum = 0.0;
    //对于每个线程,使用OpenMP的reduction进行规约求和
    #pragma omp parallel for reduction(+: sum)  
    for (int i = process_id + 1; i <= n; i += num_process) {
        sum += f(dx * (i - 0.5));
    }
    sum *= dx;
    //对于每个进程的sum值,使用MPI的reduction进行规约累加到变量pi上
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (process_id == 0) {
        end_time = MPI_Wtime();
		printf("Time:%fs\n", end_time - start_time);
        printf("%0.8f\n", pi);
    }
    MPI_Finalize();   
}   
