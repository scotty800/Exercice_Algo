#include <stdio.h>
#include <math.h>

typedef struct Point {
    float x;
    float y;
} Point;

int main() {
    Point p1, p2;
    float distance;

    printf("Entrer x1 : ");
    scanf("%f", &p1.x);
    printf("Entrer y1 : ");
    scanf("%f", &p1.y);

    printf("Entrer x2 : ");
    scanf("%f", &p2.x);
    printf("Entrer y2 : ");
    scanf("%f", &p2.y);

    distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    
    printf("La distance est : %.2f\n", distance);

    return 0;
}

