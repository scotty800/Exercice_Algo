#include <stdio.h>
#include <stdint.h>

uint8_t registre = 0;

void set_bit(uint8_t *reg, int bit) {
    *reg |= (1 << bit);
}

void clear_bit(uint8_t *reg, int bit) {
    *reg &= ~(1 << bit);
}

int read_bit(uint8_t reg, int bit) {
    return (reg >> bit) & 1;
}

void print_reg(uint8_t reg) {
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (reg >> bit) & 1);
    }
    printf("\n");
}

int main() {
    int bit, choix;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Activer un bit\n");
        printf("2. Désactiver un bit\n");
        printf("3. Lire un bit\n");
        printf("4. Afficher l’état du registre\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Numéro de bit (0 à 7) : ");
                scanf("%d", &bit);
                set_bit(&registre, bit);
                break;
            case 2:
                printf("Numéro de bit (0 à 7) : ");
                scanf("%d", &bit);
                clear_bit(&registre, bit);
                break;
            case 3:
                printf("Numéro de bit (0 à 7) : ");
                scanf("%d", &bit);
                printf("État du bit %d : %d\n", bit, read_bit(registre, bit));
                break;
            case 4:
                printf("État du registre : ");
                print_reg(registre);
                break;
            case 5:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide !\n");
        }
    }
}
