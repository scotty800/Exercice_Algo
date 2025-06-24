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
    int i;
    int n;
    Capteur *tab;

    printf("Combien de capteurs voulez-vous enregistrer ? ");
    scanf("%d", &n);

    tab = malloc(sizeof(Capteur) * n);
    if (tab == NULL)
    {
        printf("Erreur Allocation");
        return 1;
    }

    for(i = 0; i < n; i++)
    {
        printf("\nCapteur %d — ID : ", i + 1);
        scanf("%d", &tab[i].id);

        printf("Type (0 = TEMP, 1 = PRESS, 2 = HUMID) : ");
        scanf("%d", (int*)&tab[i].type);

        printf("Valeur mesurée : ");
        scanf("%f", &tab[i].valeur);
    }

    printf("\n📋 Liste des capteurs :\n");

    for(i = 0; i < n; i++)
    {
        affiche_capteur(tab[i]);
    }

    free(tab);
    return(0);
}

