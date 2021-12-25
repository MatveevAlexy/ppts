#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main()
{
    const int N = 1000;
    FILE *a = fopen("a.bin", "w"), *b = fopen("b.bin", "w");
    int num;
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

