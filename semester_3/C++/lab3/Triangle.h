#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"

class Triangle : public Figure {
    struct Point {
        double x, y, z;
    } points[3];

    double distance(const Point& a, const Point& b) const;

public:
    Triangle() = default;
    double perimeter() const override;
    std::ostream& print(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
};

#endif