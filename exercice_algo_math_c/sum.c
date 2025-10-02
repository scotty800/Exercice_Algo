#include <stdio.h>

int main() {
    int a, b, sum;

    printf ("Enter a integers: ");
    scanf("%d", &a);
    printf ("Enter b integers: ");
    scanf("%d", &b);

    sum = a + b;
    printf("The sum is: %d\n", sum);

    return 0;
}