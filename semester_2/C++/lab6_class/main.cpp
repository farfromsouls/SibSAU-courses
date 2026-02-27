#include <iostream>
#include "Ball.h"
using namespace std;

int main(){

    Ball balls[2];

    Ball A;
    A.input();
    A.output();
    cout << A.volume() << "\n";

    Ball* b = new Ball;
    b->input();
    b->output();
    cout << b->volume();

    balls[0] = A;
    balls[1] = *b;

    return 0;
}