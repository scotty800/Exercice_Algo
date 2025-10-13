#include <stdio.h>
#include <stdint.h>

#define GPIO_BASE8_ADDR 0X40021000
#define LED_PIN 5

int main() {
    volatile uint32_t *GPIO = (uint32_t *)GPIO_BASE8_ADDR;

    uint32_t register_simule = 0x00000000;
    GPIO = &register_simule;

    *GPIO |= (1 << LED_PIN);

    printf("GPIO apès allumage : 0x%08X\n", *GPIO);

    *GPIO &= ~(1 << LED_PIN);

    printf("GPIO après extinction : 0x%08X\n", *GPIO);

    return 0;
}