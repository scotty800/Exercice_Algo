#include <stdio.h>

int main() {
    int a, b, res;
    char op;

    printf(" Entrer le premier nombre : ");
    scanf("%d", &a);
    printf("Entrer le deuxieme nombre : ");
    scanf("%d", &b);
    printf("Choisir l'operateur (+, -, *, /) : ");
    scanf(" %c", &op);

    switch(op) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            if (b != 0) {
                res = a / b;
            }
            else {
                printf("Erreur : Division par zero.\n");
                return 1;
            }
            break;
        default:
            printf("Operateur invalide.\n");
    }

    printf("Le resultat est : %d\n", res);
    return 0;
}