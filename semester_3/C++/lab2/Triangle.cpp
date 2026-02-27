#include <math.h>
#include <iostream>
#include <string>

using namespace std;

class Triangle {
protected:
    float a, b, c;
public:
    Triangle() {
        a = b = c = 1;
    }
    Triangle(int _a) {
        a = b = c = _a;
    }
    Triangle(int _a, int _b, int _c) {
        a = _a;
        b = _b;
        c = _c;
    }
    Triangle(const Triangle &t) {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    virtual ~Triangle() {};

    virtual float square() {
        float p = perimeter() / 2;
        if (a + b > c && a + c > b && b + c > a) {
            return sqrt(p * (p - a) * (p - b) * (p - c));
        } else {
            return 0;
        }
    };
    virtual float perimeter() {
        return a + b + c;
    };
    virtual string myName() {
        return "Triangle";
    };
};

class TriangleEq : public Triangle {
public:
    TriangleEq() : Triangle() {}
    TriangleEq(int a) : Triangle(a) {}
    TriangleEq(const TriangleEq &t) : Triangle(t) {}
    ~TriangleEq() {}

    float square() override {
        return (sqrt(3) * (a * a)) / 4;
    }

    float perimeter() override {
        return a * 3;
    }

    string myName() override {
        return "TriangleEq";
    }

    ostream &print(ostream &out) const {
        out << "a=" << a;
        return out;
    }

    istream &scan(istream &in) {
        if (&in == &cin) {
            cout << "Введите сторону: ";
            in >> a;
            b = c = a;
        } else {
            in >> a >> b >> c;
        }
        return in;
    }

    friend ostream &operator<<(ostream &stream, const TriangleEq &obj) {
        return obj.print(stream);
    }

    friend istream &operator>>(istream &stream, TriangleEq &obj) {
        return obj.scan(stream);
    }
};

class TriangleSt : public Triangle {
public:
    TriangleSt() : Triangle(1, 1, sqrt(2)) {}
    TriangleSt(float a, float b) : Triangle(a, b, sqrt(a * a + b * b)) {}
    TriangleSt(const TriangleSt &t) : Triangle(t.a, t.b, sqrt(t.a * t.a + t.b * t.b)) {}
    ~TriangleSt() {}

    float square() override {
        return (a * b) / 2;
    }

    float perimeter() override {
        return a + b + c;
    }

    string myName() override {
        return "TriangleSt";
    }

    ostream &print(ostream &out) const {
        out << "a=" << a << " b=" << b << " c=" << c;
        return out;
    }

    istream &scan(istream &in) {
        if (&in == &cin) {
            cout << "Введите 2 стороны: ";
            in >> a >> b;
        } else {
            in >> a >> b;
        }
        c = sqrt(a * a + b * b);
        return in;
    }

    friend ostream &operator<<(ostream &stream, const TriangleSt &obj) {
        return obj.print(stream);
    }

    friend istream &operator>>(istream &stream, TriangleSt &obj) {
        return obj.scan(stream);
    }
};

class Picture {
private:
    Triangle** arr;
    int length;
public: 
    Picture(Triangle** _arr, int _length) {
        arr = _arr;
        length = _length;
    }

    void params() const {
        for (int i = 0; i < length; i++) {
            cout << "Тип треугольника: " << arr[i]->myName() << endl;
            cout << "Периметр: " << arr[i]->perimeter() << endl;
            cout << "Площадь: " << arr[i]->square() << endl;
        }
    }

    void getMinPerimeter(float x) const {
        cout << "Треугольники с периметром >= " << x << endl;
        for (int i = 0; i < length; i++) {
            if (arr[i]->perimeter() >= x) {
                cout << i << ": " << arr[i]->perimeter() << endl;
            }
        }
    }

    void getSumSquare() const {
        float sum = 0;
        for (int i = 0; i < length; i++) {
            sum += arr[i]->square();
        }
        cout << "Сумма площадей: " << sum << endl;
    }
};