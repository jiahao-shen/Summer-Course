#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 4   //线程个数
double f(double x) {
    return 4 / (1 + x * x);
}
int main(int argc, char** argv) {
    double pi, sum[NUM_THREADS];    //数组存放每个线程的结果
    long long n = 100000000;
    double dx = 1.0 / n;
    double start_time, end_time;

    omp_set_num_threads(NUM_THREADS);   //线程初始化
    start_time = omp_get_wtime();
    #pragma omp parallel    //并行域
    {
        int id = omp_get_thread_num();  //获取当前线程序号
        sum[id] = 0;    //置对应的sum为0
        for (int i = id; i <= n; i += NUM_THREADS) {   
            sum[id] += f((i - 0.5) * dx);   //对每个线程负责的矩形进行分组求和并存放在数组中
        }
    }
    //串行域
    for (int i = 0; i < NUM_THREADS; ++i) { //将每个线程的sum累加
        pi += sum[i] * dx;
    }
    end_time = omp_get_wtime();
    printf("Time:%fs\n", end_time - start_time);
    printf("%0.8f\n", pi);
}