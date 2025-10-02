#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, i;
    bool premier = true;

    printf ("Entrer un entier: ");
    scanf("%d", &n);

    if (n <= 1) {
        premier = false;
    } else {
        for (i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                premier = false;
                break;
            }
        }
    }

    if (premier) {
        printf("%d est un nombre premier.\n", n);
    } else {
        printf("%d n'est pas un nombre premier.\n", n);
    }

    return 0;
}