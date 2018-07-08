# Day5

* 使用SPMD编程模式编写求解pi的MPI程序
* 编写求解pi的OpenMP程序
    * 并行域求解
    * for循环制导求解
    * 带reduction子句的for循环制导
    * private子句和critical子句制导
* 使用MPI+OpenMP求解pi
    * 由于macOS中mpich默认使用的是clang进行编译
    * 然而clang并不支持OpenMP
    * 因此在MPI+OpenMP混合编写时要手动指定使用gcc进行编译

    `mpicc -cc=gcc-8 -fopenmp -o pi_mpi_openmp pi_mpi_openmp.c`
