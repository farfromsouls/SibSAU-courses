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

    Ball x1 = Ball();
    Ball x2 = Ball("name", 1, 2, 3, 4);
    Ball x3 = Ball(x2);
    x1.output();
    x2.output();
    x3.output();

    x2*=2.0;
    x2.output();
    x2=x3;
    x2.output();
    cout << (x2 < 5) << endl;

    cin >> x1;
    cout << x2 << endl;

    cout << Ball().getObjectCount();
    
    return 0;
}