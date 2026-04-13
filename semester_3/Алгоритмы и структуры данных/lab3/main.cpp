#include <iostream>
#include <string>
#include "DoubleLinkedList.h"
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    DoubleLinkedList<char> list;
    int choice;
    string text;
    char ch;
    int pos;

    while (true) {
        cout << "\n1. Построить список из текста\n";
        cout << "2. Добавить в начало\n";
        cout << "3. Добавить в конец\n";
        cout << "4. Добавить в позицию\n";
        cout << "5. Удалить из начала\n";
        cout << "6. Удалить из конца\n";
        cout << "7. Удалить из позиции\n";
        cout << "8. Найти по значению\n";
        cout << "9. Найти по номеру\n";
        cout << "10. Вывести список\n";
        cout << "11. Вставить символ между всеми узлами (задание)\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << "Введите текст: ";
                getline(cin, text);
                list.clear();
                for (int i = 0; i < text.length(); i++)
                    list.push_back(text[i]);
                cout << "Список построен.\n";
                break;
            case 2:
                cout << "Введите символ: ";
                cin >> ch;
                list.push_front(ch);
                break;
            case 3:
                cout << "Введите символ: ";
                cin >> ch;
                list.push_back(ch);
                break;
            case 4:
                cout << "Введите позицию: ";
                cin >> pos;
                cout << "Введите символ: ";
                cin >> ch;
                list.insert_at(pos, ch);
                break;
            case 5:
                list.pop_front();
                break;
            case 6:
                list.pop_back();
                break;
            case 7:
                cout << "Введите позицию: ";
                cin >> pos;
                list.erase_at(pos);
                break;
            case 8:
                cout << "Введите символ: ";
                cin >> ch;
                if (list.find_by_value(ch, pos))
                    cout << "Символ найден на позиции " << pos << endl;
                else
                    cout << "Символ не найден.\n";
                break;
            case 9:
                cout << "Введите позицию: ";
                cin >> pos;
                if (pos >= 0 && pos < list.getSize())
                    cout << "Символ: " << list.at(pos) << endl;
                else
                    cout << "Неверная позиция.\n";
                break;
            case 10:
                cout << "Список: ";
                list.print();
                break;
            case 11:
                if (list.getSize() < 2) {
                    cout << "В списке меньше двух элементов, вставка невозможна.\n";
                    break;
                }
                cout << "Введите символ для вставки между узлами: ";
                cin >> ch;
                list.insert_between_all(ch);
                cout << "Результат: ";
                list.print();
                break;
            default:
                cout << "Неверный выбор.\n";
        }
    }
    return 0;
}