#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int M = 10;
    char x[M];
    
    for (int i = 0; i < M; i++) {
        x[i] = rand() % 256; 
    }
    
    char *ptr = x;
    
    printf("\nUsing pointer to print array elements:\n");
    for (int i = 0; i < M; i++) {
        printf("Value: %d, Address: %u\n", *(ptr + i), (unsigned int*)(ptr + i));
    }

    return 0;
}