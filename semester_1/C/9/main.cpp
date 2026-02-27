#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findMin(int* arr, int size) {
    int min = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

double findMin(double* arr, int size) {
    double min = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    srand(time(0));

    int size = rand() % 10 + 1;
    int* intArr = (int*)malloc(size * sizeof(int));
    double* doubleArr = (double*)malloc(size * sizeof(double));

    for (int i = 0; i < size; ++i) {
        intArr[i] = rand() % 100;
        doubleArr[i] = (double)(rand() % 100) / 10;
    }

    int minInt = findMin(intArr, size);
    double minDouble = findMin(doubleArr, size);

    printf("Minimum integer value: %d\n", minInt);
    printf("Minimum double value: %.1f\n", minDouble);

    return 0;
}

