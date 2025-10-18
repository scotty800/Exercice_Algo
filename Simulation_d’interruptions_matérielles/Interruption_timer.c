#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

uint8_t TIMER_COUNT = 0;
uint8_t TIMER_INT_FLAG = 0;
#define TIMER_LIMIT 5

void timer_isr()
{
    printf("[INTERRUPTION TIMER] Tick !\n");
    TIMER_INT_FLAG = 0;
}

void timer_tick()
{
    TIMER_COUNT++;
    if (TIMER_COUNT > TIMER_LIMIT)
    {
        TIMER_INT_FLAG = 1;
        TIMER_COUNT = 0;
    }
}

void check_interrupts()
{
    if (TIMER_INT_FLAG)
    {
        timer_isr();
    }
}

int main()
{
    int i;

    printf("Simulation d'une interruption TIMER\n");

    for (i = 0; i < 20; i++)
    {
        sleep(1);
        timer_tick();
        check_interrupts();
    }

    printf("Fin du programme\n");
    return 0;
}