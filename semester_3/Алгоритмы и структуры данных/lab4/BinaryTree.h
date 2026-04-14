#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <cmath>
#include <functional>

template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& val = T(), Node* l = nullptr, Node* r = nullptr)
            : data(val), left(l), right(r) {}
    };
    Node* root;

    void copy(Node*& dest, Node* src);          // копирование
    void clear(Node* node);                     // удаление всех
    void insert(Node*& node, const T& value);   // вставка
    bool remove(Node*& node, const T& value);   // удаление
    Node* findMin(Node* node) const;            // минимальный
    bool find(Node* node, const T& value) const;
    void print(std::ostream& os, Node* node, int level) const;
    void collectPalindromes(Node* node, int level) const;

public:
    BinaryTree();                               // конструктор по умолчанию
    BinaryTree(const BinaryTree& other);        // копирования
    ~BinaryTree();                              // деструктор
    BinaryTree& operator=(const BinaryTree& other);

    void insert(const T& value);
    bool remove(const T& value);
    bool find(const T& value) const;
    bool isEmpty() const;
    void printTree() const;
    void printPalindromes() const;              // задание: палиндромы

    // перегрузка операторов
    friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
        tree.print(os, tree.root, 0);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, BinaryTree& tree) {
        T value;
        is >> value;
        tree.insert(value);
        return is;
    }
    bool operator==(const BinaryTree& other) const;
    bool operator!=(const BinaryTree& other) const { return !(*this == other); }
};

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

// копируем рекурсивно
template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) : root(nullptr) {
    copy(root, other.root);
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    clear(root);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other) {
    if (this != &other) {
        clear(root);
        copy(root, other.root);
    }
    return *this;
}

// рекурсивное копирование узлов
template<typename T>
void BinaryTree<T>::copy(Node*& dest, Node* src) {
    if (!src) { dest = nullptr; return; }
    dest = new Node(src->data);
    copy(dest->left, src->left);
    copy(dest->right, src->right);
}

// удаляем всё поддерево
template<typename T>
void BinaryTree<T>::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// вставка по правилам BST
template<typename T>
void BinaryTree<T>::insert(Node*& node, const T& value) {
    if (!node) node = new Node(value);
    else if (value < node->data) insert(node->left, value);
    else if (value > node->data) insert(node->right, value);
    // равные не добавляем
}

template<typename T>
void BinaryTree<T>::insert(const T& value) {
    insert(root, value);
}

// ищем самый левый (минимальный) узел
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

// удаление узла
template<typename T>
bool BinaryTree<T>::remove(Node*& node, const T& value) {
    if (!node) return false;
    if (value < node->data) return remove(node->left, value);
    if (value > node->data) return remove(node->right, value);
    // нашли
    if (!node->left && !node->right) { delete node; node = nullptr; }
    else if (!node->left) { Node* tmp = node; node = node->right; delete tmp; }
    else if (!node->right) { Node* tmp = node; node = node->left; delete tmp; }
    else {
        Node* minRight = findMin(node->right);
        node->data = minRight->data;
        remove(node->right, minRight->data);
    }
    return true;
}

template<typename T>
bool BinaryTree<T>::remove(const T& value) {
    return remove(root, value);
}

// поиск
template<typename T>
bool BinaryTree<T>::find(Node* node, const T& value) const {
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data) return find(node->left, value);
    return find(node->right, value);
}

template<typename T>
bool BinaryTree<T>::find(const T& value) const {
    return find(root, value);
}

template<typename T>
bool BinaryTree<T>::isEmpty() const {
    return root == nullptr;
}

// вывод дерева повёрнутым (корень по центру, правое выше)
template<typename T>
void BinaryTree<T>::print(std::ostream& os, Node* node, int level) const {
    if (node) {
        print(os, node->right, level + 1);
        for (int i = 0; i < level; i++) os << "   ";
        os << node->data << std::endl;
        print(os, node->left, level + 1);
    }
}

template<typename T>
void BinaryTree<T>::printTree() const {
    if (!root) std::cout << "Дерево пусто.\n";
    else print(std::cout, root, 0);
}

// сравниваем два дерева рекурсивно
template<typename T>
bool BinaryTree<T>::operator==(const BinaryTree& other) const {
    std::function<bool(Node*, Node*)> eq = [&](Node* a, Node* b) -> bool {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return (a->data == b->data) && eq(a->left, b->left) && eq(a->right, b->right);
    };
    return eq(root, other.root);
}

// проверка на палиндром для целых чисел
bool isPalindrome(int n) {
    int absn = std::abs(n);
    int rev = 0, orig = absn;
    while (orig > 0) {
        rev = rev * 10 + orig % 10;
        orig /= 10;
    }
    return absn == rev;
}

// собираем палиндромы обходом (левый-корень-правый)
template<typename T>
void BinaryTree<T>::collectPalindromes(Node* node, int level) const {
    if (!node) return;
    collectPalindromes(node->left, level + 1);
    if (isPalindrome(node->data))
        std::cout << node->data << " (уровень " << level << ")\n";
    collectPalindromes(node->right, level + 1);
}

template<typename T>
void BinaryTree<T>::printPalindromes() const {
    if (!root) {
        std::cout << "Дерево пусто.\n";
        return;
    }
    std::cout << "Узлы-палиндромы:\n";
    collectPalindromes(root, 1);
}

#endif