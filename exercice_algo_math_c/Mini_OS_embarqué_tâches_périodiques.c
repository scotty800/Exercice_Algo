#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define EEPROM_SIZE 256
uint8_t EEPROM[EEPROM_SIZE];
uint8_t lead_state = 0;
int compteur = 0;

float lire_capteur() 
{
    return 20.0 + (rand() % 10);
}

void toggle_led()
{
    lead_state = !lead_state;
    if(lead_state) {
        printf("LED ON\n");
    } else {
        printf("LED OFF\n");
    }
}

void eeprom_write(uint16_t addr, uint8_t data)
{
    if (addr < EEPROM_SIZE)
    {
        EEPROM[addr] = data;
    }
}

int main()
{
    printf("Démarrage du mini OS embarqué...\n");
    srand(time(NULL));
    for (int t = 0; t < 20; t++) {
        compteur++;
        
        if (compteur % 1 == 0) {
            float temp = lire_capteur();
            printf("Lecture capteur: %.2f C\n", temp);
        }

        if (compteur % 2 == 0){
            toggle_led();
        }

        if (compteur % 5 == 0) {
            eeprom_write(t, (uint8_t)compteur);
            printf("[T3] Donnée enregistrée à l'adresse %d\n", t);
        }

        sleep(1);
    }
    return 0;
}

