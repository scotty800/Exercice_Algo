#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef enum TypeCapteur{
    TEMP,
    LUMIERE,
    DISTANCE,
} TypeCapteur;

typedef struct Capteur {
    char nom[20];
    float valeur;
    TypeCapteur type;
} Capteur;

float lire_capteur(TypeCapteur type) {
    switch(type) {
        case TEMP:
            return 20.0 + rand() % 15;
        case LUMIERE:
            return rand() % 1000;
        case DISTANCE:
            return rand() % 200;
        default: return 0;
    }
}

int main() {
    srand(time(NULL));
    Capteur capteur[3] = {
        {"Température", 0, TEMP},
        {"Lumière", 0, LUMIERE},
        {"Distance", 0, DISTANCE}
    };

    for (int t = 0; t < 5; t++) {
        printf("=== Mesures %d ===\n", t + 1);
        for (int i = 0; i < 3; i++) {
            capteur[i].valeur = lire_capteur(capteur[i].type);
            printf("%s: %.2f\n", capteur[i].nom, capteur[i].valeur);
        }
        printf("\n");
        sleep(1);
    }

    return 0;
}