#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>

template<typename T>
class DoubleLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d = T(), Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n) {}
    };
    Node* head;
    Node* tail;
    int size;

public:
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList& other);
    ~DoubleLinkedList();
    DoubleLinkedList& operator=(const DoubleLinkedList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    void insert_at(int pos, const T& value);
    void pop_front();
    void pop_back();
    void erase_at(int pos);
    bool find_by_value(const T& value, int& pos) const;
    T& at(int pos);
    const T& at(int pos) const;
    void print() const;
    void clear();
    bool empty() const { return size == 0; }
    int getSize() const { return size; }
    void insert_between_all(const T& value);
};

// === РЕАЛИЗАЦИЯ МЕТОДОВ ===

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    Node* cur = other.head;
    while (cur) {
        push_back(cur->data);
        cur = cur->next;
    }
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& other) {
    if (this != &other) {
        clear();
        Node* cur = other.head;
        while (cur) {
            push_back(cur->data);
            cur = cur->next;
        }
    }
    return *this;
}

template<typename T>
void DoubleLinkedList<T>::push_front(const T& value) {
    Node* newNode = new Node(value, nullptr, head);
    if (head) head->prev = newNode;
    else tail = newNode;
    head = newNode;
    size++;
}

template<typename T>
void DoubleLinkedList<T>::push_back(const T& value) {
    Node* newNode = new Node(value, tail, nullptr);
    if (tail) tail->next = newNode;
    else head = newNode;
    tail = newNode;
    size++;
}

template<typename T>
void DoubleLinkedList<T>::insert_at(int pos, const T& value) {
    if (pos < 0 || pos > size) {
        std::cout << "Ошибка: неверная позиция\n";
        return;
    }
    if (pos == 0) {
        push_front(value);
        return;
    }
    if (pos == size) {
        push_back(value);
        return;
    }
    Node* cur = head;
    for (int i = 0; i < pos; i++) cur = cur->next;
    Node* newNode = new Node(value, cur->prev, cur);
    cur->prev->next = newNode;
    cur->prev = newNode;
    size++;
}

template<typename T>
void DoubleLinkedList<T>::pop_front() {
    if (!head) {
        std::cout << "Ошибка: список пуст\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
    size--;
}

template<typename T>
void DoubleLinkedList<T>::pop_back() {
    if (!tail) {
        std::cout << "Ошибка: список пуст\n";
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete temp;
    size--;
}

template<typename T>
void DoubleLinkedList<T>::erase_at(int pos) {
    if (pos < 0 || pos >= size) {
        std::cout << "Ошибка: неверная позиция\n";
        return;
    }
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == size - 1) {
        pop_back();
        return;
    }
    Node* cur = head;
    for (int i = 0; i < pos; i++) cur = cur->next;
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
    size--;
}

template<typename T>
bool DoubleLinkedList<T>::find_by_value(const T& value, int& pos) const {
    Node* cur = head;
    pos = 0;
    while (cur) {
        if (cur->data == value) return true;
        cur = cur->next;
        pos++;
    }
    return false;
}

template<typename T>
T& DoubleLinkedList<T>::at(int pos) {
    static T dummy;
    if (pos < 0 || pos >= size) {
        std::cout << "Ошибка: неверная позиция\n";
        return dummy;
    }
    Node* cur = head;
    for (int i = 0; i < pos; i++) cur = cur->next;
    return cur->data;
}

template<typename T>
const T& DoubleLinkedList<T>::at(int pos) const {
    static T dummy;
    if (pos < 0 || pos >= size) {
        std::cout << "Ошибка: неверная позиция\n";
        return dummy;
    }
    Node* cur = head;
    for (int i = 0; i < pos; i++) cur = cur->next;
    return cur->data;
}

template<typename T>
void DoubleLinkedList<T>::print() const {
    if (!head) {
        std::cout << "Список пуст\n";
        return;
    }
    Node* cur = head;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template<typename T>
void DoubleLinkedList<T>::insert_between_all(const T& value) {
    if (size < 2) return;
    Node* cur = head;
    while (cur && cur->next) {
        Node* nextNode = cur->next;
        Node* newNode = new Node(value, cur, nextNode);
        cur->next = newNode;
        nextNode->prev = newNode;
        cur = nextNode;
        size++;
    }
}

#endif