#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <cmath>

class Figure {
public:
    virtual double perimeter() const = 0;
    virtual ~Figure() = default;
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
};

template <typename T>
class TFigureArray {
    T** data;
    size_t capacity;
    size_t size;

    void reallocate(size_t new_capacity);
    void swap(TFigureArray& other) noexcept;

public:
    TFigureArray();
    TFigureArray(const TFigureArray& other);
    TFigureArray(TFigureArray&& other) noexcept;
    TFigureArray& operator=(const TFigureArray& other);
    TFigureArray& operator=(TFigureArray&& other) noexcept;
    ~TFigureArray();

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void push_back(const T& figure);
    void pop_back();
    void clear();
    void sortByPerimeter();
    void readFrom(std::istream& in);
    void writeTo(std::ostream& out) const;
};
#include "Figure.hpp"

#endif