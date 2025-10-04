#include <stdio.h>

long long factorielle(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorielle(n - 1);
}

int main() {
    int n;
    printf("Entrer un entier : ");
    scanf("%d", &n);

    printf("La factorielle est : %lld\n", factorielle(n));
    return 0;
}