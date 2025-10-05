#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret, guess, essais = 0;
    srand(time(NULL));
    secret = rand() % 100 + 1; // Nombre aleatoire entre 1

    do {
        printf("Devinez le nombre (entre 1 et 100) : ");
        scanf("%d", &guess);
        essais++;

        if (guess < secret) {
            printf("Trop bas!\n");
        } else if (guess > secret) {
            printf("Trop haut!\n");
        } else {
            printf("Bravo ! Vous avez trouvé en %d essais.\n", essais);
        }
    } while (guess != secret);

    return 0;
}