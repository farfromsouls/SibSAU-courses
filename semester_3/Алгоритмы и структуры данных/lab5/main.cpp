#include <iostream>
#include <string>
#include "HashTable.h"
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    HashTable<string> ht;
    int choice;
    string filename, word;
    int comparisons;

    do {
        cout << "\nМЕНЮ\n";
        cout << "1. Загрузить таблицу из файла\n";
        cout << "2. Выгрузить таблицу в файл\n";
        cout << "3. Поиск идентификатора\n";
        cout << "4. Добавить идентификатор\n";
        cout << "5. Удалить идентификатор\n";
        cout << "6. Вывести таблицу на экран\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Имя файла: ";
                getline(cin, filename);
                if (ht.loadFromFile(filename))
                    cout << "Загружено " << ht.getElements() << " элементов.\n";
                else
                    cout << "Ошибка открытия файла.\n";
                break;
            case 2:
                cout << "Имя файла: ";
                getline(cin, filename);
                if (ht.saveToFile(filename))
                    cout << "Сохранено.\n";
                else
                    cout << "Ошибка записи.\n";
                break;
            case 3:
                cout << "Введите идентификатор: ";
                getline(cin, word);
                if (ht.find(word, comparisons))
                    cout << "Найден. Сравнений: " << comparisons << endl;
                else
                    cout << "Не найден. Сравнений: " << comparisons << endl;
                cout << "Среднее число коллизий: " << ht.avgCollisions() << endl;
                cout << "Среднее число сравнений: " << ht.avgComparisons() << endl;
                break;
            case 4:
                cout << "Введите идентификатор: ";
                getline(cin, word);
                if (ht.add(word))
                    cout << "Добавлен.\n";
                else
                    cout << "Уже есть.\n";
                break;
            case 5:
                cout << "Введите идентификатор: ";
                getline(cin, word);
                if (ht.remove(word))
                    cout << "Удалён.\n";
                else
                    cout << "Не найден.\n";
                break;
            case 6:
                if (ht.empty())
                    cout << "Таблица пуста.\n";
                else
                    ht.print();
                break;
            case 0:
                cout << "Выход.\n";
                break;
            default:
                cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}