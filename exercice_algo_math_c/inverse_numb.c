#include <stdio.h>

int changer(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a = 5, b = 10;

    printf("Avant l'échange : a = %d, b = %d\n", a, b);

    changer(&a, &b);

    printf("Après l'échange : a = %d, b = %d\n", a, b);

    return 0;
}