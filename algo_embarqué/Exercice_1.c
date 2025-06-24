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
    float valeur;
} Capteur;

void affiche_capteur(Capteur c)
{
    char *types[] = {"TEMP", "PRESS", "HUMID"};

    printf("Capteur ID: %d - Type: %s - Valeur: %2.f\n ", c.id, types[c.type], c.valeur);
}

int main()
{
    int n = 3;
    Capteur *tab;
    int i;

    tab = malloc(sizeof(Capteur) * n);
    if (tab == NULL)
    {
        printf("Erreur Allocation");
        return 1;
    }

    tab[0] = (Capteur){1, TEMP, 23.4};
    tab[1] = (Capteur){2, HUMID, 57.2};
    tab[2] = (Capteur){3, PRESS, 1013.25};

    for(i = 0; i < n; i++)
    {
        affiche_capteur(tab[i]);
    }

    free(tab);
    return 0;
}