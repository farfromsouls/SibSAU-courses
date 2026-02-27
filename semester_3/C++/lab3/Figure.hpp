#ifndef FIGURE_HPP
#define FIGURE_HPP

template <typename T>
void TFigureArray<T>::reallocate(size_t new_capacity) {
    T** new_data = new T*[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template <typename T>
void TFigureArray<T>::swap(TFigureArray& other) noexcept {
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(size, other.size);
}

template <typename T>
TFigureArray<T>::TFigureArray() : data(nullptr), capacity(0), size(0) {}

template <typename T>
TFigureArray<T>::TFigureArray(const TFigureArray& other) : data(nullptr), capacity(0), size(0) {
    if (other.size > 0) {
        data = new T*[other.size];
        capacity = other.size;
        size = other.size;
        for (size_t i = 0; i < size; ++i) {
            data[i] = new T(*other.data[i]);
        }
    }
}

template <typename T>
TFigureArray<T>::TFigureArray(TFigureArray&& other) noexcept 
    : data(other.data), capacity(other.capacity), size(other.size) {
    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
}

template <typename T>
TFigureArray<T>& TFigureArray<T>::operator=(const TFigureArray& other) {
    if (this != &other) {
        TFigureArray temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
TFigureArray<T>& TFigureArray<T>::operator=(TFigureArray&& other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

template <typename T>
TFigureArray<T>::~TFigureArray() {
    clear();
}

template <typename T>
T& TFigureArray<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Индекс выходит за границы массива");
    }
    return *data[index];
}

template <typename T>
const T& TFigureArray<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Индекс выходит за границы массива");
    }
    return *data[index];
}

template <typename T>
void TFigureArray<T>::push_back(const T& figure) {
    if (size >= capacity) {
        reallocate(capacity == 0 ? 2 : capacity * 2);
    }
    data[size++] = new T(figure);
}

template <typename T>
void TFigureArray<T>::pop_back() {
    if (size > 0) {
        delete data[--size];
    }
}

template <typename T>
void TFigureArray<T>::clear() {
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    data = nullptr;
    capacity = 0;
    size = 0;
}

template <typename T>
void TFigureArray<T>::sortByPerimeter() {
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (data[j]->perimeter() > data[j + 1]->perimeter()) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

template <typename T>
void TFigureArray<T>::readFrom(std::istream& in) {
    size_t count;
    if (!(in >> count)) {
        throw std::invalid_argument("Неверный формат количества фигур");
    }
    
    clear();
    for (size_t i = 0; i < count; ++i) {
        T* figure = new T();
        try {
            figure->read(in);
            push_back(*figure);
            delete figure;
        } catch (...) {
            delete figure;
            throw;
        }
    }
}

template <typename T>
void TFigureArray<T>::writeTo(std::ostream& out) const {
    out << size << '\n';
    for (size_t i = 0; i < size; ++i) {
        data[i]->print(out);
        out << '\n';
    }
}

#endif