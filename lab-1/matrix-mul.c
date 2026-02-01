#include <stdio.h>
#include <omp.h>

double mat1[100][100], mat2[100][100], result[100][100];

void reset_result(int size)
{
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            result[row][col] = 0.0;
}

int main()
{
    int size = 100;
    int row, col, idx;
    double start, end, base_time;

    // Initialize matrices
    for (row = 0; row < size; row++)
    {
        for (col = 0; col < size; col++)
        {
            mat1[row][col] = 1.0;
            mat2[row][col] = 2.0;
        }
    }

    reset_result(size);

    // Sequential version
    printf("Sequential:\n");
    start = omp_get_wtime();

    for (row = 0; row < size; row++)
        for (col = 0; col < size; col++)
            for (idx = 0; idx < size; idx++)
                result[row][col] += mat1[row][idx] * mat2[idx][col];

    end = omp_get_wtime();
    base_time = end - start;

    printf("Execution Time = %f seconds\n", base_time);

    // Outer loop parallelization
    printf("\nOuter Loop Parallelization:\n");
    for (int t = 2; t <= 10; t++)
    {
        reset_result(size);
        omp_set_num_threads(t);

        start = omp_get_wtime();

        #pragma omp parallel for private(col, idx)
        for (row = 0; row < size; row++)
            for (col = 0; col < size; col++)
                for (idx = 0; idx < size; idx++)
                    result[row][col] += mat1[row][idx] * mat2[idx][col];

        end = omp_get_wtime();

        double exec_time = end - start;

        printf("Threads=%d  Time=%f  Speedup=%.2f\n",
               t, exec_time, base_time / exec_time);
    }

    // Two loop parallelization
    printf("\nTwo Loop Parallelization:\n");
    for (int t = 2; t <= 10; t++)
    {
        reset_result(size);
        omp_set_num_threads(t);

        start = omp_get_wtime();

        #pragma omp parallel for collapse(2) private(idx)
        for (row = 0; row < size; row++)
            for (col = 0; col < size; col++)
                for (idx = 0; idx < size; idx++)
                    result[row][col] += mat1[row][idx] * mat2[idx][col];

        end = omp_get_wtime();

        double exec_time = end - start;

        printf("Threads=%d  Time=%f  Speedup=%.2f\n",
               t, exec_time, base_time / exec_time);
    }

    return 0;
}
