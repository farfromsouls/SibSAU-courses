#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    float x = 0.0;
    do {
        float ans1 = log1p( sin(x)/pow(x, 2) );
        printf("x = %f : y = %f\n", x, ans1);
        x += 0.25;
    } while (x != 1.75);
    system("pause");
}