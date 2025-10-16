#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdlib.h>


uint8_t I2C_CR = 0;
uint8_t I2C_SR = 0;
uint8_t I2C_DR = 0;

#define SENSOR_ADDR 0x50

void i2c_init()
{
    I2C_CR |= (1 << 0);
    printf("I2C initialized.\n");
}

void i2c_start()
{
    if (!(I2C_CR & 1)) return;
    {
        I2C_SR |= (1 << 0);
        printf("[I2C] START condition\n");
    }
}

void i2c_stop()
{
    if (!(I2C_CR & 1)) return;
    {
        I2C_SR &= ~(1 << 0);
        printf("[I2C] STOP condition\n");
    }
}

void i2c_write(uint8_t data)
{
    I2C_DR = data;
    printf("[I2C] Write: 0x%02X\n", data);
}

uint8_t i2c_read(uint8_t addr)
{
    if (addr == SENSOR_ADDR)
    {
        uint8_t temp = 25 + (rand() % 10);
        printf("[I2C] Lecture capteur 0x%02X: 0x%02X\n", addr, temp);
        return temp;
    }
    else
    {
        printf("[I2C] Aucun périphérique à cette adresse.\n");
        return 0xFF;
    }
}

int main()
{
    i2c_init();
    i2c_start();
    i2c_write(SENSOR_ADDR);
    i2c_write(0x01);
    uint8_t temp = i2c_read(SENSOR_ADDR);
    i2c_stop();

    return 0;
}