#include <stdio.h>
#include <stdlib.h>

typedef enum TypeCapteur
{
    TEMP,
    PRESS,
    HUMID
} TypeCapteur;

typedef struct Capteur
{
    int id;
    TypeCapteur type;
    double *mesures;
    int nb_mesures;
} Capteur;

void initialiser_capteur(Capteur *c, int id, TypeCapteur type)
{
    c->id = id;
    c->type = type;
    c->nb_mesures = 0;
    c->mesures = malloc(sizeof(double) * 5);
    if (c->mesures == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
}

void acquerir_mesure(Capteur *c)
{
    if (c->nb_mesures >= 5) return;

    double valeur;
    switch(c->type) {
        case TEMP:
            printf("Entrez la température pour le capteur %d : ", c->id);
            break;
        case HUMID:
            printf("Entrez l'humidité pour le capteur %d : ", c->id);
            break;
        case PRESS:
            printf("Entrez la pression pour le capteur %d : ", c->id);
            break;
    }

    scanf("%lf", &valeur);
    c->mesures[c->nb_mesures] = valeur;
    c->nb_mesures++;
}

void affiche_capteur(Capteur *c)
{
    int i;
    char *types[] = {"TEMP", "HUMID", "PRESS"};
    printf("Capteur %d (%s) : ", c->id, types[c->type]);
    for (i = 0; i < c->nb_mesures; i++)
    {
        printf("%.2f ", c->mesures[i]);
    }
    printf("\n");
}

int main()
{
    Capteur capteurs[3];
    int cycle, i, j;

    initialiser_capteur(&capteurs[0], 1, TEMP);
    initialiser_capteur(&capteurs[1], 2, HUMID);
    initialiser_capteur(&capteurs[2], 3, PRESS);

    for (cycle = 0; cycle < 5; cycle++)
    {
        printf("\n=== Cycle %d ===\n", cycle + 1);
        for (i = 0; i < 3; i++) {
            acquerir_mesure(&capteurs[i]);
        }
    }

    printf("\n--- Mesures finales ---\n");
    for (j = 0; j < 3; j++)
    {
        affiche_capteur(&capteurs[j]);
        free(capteurs[j].mesures);
    }

    return 0;
}