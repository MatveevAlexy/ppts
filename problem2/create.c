#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char **argv)
{
    long N = strtol(argv[1], NULL, 10);
    char t = argv[2][0];
    FILE *a = fopen("a", "w"), *b = fopen("b", "w");
    int num;
    fwrite(&t, sizeof(t), 1, a);
    fwrite(&N, sizeof(N), 1, a);
    fwrite(&t, sizeof(t), 1, b);
    fwrite(&N, sizeof(N), 1, b);
    srand(time(NULL));
    for (int i = 0; i < N * N; i++) {
        num = rand() % 500;
        fwrite(&num, sizeof(num), 1, a);
    }
    for (int i = 0; i < N * N; i++) {
        num = rand() % 500;
        fwrite(&num, sizeof(num), 1, b);
    }
    fclose(a);
    fclose(b);
    return 0;
}

