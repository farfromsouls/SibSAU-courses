#include "Array.h"
#include <algorithm>
using namespace std;

int Array::objectCount = 0;

Array::Array() {
    this->size = 0;
    this->data = nullptr;
    objectCount++;
}

Array::Array(int n, int initValue) {
    this->size = n;
    this->data = new int[this->size];
    for (int i = 0; i < this->size; ++i)
        this->data[i] = initValue;
    objectCount++;
}

Array::Array(const Array& other) {
    this->size = other.size;
    this->data = new int[this->size];
    for (int i = 0; i < this->size; ++i)
        this->data[i] = other.data[i];
    objectCount++;
}

Array::~Array() {
    delete[] this->data;
    objectCount--;
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        this->data = new int[this->size];
        for (int i = 0; i < this->size; ++i)
            this->data[i] = other.data[i];
    }
    return *this;
}

Array& Array::operator-=(const Array& other) {
    int minSize = min(this->size, other.size);
    for (int i = 0; i < minSize; ++i)
        this->data[i] -= other.data[i];
    return *this;
}

ostream& operator<<(ostream& os, const Array& arr) {
    os << "[ ";
    for (int i = 0; i < arr.size; ++i)
        os << arr.data[i] << " ";
    os << "]";
    return os;
}

istream& operator>>(istream& is, Array& arr) {
    int n;
    cout << "enter size: ";
    is >> n;
    if (!is) return is;

    int* newData = new int[n];
    cout << "enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        is >> newData[i];
        if (!is) {
            delete[] newData;
            return is;
        }
    }

    delete[] arr.data;
    arr.size = n;
    arr.data = newData;
    return is;
}

void Array::input() {
    int n;
    cout << "arr size: ";
    cin >> n;
    int* newData = new int[n];
    cout << "elements: ";
    for (int i = 0; i < n; ++i)
        cin >> newData[i];

    delete[] this->data;
    this->size = n;
    this->data = newData;
}

void Array::output() {
    cout << "arr size: " << this->size << "\n";
    cout << "elements: [ ";
    for (int i = 0; i < this->size; ++i)
        cout << this->data[i] << " ";
    cout << "]\n";
}

int Array::sum() const {
    int s = 0;
    for (int i = 0; i < this->size; ++i)
        s += this->data[i];
    return s;
}

int Array::getObjectCount() {
    return objectCount;
}

int& Array::operator[](int index) {
    return this->data[index];
}

const int& Array::operator[](int index) const {
    return this->data[index];
}

