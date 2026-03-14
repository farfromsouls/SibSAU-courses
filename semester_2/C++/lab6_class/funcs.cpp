#include <iostream>
#include <cmath>
#include "Ball.h"
using namespace std;

int Ball::objectCount = 0;

Ball::Ball() {
    this->name = "name";
    this->x, this->y, this->z, this->r = 0;
    objectCount++;
}

Ball::Ball(string _name, int _x, int _y, int _z, int _r) {
    this->name = _name;
    this->x = _x;
    this->y = _y;
    this->z = _z;
    this->r = _r;
    objectCount++;
}

Ball::Ball(const Ball& other) {
    this->name = other.name;
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->r = other.r;
    objectCount++;
}

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

double Ball::volume() const {
    return (4.0/3.0) * M_PI * pow(this->r, 3);
}

Ball& Ball::operator=(const Ball& other) {
    if (this != &other) {  
        this->name = other.name;
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->r = other.r;
    }
    return *this;
}

Ball& Ball::operator*=(double scalar) {
    this->r = this->r * scalar;
    this->x = this->x * scalar;
    this->y = this->y * scalar;
    this->z = this->z * scalar;
    return *this;
}

bool Ball::operator<(double number) const {
    return volume() < number;
}

ostream& operator<<(ostream& os, const Ball& ball) {
    os << "\nname: " << ball.name;
    os << "\nxyz: (" << ball.x << ", " << ball.y << ", " << ball.z << ")";
    os << "\nr: " << ball.r;
    os << "\nv: " << ball.volume();
    return os;
}

istream& operator>>(istream& is, Ball& ball) {
    cout << "name: ";
    is >> ball.name;
    cout << "x: ";
    is >> ball.x;
    cout << "y: ";
    is >> ball.y;
    cout << "z: ";
    is >> ball.z;
    cout << "r: ";
    is >> ball.r;
    return is;
}

int Ball::getObjectCount() {
    return objectCount;
}

Ball::~Ball() {
    objectCount--;
}