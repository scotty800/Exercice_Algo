#include <stdio.h>
#include <stdlib.h>

typedef struct Capteur
{
    int id;
    char position[20];
    float temperature_actuelle;
    float historique[5];
    struct Capteur *next;
} Capteur;

Capteur *init_capteur(int id, char *position, float temp, float histo[5])
{
    int index1, index2;

    Capteur *c = malloc(sizeof(Capteur));
    if (c == NULL)
    {
        printf("ERREUR Allocation");
        exit(1);
    }
    c->id = id;
    for (index1 = 0; position[index1] != '\0' && index1 < 19; index1++)
    {
        c->position[index1] = position[index1];
    }
    c->position[index1] = '\0';  // Terminer la chaîne


    c->temperature_actuelle = temp;

    for (index2 = 0; index2 < 5; index2++)
    {
        c->historique[index2] = histo[index2];
    }

    c->next = NULL;

    return c;
}

void afficher_capteur(Capteur* c)
{
    int i;

    printf("Capteur %d (position : %s)\n Température actuelle : %f°c\n ", c->id, c->position, c->temperature_actuelle);

    for (i = 0; i < 5; i++)
    {
        printf("Historique : %f ", c->historique[i]);
    }
    printf("\n");
}

void afficher_liste(Capteur* tete)
{
    printf("Liste des capteurs : ");

    while(tete != NULL)
    {
        printf("Capteur %d (%s) : %f°C ", tete->id, tete->position, tete->temperature_actuelle);
        tete = tete->next;
    }

    printf("\n");
}

void mise_a_jour(Capteur* c, float nouvelle_valeur)
{
    int i;

    for (i = 0; i < 5 - 1; i++)
    {
        c->historique[i] = c->historique[i + 1];
    }

    c->historique[5 - 1] = nouvelle_valeur;
    c->temperature_actuelle = nouvelle_valeur;
}

void mise_a_jour_liste(Capteur* tete)
{
    float valeur;
    float newValue;
    while(tete)
    {
        printf("Avant : %f\n ", tete->temperature_actuelle);
        newValue = scanf("%f", &valeur);

        if (newValue == 1)
        {
            mise_a_jour(tete, valeur);
        }
        else
        {
            printf("Entreée invalide");
        }
        tete = tete->next;
    }

    printf("Après : %f ", tete->temperature_actuelle);
}

float moyenne_historique(Capteur* c)
{
    int i;
    float somme;

    if (!c)
    {
        return 0.0;
    }

    for (i = 0; i < 5; i++)
    {
        somme += c->historique[i];
    }

    return somme / 5;
}

void detecter_surchauffe(Capteur* tete)
{
    Capteur *current = tete;
    float moyenne;
    
    while(current != NULL)
    {
        moyenne = moyenne_historique(current);

        if(current->temperature_actuelle > 30.0 || moyenne > 28.0)
        {
            printf("Alerte : Capteur %d dépasse le seuil ! (actuell : %.2f°C, moyenne : %.2f°C)", current->id, current->temperature_actuelle, moyenne);
        }

        current = current->next;
    }
}

int main() {
    float histo1[] = {22.1, 22.3, 22.2, 22.4, 22.6};
    float histo2[] = {20.0, 21.0, 21.2, 21.3, 21.5};
    float histo3[] = {19.9, 20.1, 20.0, 19.8, 19.7};

    Capteur *c1 = init_capteur(1, "Salle A", 22.6, histo1);
    Capteur *c2 = init_capteur(2, "Salle B", 21.5, histo2);
    Capteur *c3 = init_capteur(3, "Exterieur", 19.7, histo3);

    c1->next = c2;
    c2->next = c3;

    int choix;
    float val;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Afficher les capteurs\n");
        printf("2. Mettre à jour les températures\n");
        printf("3. Vérifier les alertes\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficher_liste(c1);
                break;
            case 2:
                mise_a_jour_liste(c1);
                break;
            case 3:
                detecter_surchauffe(c1);
                break;
            case 4:
                printf("Au revoir\n");
                return 0;
        }
    }
}
