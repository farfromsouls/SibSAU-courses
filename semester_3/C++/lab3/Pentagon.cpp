#include "Pentagon.h"

double Pentagon::distance(const Point& a, const Point& b) const {
    return std::sqrt(
        std::pow(b.x - a.x, 2) + 
        std::pow(b.y - a.y, 2) + 
        std::pow(b.z - a.z, 2)
    );
}

double Pentagon::perimeter() const {
    double p = 0;
    for (int i = 0; i < 5; ++i) {
        p += distance(points[i], points[(i + 1) % 5]);
    }
    return p;
}

std::ostream& Pentagon::print(std::ostream& os) const {
    for (int i = 0; i < 5; ++i) {
        os << "(" << points[i].x << ", " << points[i].y << ", " << points[i].z << ") ";
    }
    return os;
}

std::istream& Pentagon::read(std::istream& is) {
    for (int i = 0; i < 5; ++i) {
        if (!(is >> points[i].x >> points[i].y >> points[i].z)) {
            throw std::invalid_argument("Неверные данные для пятиугольника");
        }
    }
    return is;
}