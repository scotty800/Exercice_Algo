#include <stdio.h>

enum Day {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

int main() {
    int n;

    printf("Entrer un nombre (1-7) : ");
    scanf("%d", &n);

    switch (n)
    {
        case MONDAY:
            printf("Lundi\n");
            break;
        case TUESDAY:
            printf("Mardi\n");
            break;
        case WEDNESDAY:
            printf("Mercredi\n");
            break;
        case THURSDAY:
            printf("Jeudi\n");
            break;
        case FRIDAY:
            printf("Vendredi\n");
            break;
        case SATURDAY:
            printf("Samedi\n");
            break;
        case SUNDAY:
            printf("Dimanche\n");
            break;
        default:
            printf("Nombre invalide. Veuillez entrer un nombre entre 1 et 7.\n");
            break;
    }

    return 0;
}