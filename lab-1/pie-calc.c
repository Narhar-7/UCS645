#include <stdio.h>
#include <omp.h>
int main() {
    long total_steps = 10000;
    double interval;
    int idx, t;
    double pos, pi_value, total;
    double start, end, base_time;
    interval = 1.0 / (double) total_steps;
    total = 0.0;
    start = omp_get_wtime();
    for (idx = 0; idx < total_steps; idx++) {
        pos = (idx + 0.5) * interval;
        total = total + 4.0 / (1.0 + pos * pos);
    }
    pi_value = interval * total;
    end = omp_get_wtime();
    base_time = end - start;
    printf("Sequential Execution:\n");
    printf("Pi value = %.10f\n", pi_value);
    printf("Execution Time = %f\n", base_time);
    printf("\nParallel Execution:\n");
    for (t = 2; t <= 10; t++) {
        omp_set_num_threads(t);
        total = 0.0;
        start = omp_get_wtime();
        #pragma omp parallel for private(pos) reduction(+:total)
        for (idx = 0; idx < total_steps; idx++) {
            pos = (idx + 0.5) * interval;
            total = total + 4.0 / (1.0 + pos * pos);
        }
        pi_value = interval * total;
        end = omp_get_wtime();
        double exec_time = end - start;
        printf("Threads=%d  Pi=%.10f  Time=%f  Speedup=%.2f\n",
               t, pi_value, exec_time, base_time / exec_time);
    }
    return 0;
}
