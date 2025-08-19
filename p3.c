#include <stdio.h>
#include <omp.h>

int fib(int n) {
    if (n < 2) {
        return n;
    } else {
        int i, j;

        #pragma omp task shared(i) firstprivate(n)
        i = fib(n - 1);

        #pragma omp task shared(j) firstprivate(n)
        j = fib(n - 2);

        #pragma omp taskwait
        return i + j;
    }
}

int main() {
    int n;
    printf("Enter the Fibonacci number to calculate: ");
    scanf("%d", &n);

    omp_set_dynamic(0);
    omp_set_num_threads(4);

    int result;
    double t0 = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    double t1 = omp_get_wtime();

    printf("fib(%d) = %d\n", n, result);
    printf("time = %f sec\n", t1 - t0);

    return 0;
}
