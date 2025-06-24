#include <stdio.h>
#include <stdlib.h>

typedef struct Echantillon
{
    float valeur;
    struct Echantillon *next;
    struct Echantillon *prev;
} Echantillon;

void ajouter_echantillon(Echantillon **debut, Echantillon **fin)
{
    float valeur;
    printf("Entrez un échantillon : ");
    scanf("%f", &valeur);

    Echantillon *newnode = malloc(sizeof(Echantillon));
    if (!newnode)
    {
        printf("Erreur Allocation\n");
        return;
    }
    newnode->valeur = valeur;
    newnode->next = NULL;
    newnode->prev = NULL;

    if (*debut == NULL) // Liste vide
    {
        *debut = *fin = newnode;
    }
    else
    {
        (*fin)->next = newnode;
        newnode->prev = *fin;
        *fin = newnode;
    }
}

void calcule_moyenne_glissant(Echantillon *fin)
{
    int count = 0;
    float somme = 0.0;
    float moyenne;

    Echantillon *current = fin;

    while (current != NULL && count < 3)
    {
        somme += current->valeur;
        current = current->prev;
        count++;
    }

    if (count > 0)
    {
        moyenne = somme / count;
        printf("Moyenne glissante : %.2f\n", moyenne);
    }
}

void free_liste(Echantillon *debut)
{
    Echantillon *temp;
    while (debut != NULL)
    {
        temp = debut;
        debut = debut->next;
        free(temp);
    }
}

int main()
{
    Echantillon *debut = NULL;
    Echantillon *fin = NULL;
    int i;

    for (i = 0; i < 6; i++)
    {
        ajouter_echantillon(&debut, &fin);
        calcule_moyenne_glissant(fin);
    }

    free_liste(debut);
    return 0;
}
