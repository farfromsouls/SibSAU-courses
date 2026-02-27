#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

double calculateAverage(int *arr, int size) {
    if (size == 0) return 0.0;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

int main() {
    int N;
    scanf("%d", &N);
    int start = 3; 
    int K = 3; 
    int* X = (int*)malloc(N * sizeof(int));
    int Y[N-K];  

    for (int i = 0; i < N; i++) {
        X[i] = rand() % 100; 
    }
    
    printf("Original array:\n");
    printArray(X, N); 
    
    double averageBefore = calculateAverage(X, N);
    printf("Average before deletion: %.2f\n", averageBefore);
    
    if (start >= 0 && start < N && K > 0 && start + K <= N) {
        int z = 0;
        for(int i = 0; i < N; i++){
            if (i < start || i > start+K-1){
                Y[z] = X[i];
                z++;
            }
        }
    }
    
    free(X);
    printf("Array after deletion:\n");
    printArray(Y, N-K);

    double averageAfter = calculateAverage(Y, N-K);
    printf("Average after deletion: %.2f\n", averageAfter);

    return 0;
}