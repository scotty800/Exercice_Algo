#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int led_state = 0;

void button_interrupt() {
    led_state = !led_state;
    if(led_state) {
        printf("LED ON\n");
    } else {
        printf("LED OFF\n");
    }
}

int main() {
    int i;
    srand(time(NULL));
    for (i = 0; i < 10; i++)
    {
        if (rand() %2 == 0)
        {
            button_interrupt();
        }
        sleep(2);
    }

    return 0;
}