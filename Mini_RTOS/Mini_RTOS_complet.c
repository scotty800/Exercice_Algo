#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

typedef struct Task
{
    char *name;
    void (*taskFunc)(void);
    uint8_t priority;
    uint8_t ready;
} Task;

void task_blink()
{
    printf("[Tâche] Blink LED\n");
}

void task_sensor()
{
    printf("[Tâche] Lecture capteur\n");
}

void task_uart()
{
    printf("[Tâche] UART RX Handler\n");
}

#define NB_TASKS 3

Task tasks[NB_TASKS] = {
    {"Blink", task_blink, 1, 1},
    {"Capteur", task_sensor, 2, 1},
    {"UART", task_uart, 3, 0}
};

char DR = 0;
int timerCount = 0;

void uart_receive_sim(char c)
{
    DR = c;
    tasks[2].ready = 1;
    printf("[INTERRUPTION UART] Nouveau caractère reçu : '%c'\n", c);
}

void scheduler()
{
    int maxPrio = -1, index = -1, i;

    for (i = 0; i < NB_TASKS; i++)
    {
        if (tasks[i].ready && tasks[i].priority > maxPrio)
        {
            maxPrio = tasks[i].priority;
            index = i;
        }

        if (index != -1)
        {
            tasks[index].taskFunc();
            if (index == 2)
            {
                tasks[index].ready = 0;
            }
        }
    }
}

int main()
{
    int t;
    printf("=== Mini RTOS à priorité + interruptions ===\n");

    for (t = 0; t < 12; t++)
    {
        sleep(1);

        if (t == 4)
        {
            uart_receive_sim('A');
        }

        if (t == 8)
        {
            uart_receive_sim('B');
        }

        scheduler();
        timerCount++;
    }

    printf("=== Fin du mini RTOS ===\n");
    return 0;
}