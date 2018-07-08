# Day2

* 搭建MPICH
* 使用MPI运行Hello World

```bash
brew install mpich
mpicc -o hello_world hello_world.c
mpirun -np 6 ./hello_world
```