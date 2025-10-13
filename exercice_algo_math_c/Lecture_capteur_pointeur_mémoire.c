#include <stdio.h>
#include <stdint.h>

#define SENSOR_ADDR 0X40030000

float lire_temperature(volatile uint16_t *registre) {
    uint16_t val = *registre;
    return (val * 3.3 / 1023.0) * 100;
}

int main() {
    uint16_t capteur_simule = 512;
    volatile uint16_t *CAPTEUR = &capteur_simule;

    float temperature = lire_temperature(CAPTEUR);
    printf("Température lue: %.2f C\n", temperature);

    return 0;
}