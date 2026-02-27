#include <iostream>
#include <cmath>
#include "Ball.h"
using namespace std;

void Ball::input() {
    cout << "Ball name: ";
    cin >> this->name;
    cout << "Ball X: ";
    cin >> this->x;
    cout << "Ball Y: ";
    cin >> this->y;
    cout << "Ball Z: ";
    cin >> this->z;
    cout << "Ball radius: ";
    cin >> this->r;
}

void Ball::output() {
    cout << "\n\nBall name: " << this->name;
    cout << "\nBall X: " << this->x;
    cout << "\nBall Y: " << this->y;
    cout << "\nBall Z: " << this->z;
    cout << "\nBall radius: " << this->r << "\n";
}

double Ball::volume() {
    return (4.0/3.0) * M_PI * pow(this->r, 3);
}