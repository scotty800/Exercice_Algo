#include <stdio.h>

int main() {
    int n, i;
    long long factorial = 1;

    printf ("Entrer un entier: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        factorial *= i;
    }
    
    printf("La factorielle est : %lld\n", factorial);
    
    return 0;
}