#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

typedef struct Task{
    char *name;
    void (*taskFunc)(void);
    uint8_t state;
    uint8_t priority;
} Task;

#define READY 0
#define RUNNING 1
#define WAITING 2

void task_blink()
{
    printf("[Tàche] Blink LED\n");
}

void task_sensor()
{
    printf("[Tàche] Lecture capteur\n");
}

void task_uart()
{
    printf("[Tàche] Communication UART\n");
}

int main()
{
    Task tasks[3] = {
        {"Blink", task_blink, READY, 1},
        {"Sensor", task_sensor, READY, 2},
        {"UART", task_uart, READY, 1},
    };

    printf("=== Mini RTOS - Ordonnanceur Round Robin ===\n");

    for (int i = 0; i < 6; i++)
    {
        Task *t = &tasks[i % 3];
        printf("\nOrdonnanceur -> %s\n", t->name);
        t->state = RUNNING;
        t->taskFunc();
        t->state = READY;
        sleep(1);
    }

    printf("\n=== Fin du cycle ===\n");
    return 0;
}