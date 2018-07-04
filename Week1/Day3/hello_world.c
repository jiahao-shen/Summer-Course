#include <stdio.h>
#include "mpi.h"
int main(int argc, char** argv) {
    int my_id, num_process;
    int name_len;
    char process_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_process);
    MPI_Get_processor_name(process_name, &name_len);
    printf("Hello Wolrd! Process %d of %d on %s\n", my_id, num_process, process_name);
    MPI_Finalize();
}