#include <iostream>
#include "BinaryTree.h"
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    BinaryTree<int> tree, tree2;
    int choice, value, n;

    do {
        cout << "1. Построить дерево из последовательности\n";
        cout << "2. Добавить узел\n";
        cout << "3. Удалить узел\n";
        cout << "4. Найти узел\n";
        cout << "5. Вывести дерево\n";
        cout << "6. Сравнить два дерева\n";
        cout << "7. Присвоить одно дерево другому\n";
        cout << "8. Вывести палиндромы с уровнями (задание)\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tree = BinaryTree<int>();
                cout << "Сколько чисел? ";
                cin >> n;
                cout << "Введите числа:\n";
                for (int i = 0; i < n; i++) {
                    cin >> value;
                    tree.insert(value);
                }
                break;
            case 2:
                cout << "Значение: ";
                cin >> value;
                tree.insert(value);
                break;
            case 3:
                cout << "Что удалить: ";
                cin >> value;
                if (tree.remove(value)) cout << "Удалено.\n";
                else cout << "Не найдено.\n";
                break;
            case 4:
                cout << "Искать: ";
                cin >> value;
                if (tree.find(value)) cout << "Есть.\n";
                else cout << "Нет.\n";
                break;
            case 5:
                cout << "Дерево:\n";
                tree.printTree();
                break;
            case 6:
                if (tree == tree2) cout << "Равны.\n";
                else cout << "Не равны.\n";
                break;
            case 7:
                tree2 = tree;
                cout << "Присвоено.\n";
                break;
            case 8:
                tree.printPalindromes();
                break;
        }
    } while (choice != 0);

    return 0;
}