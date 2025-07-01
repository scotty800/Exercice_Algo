#include <stdio.h>
#include <stdlib.h>

typedef struct Timer
{
    int counter;
    int expired;
} Timer;

void start_timer(Timer *t, int duration)
{
    t->counter = duration;
    t->expired = 0;
}

void tick_timer(Timer *t)
{
    if (!t->counter && t->counter > 0)
    {
        t->counter--;
        if (t->counter == 0)
        {
            t->expired = 1;
        }
    }
}

int is_expired(Timer *t)
{
    return t->expired;
}

int main()
{
    Timer t;
    int i;
    
        start_timer(&t, 5);

        for (i = 0; i < 6; i++)
        {
            printf("Tick %d : compteur = %d, expiré = %d\n", i, t.counter, is_expired(&t));
            tick_timer(&t);
        }
}