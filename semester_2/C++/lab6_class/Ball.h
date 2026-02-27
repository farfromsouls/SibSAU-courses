#include <iostream>
using namespace std;

class Ball {
    string name;
    double x, y, z, r;

    public:
    void input();
    void output();
    double volume();
};