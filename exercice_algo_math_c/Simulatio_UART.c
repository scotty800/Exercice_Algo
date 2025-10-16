#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define UART_BASE_ADDR 0x40004000
#define UART_DR        (*(volatile uint8_t *)(UART_BASE_ADDR + 0x00))
#define UART_SR        (*(volatile uint8_t *)(UART_BASE_ADDR + 0x04))
#define UART_CR        (*(volatile uint8_t *)(UART_BASE_ADDR + 0x08))

uint8_t UART_DR_SIM = 0;
uint8_t UART_SR_SIM = 0x01;
uint8_t UART_CR_SIM = 0;

#undef UART_DR
#undef UART_SR
#undef UART_CR
#define UART_DR        (UART_DR_SIM)
#define UART_SR        (UART_SR_SIM)
#define UART_CR        (UART_CR_SIM)

int uart_init() {
    UART_CR |= (1 << 0);
    printf("UART initialized.\n");
}

void uart_send(char c)
{
    if (!(UART_CR & 1))
    {
        printf("Erreur : UART non activé !\n");
        return;
    }

    if (!(UART_SR & (1 << 0)))
    {
        printf("UART non prêt à envoyer.\n");
        return;
    }

    if (UART_CR & 1)
    {
        UART_SR &= ~(1 << 0);
        UART_DR = c;
        printf("UART envoi : %c\n", UART_DR);
        UART_SR |= (1 << 0);
        UART_SR |= (1 << 1); 
    }
}

char uart_receive()
{
    if (!(UART_CR & 1))
    {
        printf("Erreur : UART non activé !\n");
        return 0;
    }

    if (UART_SR & (1 << 1))
    {
        UART_SR &= ~(1 << 1);
        printf("UART reçu : %c\n", UART_DR);
        return UART_DR;
    }
    else
    {
        printf("Aucune donnée reçue.\n");
        return 0;
    }
}

int main()
{
    int i;

    uart_init();
    char *msg = "HELLO";

    for (i = 0; i < strlen(msg); i++)
    {
        uart_send(msg[i]);
        uart_receive();
    }

    return 0;
    
}
