# Day4

* 练习使用OpenMP实现Hello World

```bash
gcc-8 -fopenmp -o hello_world hello_world.c
export OMP_NUM_THREADS=4
./hello_world
```

* 使用OpenMP求解pi

```bash
gcc-8 -fopenmp -o solve_pi solve_pi.c
./solve_pi
```