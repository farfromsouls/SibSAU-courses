#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

// Узел бинарного дерева (для хранения идентификаторов в ячейке)
template<typename T>
struct BSTNode {
    T data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

// Бинарное дерево поиска (упорядоченный список с логарифмическим поиском)
template<typename T>
class BinaryTree {
private:
    BSTNode<T>* root;
    int size;

    void clear(BSTNode<T>* node) {
        if (node) { clear(node->left); clear(node->right); delete node; }
    }

    BSTNode<T>* copy(BSTNode<T>* node) {
        if (!node) return nullptr;
        BSTNode<T>* newNode = new BSTNode<T>(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    bool insert(BSTNode<T>*& node, const T& val) {
        if (!node) { node = new BSTNode<T>(val); return true; }
        if (val < node->data) return insert(node->left, val);
        if (val > node->data) return insert(node->right, val);
        return false; // уже есть
    }

    bool remove(BSTNode<T>*& node, const T& val) {
        if (!node) return false;
        if (val < node->data) return remove(node->left, val);
        if (val > node->data) return remove(node->right, val);
        // нашли
        if (!node->left && !node->right) { delete node; node = nullptr; }
        else if (!node->left) { BSTNode<T>* tmp = node; node = node->right; delete tmp; }
        else if (!node->right) { BSTNode<T>* tmp = node; node = node->left; delete tmp; }
        else {
            BSTNode<T>* minRight = node->right;
            while (minRight->left) minRight = minRight->left;
            node->data = minRight->data;
            remove(node->right, minRight->data);
        }
        return true;
    }

    bool find(BSTNode<T>* node, const T& val, int& comparisons) const {
        comparisons++;
        if (!node) return false;
        if (val == node->data) return true;
        if (val < node->data) return find(node->left, val, comparisons);
        else return find(node->right, val, comparisons);
    }

    void inorder(BSTNode<T>* node, std::ostream& os) const {
        if (node) { inorder(node->left, os); os << node->data << " "; inorder(node->right, os); }
    }

public:
    BinaryTree() : root(nullptr), size(0) {}
    BinaryTree(const BinaryTree& other) : root(nullptr), size(other.size) { root = copy(other.root); }
    ~BinaryTree() { clear(root); }
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) { clear(root); root = copy(other.root); size = other.size; }
        return *this;
    }

    bool insert(const T& val) { if (insert(root, val)) { size++; return true; } return false; }
    bool remove(const T& val) { if (remove(root, val)) { size--; return true; } return false; }
    bool find(const T& val, int& comparisons) const { return find(root, val, comparisons); }
    bool empty() const { return root == nullptr; }
    int getSize() const { return size; }
    void print(std::ostream& os) const { inorder(root, os); }
};

// Хеш-функция: метод середины квадрата
// Преобразуем строку в число (сумма кодов + сдвиги), возводим в квадрат, берём средние биты
unsigned int hashMidSquare(const std::string& key, unsigned int tableSize) {
    unsigned long long h = 0;
    for (char c : key) h = h * 31 + c;          // полиномиальный хеш
    unsigned long long square = h * h;          // квадрат
    // берём средние 32 бита (сдвиг на 16) и модуль
    unsigned int middle = (square >> 16) & 0xFFFFFFFF;
    return middle % tableSize;
}

// Шаблон хеш-таблицы (комбинированный метод: хеш + дерево)
template<typename T>
class HashTable {
private:
    BinaryTree<T>* table;      // массив деревьев
    unsigned int size;         // размер таблицы
    unsigned int elements;     // всего элементов
    unsigned long long collisions; // общее число коллизий
    unsigned long long totalComparisons; // сумма сравнений при поиске
    unsigned long long searchCount;      // количество поисков

    // вспомогательная копия
    void copyTable(const HashTable& other) {
        for (unsigned int i = 0; i < size; i++)
            table[i] = other.table[i];
    }

public:
    // конструкторы
    HashTable(unsigned int sz = 101) : size(sz), elements(0), collisions(0), totalComparisons(0), searchCount(0) {
        table = new BinaryTree<T>[size];
    }

    HashTable(const HashTable& other) : size(other.size), elements(other.elements),
        collisions(other.collisions), totalComparisons(other.totalComparisons), searchCount(other.searchCount) {
        table = new BinaryTree<T>[size];
        copyTable(other);
    }

    ~HashTable() { delete[] table; }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            delete[] table;
            size = other.size;
            elements = other.elements;
            collisions = other.collisions;
            totalComparisons = other.totalComparisons;
            searchCount = other.searchCount;
            table = new BinaryTree<T>[size];
            copyTable(other);
        }
        return *this;
    }

    // добавление
    bool add(const T& value) {
        unsigned int idx = hashMidSquare(value, size);
        bool inserted = table[idx].insert(value);
        if (inserted) {
            elements++;
            if (table[idx].getSize() > 1) collisions++; // была коллизия (уже были элементы)
        }
        return inserted;
    }

    // удаление
    bool remove(const T& value) {
        unsigned int idx = hashMidSquare(value, size);
        if (table[idx].remove(value)) {
            elements--;
            return true;
        }
        return false;
    }

    // поиск с подсчётом сравнений
    bool find(const T& value, int& comparisons) {
        unsigned int idx = hashMidSquare(value, size);
        comparisons = 0;
        bool found = table[idx].find(value, comparisons);
        totalComparisons += comparisons;
        searchCount++;
        return found;
    }

    // статистика
    double avgCollisions() const { return (elements == 0) ? 0 : (double)collisions / elements; }
    double avgComparisons() const { return (searchCount == 0) ? 0 : (double)totalComparisons / searchCount; }

    // вывод всей таблицы
    void print(std::ostream& os = std::cout) const {
        for (unsigned int i = 0; i < size; i++) {
            if (!table[i].empty()) {
                os << i << " (хеш=" << i << "): ";
                table[i].print(os);
                os << std::endl;
            }
        }
    }

    // загрузка из файла (по одному идентификатору в строке)
    bool loadFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin) return false;
        std::string line;
        while (std::getline(fin, line)) {
            if (!line.empty()) add(line);
        }
        fin.close();
        return true;
    }

    // выгрузка в файл
    bool saveToFile(const std::string& filename) const {
        std::ofstream fout(filename);
        if (!fout) return false;
        for (unsigned int i = 0; i < size; i++) {
            if (!table[i].empty()) {
                table[i].print(fout);
                fout << std::endl;
            }
        }
        fout.close();
        return true;
    }

    // очистка
    void clear() {
        delete[] table;
        table = new BinaryTree<T>[size];
        elements = 0;
        collisions = 0;
        totalComparisons = 0;
        searchCount = 0;
    }

    bool empty() const { return elements == 0; }
    unsigned int getElements() const { return elements; }
};

#endif