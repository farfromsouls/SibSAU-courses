#include <iostream>
using namespace std;

class Array {
private:
    int size;
    int* data;
    static int objectCount;

public:
    Array();
    explicit Array(int n, int initValue = 0);
    Array(const Array& other);
    ~Array();

    Array& operator=(const Array& other);
    Array& operator-=(const Array& other);

    int& operator[](int index);
    const int& operator[](int index) const;

    friend ostream& operator<<(ostream& os, const Array& arr);
    friend istream& operator>>(istream& is, Array& arr);

    void input();
    void output();
    int sum() const;             
    static int getObjectCount();
};

