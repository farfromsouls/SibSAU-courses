#include <stdio.h>
#include <stdlib.h>

int main() {
    int N = 10;
    int X[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10}; 

    int max1 = 10;
    int max2 = 10;

    for (int i = 0; i < N/2; i++) {  
        if (X[i] < max1) {
            max1 = X[i];
        }
    }

    for (int i = N/2; i < N; i++) {
        if (X[i] < max2) {
            max2 = X[i];
        }
    }

    printf("min1: %d\n", max1);
    printf("min2: %d\n", max2);

    system("pause");
}