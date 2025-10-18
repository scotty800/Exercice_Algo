#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

uint8_t GPIO_INT_STATUS = 0;

void gpio_isr()
{
    printf("[INTERRUPTION GPIO] Bouton pressé !\n");
    GPIO_INT_STATUS = 0;
}

void check_interrupts()
{
    if (GPIO_INT_STATUS & 0x01) {
        gpio_isr();
    }
}

int main()
{
    int i;
    printf("Simulation d'une interruption GPIO\n");

    for (i = 0; i < 5; i++)
    {
        sleep(1);
        if (i == 2)
        {
            printf("Appui sur le bouton détecté\n"); 
            GPIO_INT_STATUS |= 1;  
        }
        check_interrupts();
    }

    printf("Fin du programme\n");
    return 0;

}