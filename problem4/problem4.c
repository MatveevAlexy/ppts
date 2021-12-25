#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {
    N = 4096
};

int main(int argc, char **argv)
{
    FILE *f_a = fopen(argv[1], "r"), *f_b = fopen(argv[2], "r");
    int *c = calloc(sizeof(*c), N), *c_ans = calloc(sizeof(*c_ans), N), *b = calloc(sizeof(*b), N);
    fread(b, sizeof(*b), N, f_b);
    fclose(f_b);
    int p, rank;
    double starttime, endtime;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    if (rank == 0) {
        starttime = MPI_Wtime();
    }
    int elem_num = N * N / p;
    int *a = calloc(sizeof(*a), elem_num);
    for (int i = 0; i < p; i++) {
        if (rank == p - 1) {
            fread(a, sizeof(*a), elem_num, f_a);
            if (i != p - 1) {
                MPI_Send(a, elem_num, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        } else if (rank == i) {
            MPI_Recv(a, elem_num, MPI_INT, p - 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        }
    }

    for (int i = 0; i < elem_num; i++) {
        c[(elem_num * rank + i) / N] += a[i] * b[(elem_num * rank + i) % N];
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(c, c_ans, N, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        endtime = MPI_Wtime();
        printf("N_proc = %d, Time is %f\n", p, endtime - starttime);
        int *c_test = calloc(sizeof(*c_test), N);
        for (int i = 0; i < p; i++) {
            fread(a, sizeof(*a), elem_num, f_a);
            for (int j = 0; j < elem_num; j++) {
                c_test[(i * elem_num + j) / N] += a[j] * b[(i * elem_num + j) % N];
            }
        }
        for (int i = 0; i < N; i++) {
            if (c_ans[i] != c_test[i]) {
                printf("Oh no\n");
                break;
            }
        }
        free(c_test);
        FILE *f_c = fopen(argv[3], "w");
        fwrite(c, sizeof(*c), N, f_c);
        fclose(f_c);
    }
    MPI_Finalize();
    free(a);
    free(b);
    free(c);
    free(c_ans);
    fclose(f_a);
    return 0;
}

