#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Capteur {
    int id;
    char nom[32];
    float temperature_actuelle;
    float historique[5];
    struct Capteur *next;
} Capteur;

Capteur *init_liste_capteurs(int id, char *nom, float temp, float histo[5])
{
    int index1, index2;
    Capteur *c = malloc(sizeof(Capteur));
    if (!c)
    {
        printf("Erreur d'allocation");
        exit(1);
    }
    c->id = id;

    for (index1 = 0; nom[index1] != '\0' && index1 < 31; index1++)
    {
        c->nom[index1] = nom[index1];
    }
    c->nom[index1] = '\0';

    c->temperature_actuelle = temp;

    for (index2 = 0; index2 < 5; index2++)
    {
        c->historique[index2] = histo[index2];
    }
    
    c->next = NULL;

    return c;
}

float generer_temperature_simulee()
{
    return (float)(rand() % 170) / 10.0 + 18.0;
}

void mise_a_jour_temperature(Capteur *c, float nouvelle_temp)
{
    int i;

    for (i = 0; i < 5 - 1; i++)
    {
        c->historique[i] = c->historique[i+1];
    }

    c->historique[5 - 1] = nouvelle_temp;
    c->temperature_actuelle = nouvelle_temp;
}

void mise_a_jour_liste(Capteur *tete)
{
    float nouvelle_temp;

    while(tete)
    {
        nouvelle_temp = generer_temperature_simulee();
        printf("Capteur %d (%s) - Ancienne : %.2f°C | Nouvelle : %.2f°C\n", tete->id, tete->nom, tete->temperature_actuelle, nouvelle_temp);

        mise_a_jour_temperature(tete, nouvelle_temp);

        tete = tete->next;
    }
}

float moyenne_historique(Capteur *c)
{
    if (!c)
    {
        return 0.0;
    }

    float somme;
    int i;

    for (i = 0; i < 5; i++)
    {
        somme += c->historique[i];
    }

    return somme / 5;
}

void affiche_capteur(Capteur *c)
{
    printf("Liste Capteur");

    while(c != NULL)
    {
        printf("Capteur %d (%s) : %f°C ", c->id, c->nom, c->temperature_actuelle);
        c = c->next;
    }
}

void detecter_anomalie(Capteur *tete)
{
    Capteur *current = tete;
    FILE* fp = fopen("logs.txt", "a");
    float moyenne;
    time_t timestamp;
    struct tm *now;
    char strNow[9];
    
    while(current != NULL)
    {
        moyenne = moyenne_historique(current);

        if (current->temperature_actuelle > 30.0 || moyenne > 28.0)
        {
            printf("Alerte : Capteur %d SurChauffe détectée : %.2f°C - Moyenne : %.2f°C", current->id, current->temperature_actuelle, moyenne);

            timestamp = time(NULL);
            now = localtime(&timestamp);
            strftime(strNow, sizeof(strNow), "%H:%M:%S", now);

            fprintf(fp, "Alerte : Capteur %d SurChauffe détectée : %.2f°C - Moyenne : %.2f°C - %s\n", current->id, current->temperature_actuelle, moyenne, strNow);
        }
        current = current->next;
    }

    fclose(fp);
}

int main() {

    srand(time(NULL)); // initialise le générateur aléatoire

    float histo1[] = {22.1, 22.3, 22.2, 22.4, 22.6};
    float histo2[] = {20.0, 21.0, 21.2, 21.3, 21.5};
    float histo3[] = {19.9, 20.1, 20.0, 19.8, 19.7};

    Capteur *c1 = init_liste_capteurs(1, "Salle A", 22.6, histo1);
    Capteur *c2 = init_liste_capteurs(2, "Salle B", 21.5, histo2);
    Capteur *c3 = init_liste_capteurs(3, "Exterieur", 19.7, histo3);

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
                affiche_capteur(c1);
                break;
            case 2:
                mise_a_jour_liste(c1);
                break;
            case 3:
                detecter_anomalie(c1);
                break;
            case 4:
                printf("Au revoir\n");
                return 0;
        }
    }
}