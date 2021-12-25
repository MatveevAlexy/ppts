#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

int32_t **myallocd(int N) {
    int32_t **a = calloc(sizeof(*a), N);
    for (int i = 0; i < N; i++) {
        a[i] = calloc(sizeof(**a), N);
    }
    return a;
}

void myfreed(int32_t **a, int N) {
    for (int i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);
}

int64_t **myallocl(int N) {
    int64_t **a = calloc(sizeof(*a), N);
    for (int i = 0; i < N; i++) {
        a[i] = calloc(sizeof(**a), N);
    }
    return a;
}

void myfreel(int64_t **a, int N) {
    for (int i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);
}

int main(int argc, char **argv)
{
    int N;
    char t;
    int L2 = PAPI_NULL;
    long long misses;
    long mode = strtol(argv[4], NULL, 10);
    FILE *f_a = fopen(argv[1], "r"), *f_b = fopen(argv[2], "r"), *f_c = fopen(argv[3], "w");
    fread(&t, sizeof(t), 1, f_a);
    fread(&N, sizeof(N), 1, f_a);
    fread(&t, sizeof(t), 1, f_b);
    fread(&N, sizeof(N), 1, f_b);
    if (t == 'd') {
    int32_t **a = myallocd(N), **b = myallocd(N), **c = myallocd(N);
    for (int i = 0; i < N; i++) {
        fread(a[i], sizeof(*(a[i])), N, f_a);
        fread(b[i], sizeof(*(b[i])), N, f_b);
    }
    PAPI_library_init(PAPI_VER_CURRENT);
    PAPI_create_eventset(&L2);
    PAPI_add_event(L2, PAPI_L2_LDM);
    PAPI_start(L2);
    switch (mode) {
        case 0:
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 1:
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 2:
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 3:
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                for (int k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 4:
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int i = 0; i < N; i++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 5:
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                for (int i = 0; i < N; i++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
    }
    PAPI_stop(L2, &misses);
    PAPI_shutdown();
    printf("L2 load misses: %llu\n", misses);
    for (int i = 0; i < N; i++) {
        fwrite(c[i], sizeof(*(c[i])), N, f_c);
    }
    myfreed(a, N);
    myfreed(b, N);
    myfreed(c, N);
    } else {
    int64_t **a = myallocl(N), **b = myallocl(N), **c = myallocl(N);
    for (int i = 0; i < N; i++) {
        fread(a[i], sizeof(*(a[i])), N, f_a);
        fread(b[i], sizeof(*(b[i])), N, f_b);
    }
    PAPI_library_init(PAPI_VER_CURRENT);
    PAPI_create_eventset(&L2);
    PAPI_add_event(L2, PAPI_L2_LDM);
    PAPI_start(L2);
    switch (mode) {
        case 0:
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 1:
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 2:
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 3:
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                for (int k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 4:
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int i = 0; i < N; i++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
        break;
        case 5:
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                for (int i = 0; i < N; i++) {
                    c[i][j] += a[i][k] * b[j][k];
                }
            }
        }
    }
    PAPI_stop(L2, &misses);
    PAPI_shutdown();
    printf("L2 load misses: %llu\n", misses);
    for (int i = 0; i < N; i++) {
        fwrite(c[i], sizeof(*(c[i])), N, f_c);
    }
    myfreel(a, N);
    myfreel(b, N);
    myfreel(c, N);
    }
    fclose(f_a);
    fclose(f_b);
    fclose(f_c);
    return 0;
}
