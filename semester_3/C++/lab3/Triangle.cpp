#include "Triangle.h"

double Triangle::distance(const Point& a, const Point& b) const {
    return std::sqrt(
        std::pow(b.x - a.x, 2) + 
        std::pow(b.y - a.y, 2) + 
        std::pow(b.z - a.z, 2)
    );
}

double Triangle::perimeter() const {
    return distance(points[0], points[1]) + 
           distance(points[1], points[2]) + 
           distance(points[2], points[0]);
}

std::ostream& Triangle::print(std::ostream& os) const {
    for (int i = 0; i < 3; ++i) {
        os << "(" << points[i].x << ", " << points[i].y << ", " << points[i].z << ") ";
    }
    return os;
}

std::istream& Triangle::read(std::istream& is) {
    for (int i = 0; i < 3; ++i) {
        if (!(is >> points[i].x >> points[i].y >> points[i].z)) {
            throw std::invalid_argument("Неверные данные для треугольника");
        }
    }
    return is;
}