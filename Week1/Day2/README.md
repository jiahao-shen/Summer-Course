# Day2

* 搭建MPICH
* 使用MPI运行Hello World

## Mac

1. brew install mpich
2. mpicc -o hello_world hello_world.c
3. mpirun -np 6 ./hello_world

## Ubuntu

1. apt install mpich
2. mpicc -o hello_world hello_world.c
3. mpirun -np 6 ./hello_world

## Centos

1. yum install mpich
2. mpicc -o hello_world hello_world.c
3. mpirun -np 6 ./hello_world