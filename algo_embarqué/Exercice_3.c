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

void mettre_a_jour_capteur(Capteur *cap)
{
    if (cap == NULL)
    {
        return;
    }

    printf("Avant mise à jour : Capteur ID: %d - ", cap->id);
    switch (cap->type) {
        case TEMP:
            printf("Type: TEMP");
            break;
        case HUMID:
            printf("Type: HUMID");
            break;
        case PRESS:
            printf("Type: PRESS");
            break;
    }
    printf(" - Valeur: %.2f\n", cap->valeur);

    printf("Nouvelle valeur mesurée : ");
    scanf("%1f", &(cap->valeur));

    printf("Mise à jour effectuée.\n");
    printf("Capteur ID: %d - Valeur: %.2f\n", cap->id, cap->valeur);
}

int main()
{
    Capteur capteurs[3] = {
        {10, TEMP, 23.5},
        {20, HUMID, 45.1},
        {30, PRESS, 1013.2}
    };

    int id_recherche, i;
    printf("Entrez l'ID du capteur à mettre à jour : ");
    scanf("%d", &id_recherche);

    int trouve = 0;
    for (i = 0; i < 3; i++)
    {
        if (capteurs[i].id == id_recherche) {
            mettre_a_jour_capteur(&capteurs[i]);
            trouve = 1;
            break;
        }
    }

      if (!trouve) {
        printf("Capteur avec ID %d non trouvé.\n", id_recherche);
    }

}
