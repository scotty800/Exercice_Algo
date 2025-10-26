#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_counter = 0;
pthread_mutex_t lock;

void *task_write(void *arg)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&lock);
        shared_counter++;
        printf("[WRITE] Counter = %d\n", shared_counter);
        pthread_mutex_unlock(&lock);
        usleep(100000);
    }
    return NULL;
}

void *task_read(void *arg)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&lock);
        printf("[READE] Counter = %d\n", shared_counter);
        pthread_mutex_unlock(&lock);
        usleep(120000);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, task_write, NULL);
    pthread_create(&t2, NULL, task_read, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("\n[END] Final Counter = %d\n", shared_counter);
    return 0;
}