#include <stdio.h>
#include <stdint.h>

uint8_t SPI_DR = 0;
uint8_t SPI_SR = 0x01;
uint8_t SPI_CR = 0;

void spi_init() {
    SPI_CR |= (1 << 0);
    printf("SPI initialized.\n");
}

uint8_t spi_transfer(uint8_t data)
{
    if (!(SPI_CR & 1)) return 0;

    SPI_SR &= ~1;
    SPI_DR = data;
    printf("SPI TX: 0x%02X\n", SPI_DR);

    uint8_t received = SPI_DR ^ 0xFF;
    SPI_SR |= 1;

    printf("SPI RX: 0x%02X\n", received);
    return received;
}

int main()
{
    spi_init();
    uint8_t val = spi_transfer(0xA5);
    printf("Réponse de l'esclave : 0x%02X\n", val);
    return 0;
}