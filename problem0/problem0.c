#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

double pi = 0;
long num_rect, num_threads;
pthread_mutex_t mut;

void *calcPart(void *param)
{
    double sum = 0, x;
    int thread_num = *((int *)param);
    for (int i = thread_num; i < num_rect; i += num_threads) {
        x = 1.0 / num_rect * (0.5 + i);
        sum += 4.0 / (1 + x * x);
    }
    pthread_mutex_lock(&mut);
    pi += sum;
    pthread_mutex_unlock(&mut);
    return 0;
}

int main(int argc, char **argv)
{
    num_rect = strtol(argv[1], NULL, 10);
    num_threads = strtol(argv[2], NULL, 10);
    int nums[num_threads];
    pthread_t threads[num_threads];
    pthread_mutex_init(&mut, NULL);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < num_threads; i++) {
        nums[i] = i;
        pthread_create(&threads[i], NULL, calcPart, (void*) &nums[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    pi /= num_rect;
    gettimeofday(&end, NULL);
    printf("Pi = %f\n", pi);
    double time = (double) (end.tv_sec - start.tv_sec) +
            (double) (end.tv_usec - start.tv_usec) / 1000000;
    printf("Time: %lf\n", time);
    pthread_mutex_destroy(&mut);
    return 0;
}
