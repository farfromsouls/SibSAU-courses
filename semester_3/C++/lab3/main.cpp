#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <cmath>
#include "Triangle.h"
#include "Pentagon.h"
#include <locale.h>

// ==================== Основная программа ====================
int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8");

    try {
        std::cout << "=== Тест с треугольниками ===\n";
        TFigureArray<Triangle> triangleArray;
        
        // файл и стд
        std::ifstream triInput("triangles.txt");
        if (triInput) {
            triangleArray.readFrom(triInput);
            triInput.close();
        } else {
            std::cout << "Файл triangles.txt не найден. Введите данные для треугольников:\n";
            triangleArray.readFrom(std::cin);
        }
        
        std::cout << "До сортировки:\n";
        triangleArray.writeTo(std::cout);
        
        triangleArray.sortByPerimeter();
        std::cout << "\nПосле сортировки по периметру:\n";
        triangleArray.writeTo(std::cout);
        
        std::cout << "\n=== Тест с пятиугольниками ===\n";
        TFigureArray<Pentagon> pentagonArray;
        
        std::ifstream pentInput("pentagons.txt");
        if (pentInput) {
            pentagonArray.readFrom(pentInput);
            pentInput.close();
        } else {
            std::cout << "Файл pentagons.txt не найден. Пропускаем пятиугольники.\n";
        }
        
        // исключение
        try {
            std::cout << "Попытка доступа к несуществующему элементу...\n";
            pentagonArray[100];
        } catch (const std::out_of_range& e) {
            std::cout << "Поймано исключение: " << e.what() << "\n";
        }
        
        // конструкт копирования
        TFigureArray<Triangle> copied = triangleArray;
        std::cout << "\nКопия массива треугольников (размер: " << copied.getSize() << ")\n";
        
        // конструкт перемещения
        TFigureArray<Triangle> moved = std::move(copied);
        std::cout << "Перемещенный массив (размер: " << moved.getSize() << ")\n";
        std::cout << "Исходный массив после перемещения (размер: " << copied.getSize() << ")\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}