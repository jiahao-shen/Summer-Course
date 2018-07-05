# Day2

* 搭建MPICH
* 使用MPI运行Hello World

1. brew install mpich
2. mpicc -o hello_world hello_world.c
3. mpirun -np 6 ./hello_world