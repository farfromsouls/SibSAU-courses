#include <iostream>
using namespace std;



class Ball {
    string name;
    double x, y, z, r;
    static int objectCount;

    public:
    Ball();
    Ball(string _name, int _x, int _y, int _z, int _r);
    Ball(const Ball& other);
    ~Ball();
    Ball& operator=(const Ball& other);  
    Ball& operator*=(double scalar);     
    friend ostream& operator<<(ostream& os, const Ball& ball);
    friend istream& operator>>(istream& is, Ball& ball);
    bool operator<(double number) const; 
    void input();
    void output();
    double volume() const;
    static int getObjectCount();
};