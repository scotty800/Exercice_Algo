#include <stdio.h>
#include <stdlib.h>

typedef struct Timer
{
    int compteur;
    int actif;
} Timer;

void start_timer(Timer *t, int duree)
{
    t->compteur = duree;
    t->actif = 1;
}

void tick_timer(Timer *t)
{
    if (t->compteur > 0)
    {
        t->compteur--;
        if (t->compteur == 0)
        {
            t->actif = 0;
        }
    }
}

int is_expired(Timer *t)
{
    return t->actif;
}

int main()
{
    Timer t;
    int i;

    start_timer(&t, 5);

    for (i = 0; i < 6; i++)
    {
        printf("Tick %d : compteur = %d, expiré = %d\n", i, t.compteur, is_expired(&t));
        is_expired(&t);
    }
}