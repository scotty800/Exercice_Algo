#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int read_adc() {
    return rand() % 1024;
}

int convert_to_temp(int adc) {
    return (adc * 5.0 / 1023.0) * 100;
}

int main() {
    int i, val;
    float temp;
    srand(time(NULL));
    for (i = 1; i < 10; i++) {
        val = read_adc();
        temp = convert_to_temp(val);
        printf("ADC=%d, Temp=%.2f C\n", val, temp);
        sleep(2);
    }

    return 0;
}