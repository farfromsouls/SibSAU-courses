#include <iostream>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <chrono>
#include "Array.cpp"

using namespace std::chrono;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    while (true) {
        int a;
        cout << "Выберите режим работы: (1) & (2): ";
        cin >> a;

        if (a == 1) {
            int len, x1, x2, method;
            string filename;
            cout << "Введите размер массива: ";
            cin >> len;
            cout << "Введите диапозон значений массива (через пробел): ";
            cin >> x1 >> x2;
            cout << "Введите метод сотрировки массива (1-включения, 2-Шелла): ";
            cin >> method;
            cout << "Введите имя файла: ";
            cin >> filename;

            simple_array<int> arr(len);
            ofstream file(filename + ".txt");

            file << "Исходный массив: ";
            for (int i=0; i<len; i++){
                float random_number = rand() % (x2-x1+1) + x1;
                arr[i] = random_number;
                file << random_number << " ";
            }
            file << endl;

            long comparisons, swaps;
            if (method == 1){
                arr.insertSort(comparisons, swaps);
            } else if (method == 2) {
                arr.shellSort(comparisons, swaps);
            }

            file << "Отсортированный массив: ";
            for (int i=0; i<len; i++){
                file << arr[i] << " ";
            }
            file.close();
            cout << "сравнения: " << comparisons << ", перестановки: "<< swaps << endl;

        } else if (a == 2) {
            int creating_type, beggin, end, step, method = 0;
            string filename;
            string result;
            cout << "Формирование элементов 1-случайное 2-упорядоченное 3-обратный порядок: ";
            cin >> creating_type;
            cout << "Напишите через пробел диапозон и шаг изменения резмеров массива: ";
            cin >> beggin >> end >> step;
            cout << "Введите метод сотрировки массива (1-включения, 2-Шелла): ";
            cin >> method;
            cout << "Введите имя файла: ";
            cin >> filename;

            ofstream file(filename + ".txt");

            for (int i = beggin; i < end; i += step) {
                simple_array<int> arr(i);
                if (creating_type == 1) {
                    for (int i2 = 0; i2 < i; i2++) {
                        arr[i2] = rand() % (1000000);
                    }
                } else if (creating_type == 2) {
                    for (int i2 = 0; i2 < i; i2++) {
                        arr[i2] = i2;
                    }
                } else if (creating_type == 3) {
                    for (int i2 = i; i2 > 0; i2--) {
                        arr[i2] = i2;
                    }
                }
                long comparisons, swaps;
                auto start = high_resolution_clock::now();
                if (method == 1){
                    arr.insertSort(comparisons, swaps);
                } else if (method == 2) {
                    arr.shellSort(comparisons, swaps);
                }
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                file << "N=" << i << " time=" << duration.count() << endl;
            }
            file.close();
        } 
    }
    return 0;
}