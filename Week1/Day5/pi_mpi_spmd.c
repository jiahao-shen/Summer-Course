# include <stdio.h>
# include "mpi.h"
double f(double x) {    //函数求解
    return 4 / (1 + x * x);
}
int main(int argc, char** argv) {
    double pi;  //最终结果
    int num_process, process_id;    //进程个数和进程序号
    long long n = 100000000;    //定积分矩阵个数
    double start_time, end_time;    //开始和结束时间

    MPI_Init(&argc, &argv); //初始化
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id); //获取当前进程序号
    MPI_Comm_size(MPI_COMM_WORLD, &num_process);    //获取进程个数

    start_time = MPI_Wtime();   //获取开始时间

    double dx = 1.0 / n;    //求解dx
    double sum = 0.0;   //定积分f(x)之和
    for (int i = process_id + 1; i <= n; i += num_process) {    //每个进程分组处理
        sum += f(dx * (i - 0.5));
    }
    sum *= dx;  //矩形高即f(x)*dx即为矩形的面积
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);   //每个进程的结果规约累加到0进程的pi上

    if (process_id == 0) {
        end_time = MPI_Wtime(); //获取结束时间
        printf("Time:%fs\n", end_time - start_time);
        printf("%0.8f\n", pi);
    }
    MPI_Finalize(); //MPI结束
}