#include <stdio.h>
#include <omp.h>

int main() {

    double vec_a[65536], vec_b[65536];
    double scalar = 2.5;
    double seq_time, par_time, speedup;
    double start, end;
    int idx;

    // Setup arrays
    for (idx = 0; idx < 65536; idx++) {
        vec_a[idx] = 1.0;
        vec_b[idx] = 2.0;
    }

    // Run sequential version
    start = omp_get_wtime();
    for (idx = 0; idx < 65536; idx++) {
        vec_a[idx] = scalar * vec_a[idx] + vec_b[idx];
    }
    end = omp_get_wtime();

    seq_time = end - start;
    printf("Sequential Time = %f seconds\n\n", seq_time);

    // Test with different thread counts
    for (int t = 2; t <= 12; t++) {

        // Reset array
        for (idx = 0; idx < 65536; idx++)
            vec_a[idx] = 1.0;

        omp_set_num_threads(t);

        start = omp_get_wtime();

        #pragma omp parallel for
        for (idx = 0; idx < 65536; idx++) {
            vec_a[idx] = scalar * vec_a[idx] + vec_b[idx];
        }

        end = omp_get_wtime();

        par_time = end - start;
        speedup = seq_time / par_time;

        printf("Threads = %d   Time = %f   Speedup = %.2f\n",
               t, par_time, speedup);
    }

    return 0;
}
