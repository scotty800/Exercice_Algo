#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define EEPROM_SIZE 256
uint8_t EEPROM[EEPROM_SIZE];

void eeprom_write(uint16_t addr, uint8_t data)
{
    if (addr < EEPROM_SIZE)
    {
        EEPROM[addr] = data;
    }
}

uint8_t eeprom_read(uint16_t addr)
{
    if (addr < EEPROM_SIZE)
    {
        return EEPROM[addr];
    }
    return 0xFF;
}

void eeprom_clear()
{
    memset(EEPROM, 0x00, EEPROM_SIZE);
}

int main()
{
    eeprom_clear();
    eeprom_write(10, 0x42);
    eeprom_write(11, 0x7A);

    printf("Lecture à 10 : 0x%02X\n", eeprom_read(10));
    printf("Lecture à 11 : 0x%02X\n", eeprom_read(11));

    return 0;
}