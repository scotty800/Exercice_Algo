#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 30

typedef enum Etat
{
    IDLE,
    PRESS_DETECTED,
    CONFIRMED
} Etat;

int simulate_button()
{
    return rand() % 2;
}

int main()
{
    srand(time(NULL));
    int i;
    int lecture;
    int compteur = 0;
    Etat etat = IDLE;

    for (i = 0; i < MAX; i++)
    {
        lecture = simulate_button();
        printf("[%d] Valeur lue = %d | ", i, lecture);

        switch(etat)
        {
            case IDLE:
                if (lecture == 1)
                {
                    compteur = 1;
                    etat = PRESS_DETECTED;
                }
                break;
            
            case PRESS_DETECTED:
                if (lecture == 1)
                {
                    compteur++;
                    if (compteur >= 3)
                    {
                        etat = CONFIRMED;
                        printf(">>> BOUTON CONFIRMÉ <<< ");
                    }
                }
                else
                {
                    compteur = 0;
                    etat = IDLE;
                }
                break;
            
            case CONFIRMED:
                if (lecture == 0)
                {
                    etat = IDLE;
                    compteur = 0;
                }
                break;
        }

        printf("État actuel : ");
        switch(etat)
        {
            case IDLE: 
                printf("IDLE\n"); 
                break;
            case PRESS_DETECTED:
                printf("PRESS_DETECTED\n");
                break;
            case CONFIRMED:
                printf("CONFIRMED\n");
                break;
        }
    }
    return 0;

}