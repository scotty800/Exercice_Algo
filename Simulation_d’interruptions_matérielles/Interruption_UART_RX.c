#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

uint8_t UART_DR = 0;
uint8_t UART_INT_FLAG = 0;

void uart_rx_isr()
{
    printf("[INTERRUPTION UART RX] Caractère reçu : '%c'\n", UART_DR);
    UART_INT_FLAG = 0;
}

void uart_receive_sim(char c)
{
    UART_DR = c;
    UART_INT_FLAG = 1;
}

void check_interrupts()
{
    if(UART_INT_FLAG)
    {
        uart_rx_isr();
    }
}

int main()
{
    int i;
    char *message = "HELLO";

    for (i = 0; i < strlen(message); i++)
    {
        sleep(1);
        uart_receive_sim(message[i]);
        check_interrupts();
    }

   printf("Fin de la simulation\n");
   return 0;
}