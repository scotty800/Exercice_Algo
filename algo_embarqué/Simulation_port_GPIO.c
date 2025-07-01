#include <stdio.h>
#include <stdint.h>

uint8_t DDR = 0x00;
uint8_t PORT = 0x00;
uint8_t PIN = 0x00;

void set_direction(int bit, int direction)
{
    if (bit < 0 || bit > 7)
        return;

    if (direction == 1)
        DDR |= (1 << bit);
    else
        DDR &= ~(1 << bit);
}

void write_gpio(int bit, int value)
{
    if ((DDR >> bit) & 1)
    {
        if (value == 1)
            PORT |= (1 << bit);
        else
            PORT &= ~(1 << bit);
    }
}

int read_gpio(int bit)
{
    if (((DDR >> bit) & 1) == 0)
        return (PIN >> bit) & 1;
    return -1;
}

void simulate_input(int bit, int value)
{
    if (bit < 0 || bit > 7)
        return;

    if (value == 1)
        PIN |= (1 << bit);
    else
        PIN &= ~(1 << bit);
}

void print_registers(uint8_t value)
{
    for (int bit = 7; bit >= 0; bit--)
        printf("%d", (value >> bit) & 1);
    printf("\n");
}

int main()
{
    int bit, choix, value;

    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Configurer une broche\n");
        printf("2. Écrire sur une broche\n");
        printf("3. Lire une broche\n");
        printf("4. Simuler une entrée\n");
        printf("5. Afficher les registres\n");
        printf("6. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                printf("Bit ? ");
                scanf("%d", &bit);
                printf("Direction (0:entrée, 1:sortie) ? ");
                scanf("%d", &value);
                set_direction(bit, value);
                break;
            case 2:
                printf("Bit ? ");
                scanf("%d", &bit);
                printf("Valeur (0 ou 1) ? ");
                scanf("%d", &value);
                write_gpio(bit, value);
                break;
            case 3:
                printf("Bit ? ");
                scanf("%d", &bit);
                value = read_gpio(bit);
                if (value != -1)
                    printf("Valeur lue : %d\n", value);
                else
                    printf("Erreur : broche non configurée en entrée\n");
                break;
            case 4:
                printf("Bit ? ");
                scanf("%d", &bit);
                printf("Valeur à simuler (0 ou 1) ? ");
                scanf("%d", &value);
                simulate_input(bit, value);
                break;
            case 5:
                printf("DDR  : "); print_registers(DDR);
                printf("PORT : "); print_registers(PORT);
                printf("PIN  : ");  print_registers(PIN);
                break;
            case 6:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide !\n");
        }
    }
}
