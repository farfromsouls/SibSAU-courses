#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure {
    struct Point {
        double x, y, z;
    } points[5];

    double distance(const Point& a, const Point& b) const;

public:
    Pentagon() = default;
    double perimeter() const override;
    std::ostream& print(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
};

#endif