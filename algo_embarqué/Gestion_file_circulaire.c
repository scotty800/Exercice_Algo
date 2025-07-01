#include <stdio.h>
#include <stdlib.h>

#define MAX 8

typedef struct Queue {
    char data[MAX];
    int rear;
    int front;
    int size;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(Queue *q) {
    return q->size == 0;
}

int isFull(Queue *q) {
    return q->size == MAX;
}

int enqueue(Queue *q, char val) {
    if (isFull(q)) {
        printf("Buffer plein !\n");
        return 0;
    }

    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = val;
    q->size++;
    return 1;
}

int dequeue(Queue *q, char *val) {
    if (isEmpty(q)) {
        printf("Buffer vide !\n");
        return 0;
    }

    *val = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return 1;
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Buffer vide !\n");
        return;
    }

    printf("Contenu du buffer : ");
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % MAX;
        printf("%c ", q->data[index]);
    }
    printf("\n");
}

int main() {
    Queue buffer;
    initQueue(&buffer);

    int choix;
    char c, temp;

    do {
        printf("\nMenu :\n");
        printf("1 - Ajouter un caractère\n");
        printf("2 - Retirer un caractère\n");
        printf("3 - Afficher le buffer\n");
        printf("0 - Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez un caractère à ajouter : ");
                getchar(); // consommer '\n'
                c = getchar();
                enqueue(&buffer, c);
                break;

            case 2:
                if (dequeue(&buffer, &temp))
                    printf("Caractère retiré : %c\n", temp);
                break;

            case 3:
                displayQueue(&buffer);
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide\n");
        }
    } while (choix != 0);

    return 0;
}
