#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

uint8_t GPIO_FLAG = 0;
uint8_t TIMER_FLAGE = 0;
uint8_t UART_FLAGE = 0;
uint8_t UART_DR = 0;
uint8_t TIMER_COUNT = 0;

#define TIMER_TIME 3

void gpio_isr()
{
    printf("[INTERRUPTION GPIO] Bouton pressé !\n");
    GPIO_FLAG = 0;
}

void timer_isr()
{
    printf("[INTERRUPTION TIMER] Tick !\n");
    TIMER_FLAGE = 0;
}

void uart_isr()
{
    printf("[INTERRUPTION UART RX] Caractère reçu : '%c'\n", UART_DR);
    UART_FLAGE = 0;
}

void uart_receive_sim(char c)
{
    UART_DR = c;
    UART_FLAGE = 1;
}

void timer_tick()
{
    TIMER_COUNT++;
    if (TIMER_COUNT > TIMER_TIME)
    {
        TIMER_FLAGE = 1;
        TIMER_COUNT = 0;
    }
}


void check_interrupts()
{
    if (GPIO_FLAG) {
        gpio_isr();
    }

    if (TIMER_FLAGE) {
        timer_isr();
    }

    if (UART_FLAGE) {
        uart_isr();
    }
}

int main()
{
    int t;
    char *caractère = "A";

    for (t = 0; t < 10; t++)
    {
        sleep(1);
        timer_tick();
        if (t == 5)
        {
            GPIO_FLAG = 1;
        }

        if (t == 7)
        {
            for (t = 0; t < strlen(caractère); t++)
            {
                uart_receive_sim(caractère[t]);
            }
        }

        check_interrupts();
    }

    printf("=== Fin du programme ===\n");
    return 0;
}