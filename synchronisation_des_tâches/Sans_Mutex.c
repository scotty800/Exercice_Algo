#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_counter;

void *task_write(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        shared_counter++;
        printf("[WRITE] Counter = %d\n", shared_counter);
        usleep(100000);
    }
    return NULL;
}

void *task_read(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("[READ] counter = %d\n", shared_counter);
        usleep(120000);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, task_write, NULL);
    pthread_create(&t2, NULL, task_read, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\n[END] Final counter = %d\n", shared_counter);
    return 0;
}