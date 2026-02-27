#include <iostream>
#include <locale.h>
#include "Triangle.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Triangle** arr = new Triangle*[8];
    arr[0] = new Triangle{};
    arr[1] = new Triangle{1};
    arr[2] = new Triangle{1, 2, 3};
    arr[3] = new Triangle{*arr[2]};
    arr[4] = new TriangleEq{};
    arr[5] = new TriangleEq{2};
    arr[6] = new TriangleSt{};
    arr[7] = new TriangleSt{1, 2};
    Picture test(arr, 8);

    while (true) {
        int task;
        cout << "1) Получить параметры треугольников\n"
             << "2) Фильтр по периметру\n"
             << "3) Суммарная площадь треугольников\n";
        cout << "Выберите команду: ";
        cin >> task;

        switch (task){
        case 1:
            test.params();
            break;
        case 2:
            float min;
            cout << "Введите минимальный периметр: ";
            cin >> min;
            test.getMinPerimeter(min);
            break;
        case 3:
            test.getSumSquare();
            break;
        }
    }

    for (int i = 0; i < 8; i++) {
        delete arr[i];
    }
    delete[] arr;

    return 0;
}