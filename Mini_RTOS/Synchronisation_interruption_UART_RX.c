#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

uint8_t uart_interrupt_flag = 0;
char DR = 0;

void task_blink()
{
    printf("[Tâche] Blink LED\n");
}

void task_sensor()
{
    printf("[Tâche] Lecture capteur\n");
}

void task_uart_handler()
{
    if (uart_interrupt_flag)
    {
        printf("[Tâche] UART RX ISR : Caractère reçu = '%c'\n", DR);
        uart_interrupt_flag = 0;
    }
}

void uart_receive_sim(char c)
{
    DR = c;
    uart_interrupt_flag = 1;
}

#define NB_TASKS 3

void (*tasks[NB_TASKS])() = { task_blink, task_sensor, task_uart_handler };

int currentTask = 0;
int timerCount = 0;

void timer_interrupt()
{
    currentTask = (currentTask + 1) % NB_TASKS;
    timerCount = 0;
}

int main()
{
    int i;
    printf("=== Mini RTOS avec Timer + UART RX Interrupt ===\n");

    for (i = 0; i < 12; i++)
    {
        sleep(1);

        if (i == 5)
        {
            uart_receive_sim('A');
        }

        if (i == 9)
        {
            uart_receive_sim('B');
        }

        tasks[currentTask]();
        timerCount++;

        if (timerCount >= 3)
        {
            timer_interrupt();
        }
    }

    printf("=== Fin de la simulation ===\n");
    return 0;
}
