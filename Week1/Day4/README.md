# Day4

* 练习使用OpenMP实现Hello World
    1. gcc-8 -fopenmp -o hello_world hello_world.c
    2. export OMP_NUM_THREADS=4
    3. ./hello_world

* 使用OpenMP求解pi
    1. gcc-8 -fopenmp -o solve_pi solve_pi.c
    2. ./solve_pi