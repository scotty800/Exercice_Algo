#include <stdio.h>
#include <unistd.h>

unsigned char GPIO = 0x00;
#define LED_PIN 0 

void led_on() {
    GPIO |= (1 << LED_PIN);
    printf("LED ON, GPIO state: 0x%02X\n", GPIO);
}

void led_off() {
    GPIO &= ~(1 << LED_PIN);
    printf("LED OFF, GPIO state: 0x%02X\n", GPIO);
}

int main() {
    int i;

    for (i = 0; i < 5; i++)
    {
        led_on();
        sleep(1);
        led_off();
        sleep(1);
    }

    return 0;
}