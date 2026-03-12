#include <iostream>
#include "Array.h"
using namespace std;

int main() {
    Array arr1;
    arr1.output();
    cout << "Sum: " << arr1.sum() << "\n\n";

    Array arr2(5, 10);
    arr2.output();
    cout << "Sum: " << arr2.sum() << "\n\n";

    Array arr3 = arr2;
    arr3.output();
    cout << "Sum: " << arr3.sum() << "\n\n";

    Array arr4;
    arr4 = arr2;
    arr4.output();
    cout << "Sum: " << arr4.sum() << "\n\n";

    arr2[0] = 99;
    cout << "after arr2[0]=99:\n";
    arr2.output();
    arr3.output();
    arr4.output();

    cout << "\nenter a new array:\n";
    Array arr5;
    cin >> arr5;
    cout << "arr5: " << arr5 << "\n";

    Array a(4);
    a[0] = 2; a[1] = 5; a[2] = 3; a[3] = 7;
    Array b(3);
    b[0] = 5; b[1] = 2; b[2] = 6;

    cout << "\na: " << a << "\n";
    cout << "b: " << b << "\n";
    a -= b;
    cout << "a after a -= b: " << a << "\n";

    Array c(2);
    c[0] = 10; c[1] = 20;
    Array d(5, 1);
    cout << "\nc: " << c << "\n";
    cout << "d: " << d << "\n";
    c -= d;
    cout << "c after c -= d: " << c << "\n";

    Array e(5, 10);
    Array f(3, 2);
    cout << "\ne: " << e << "\n";
    cout << "f: " << f << "\n";
    e -= f;
    cout << "e after e -= f: " << e << "\n";

    cout << "\nhow many obj: " << Array::getObjectCount() << "\n";

    return 0;
}