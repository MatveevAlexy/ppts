#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int size, size_last, *a, n_chank;
long p;

int comp(const int *a, const int *b) {
    return *a - *b;
}

void sort(int i)
{
    if (i != n_chank - 1) {
        qsort(&a[i * size], size, sizeof(*a), (int(*) (const void *, const void *)) comp);
    } else {
        qsort(&a[size * i], size_last, sizeof(*a), (int(*) (const void *, const void *)) comp);
    }
}

void process(int i)
{
    int *b = calloc(sizeof(*b), size), start = i * size;
    for (int j = 0; j < size; j++) {
        b[j] = a[start + j];
    }
    int o = 0, p = 0, size_p = i == n_chank - 2 ? size_last : size;
    while (o < size && p < size_p) {
        if (b[o] < a[start + size + p]) {
            a[start + o + p] = b[o];
            o++;
        } else {
            a[start + o + p] = a[start + size + p];
            p++;
        }
    }
    if (o < size) {
        for (; o < size; o++) {
            a[start + o + p] = b[o];
        }
    }
    free(b);
}

int main(int argc, char **argv)
{
    long n = strtol(argv[1], NULL, 10);
    p = strtol(argv[2], NULL, 10);
    a = calloc(sizeof(*a), n), n_chank = 4 * p, size = n / n_chank, size_last = n % n_chank;
    if (size_last == 0) {
        size_last = size;
    }
    int *c = calloc(sizeof(*c), n);
    double start, mid, end;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = c[i] = rand() % 100;
    }
    start = omp_get_wtime();
    #pragma omp parallel num_threads(p)
    {
        #pragma omp single
        {
            for (int i = 0; i < n_chank; i++) {
                #pragma omp task
                    sort(i);
            }
        }
    }
    for (; n_chank > 1; n_chank = (n_chank + 1) / 2) {
        #pragma omp parallel num_threads(p)
        {
            #pragma omp single
            {
                for (int i = 0; i < n_chank - 1; i += 2) {
                    #pragma omp task
                        process(i);
                }
            }
        }
        /*for (int i = 0; i < n_chank - 1; i += 2) {
            process(i);
        }*/
        size_last += size * !(n_chank & 1);
        size <<= 1;
    }
    
    mid = omp_get_wtime();

    qsort(c, n, sizeof(*a), (int(*) (const void *, const void *)) comp);

    end = omp_get_wtime();

    for (int i = 0; i < n; i++) {
        if (a[i] != c[i]) {
            printf("No\n");
            break;
        }
    }

    printf("%ld\nparallel: %f\nqsort: %f\n", p, mid - start, end - mid);
    free(a);
    free(c);
    return 0;
}
