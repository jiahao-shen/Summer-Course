#include <stdio.h>
#include "mpi.h"
int main(int argc, char** argv) {

    int task_num, task_id;

    int rt = MPI_Init(&argc, &argv);
    if (rt != MPI_SUCCESS) {
        printf("Error\n");
        MPI_Abort(MPI_COMM_WORLD, rt);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &task_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);

    printf("Hello World! %dth of totalNum = %d\n", task_id, task_num);

    MPI_Finalize();

    return 0;
}
