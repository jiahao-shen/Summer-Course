# include <stdio.h>
# include "mpi.h"
double f(double x) {
    return 4 / (1 + x * x);
}
int main(int argc, char** argv) {
    double pi;
    int num_process, my_id;
    long long n = 100000000;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_process);

    start_time = MPI_Wtime();

    double dx = 1.0 / n;
    double sum = 0.0;
    for (int i = my_id + 1; i <= n; i += num_process) {
        sum += f(dx * (i - 0.5));
    }
    sum *= dx;
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_id == 0) {
        end_time = MPI_Wtime();
        printf("Time:%fs\n", end_time - start_time);
        printf("%0.8f\n", pi);
    }
    MPI_Finalize();
}