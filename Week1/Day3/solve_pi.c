#include <stdio.h>
#include "mpi.h"
double f(double x) {
    return 4 / (1 + x * x);
}
int main(int argc, char** argv) {
    double pi, dx, sum, x, start_time, end_time; 
    int num_process, my_id;
    long long n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_process);

    n = 0;
    if (my_id == 0) {
        printf("Please enter n:");
        scanf("%lld", &n);
        start_time = MPI_Wtime();
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    dx = 1.0 / (double) n;
    sum = 0.0;
    for (int i = my_id + 1; i <= n; i+= num_process) {
        x = dx * ((double) i - 0.5);
        sum += f(x);
    }
    sum *= dx;
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (my_id == 0) {
        end_time = MPI_Wtime();
        printf("Time:%f\n", end_time - start_time);
        printf("%0.15f\n", pi);
    }
}