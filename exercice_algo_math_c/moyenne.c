#include <stdio.h>

int main() {
    int n, i;
    float somme = 0.0;

    printf("Combien de nombres ? ");
    scanf("%d", &n);

    int tab[n];

    for (i = 0; i < n; i++) 
    {
        printf("Entrez le nombre %d: ", i + 1);
        scanf("%d", &tab[i]);
        somme += tab[i];
    }

    printf("La moyenne est: %.2f\n", somme / n);
    
    return 0;
}