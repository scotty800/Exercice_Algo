#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

typedef struct Task {
    char *name;
    void (*taskFunc)(void);
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
    printf("[Tâche] Communication UART\n");
}

#define NB_TASKS 3

Task tasks[NB_TASKS] = {
    {"Blink", task_blink},
    {"Sensor", task_sensor},
    {"UART", task_uart}

};

int currentTask = 0;
int timerCount = 0;

void timer_interrupt()
{
    printf("\n[INTERRUPTION TIMER] -> Changement de tâche\n");
    currentTask = (currentTask + 1) % NB_TASKS;
    timerCount = 0;
}

int main()
{
    printf("=== Mini RTOS avec Timer Interrupt ===\n");

    while (1)
    {
        tasks[currentTask].taskFunc();
        sleep(1);
        timerCount++;

        if (timerCount >= 3)
        {
            timer_interrupt();
        }
    }
    
    return 0;
}