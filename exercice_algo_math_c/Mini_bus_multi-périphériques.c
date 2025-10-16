#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void uart_send(const char* msg)
{
    printf("[UART] %s\n", msg);
}

uint8_t spi_transfer(uint8_t data)
{
    printf("[SPI] TX : 0x%02x | RX : 0x%02x\n", data, data ^ 0xFF);
    return data ^ 0xFF;
}

uint8_t i2c_read_temp()
{
    uint8_t t = 20 + (rand() % 10);
    printf("[I2C] Température lue : %d°C\n", t);
    return t;
}

int main()
{
    srand(time(NULL));
    printf("=== Démarrage du microcontroleur virtuel ===\n");

    uint8_t temp = i2c_read_temp();
    uint8_t spi_data = spi_transfer(temp);
    char msg[50];
    snprintf(msg, sizeof(msg), "Temp envoyée via SPI : 0x%02x", spi_data);
    uart_send(msg);

    printf("=== Fin de l'exécution ===\n");
    return 0;
}