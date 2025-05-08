#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Δημιουργία Πίνακα
unsigned int* createArray(int n) {
    unsigned int* array = (unsigned int*)malloc(n * sizeof(unsigned int));
    if (array == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    return array;
}

// Αρχικοποίηση με τυχαίες τιμές
void fillArrayRAND(unsigned int* p, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        p[i] = rand() % 10000;
    }
}

// Αρχικοποίηση σε αύξουσα σειρά
void fillArrayASC(unsigned int* p, int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
    }
}

// Αρχικοποίηση σε φθίνουσα σειρά
void fillArrayDESC(unsigned int* p, int n) {
    for (int i = 0; i < n; i++) {
        p[i] = n - i;
    }
}

// Αντιγραφή πίνακα
void copyArray(unsigned int* p, unsigned int* q, int n) {
    for (int i = 0; i < n; i++) {
        q[i] = p[i];
    }
}

// Εκτύπωση πίνακα
void printArray(unsigned int* p, int n) {
    for (int i = 0; i < n; i++) {
        printf("%u ", p[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    unsigned int* array1 = createArray(n);
    unsigned int* array2 = createArray(n);

    printf("\nRandom array:\n");
    fillArrayRAND(array1, n);
    printArray(array1, n);

    printf("\nAscending array:\n");
    fillArrayASC(array1, n);
    printArray(array1, n);

    printf("\nDescending array:\n");
    fillArrayDESC(array1, n);
    printArray(array1, n);

    printf("\nCopy array:\n");
    copyArray(array1, array2, n);
    printArray(array2, n);

    free(array1);
    free(array2);

    return 0;
}
