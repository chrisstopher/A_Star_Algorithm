#include "Vec2i.h"

Vec2i::Vec2i(int X, int Y) : x(X), y(Y) {

}

int Vec2i::getX() const {
    return x;
}

int Vec2i::getY() const {
    return y;
}

void Vec2i::setX(int X) {
    x = X;
}

void Vec2i::setY(int Y) {
    y = Y;
}

void Vec2i::moveX(int X) {
    x += X;
}

void Vec2i::moveY(int Y) {
    y += Y;
}

bool Vec2i::operator==(const Vec2i& v) {
    return x == v.getX() && y == v.getY();
}

/**
 * @brief Vec2iComparer::operator ()
 * for the compare in std::map in A_Star
 * @param v1
 * @param v2
 * @return v1 < v2
 */
bool Vec2iComparer::operator() (const Vec2i& v1, const Vec2i& v2) {
    if (v1.getX() == v2.getX())
        return v1.getY() < v2.getY();
    return v1.getX() < v2.getX();
}

std::ostream& operator<<(std::ostream& os, const Vec2i& vec) {
    os << "X: " << vec.getX() << "    Y: " << vec.getY();
    return os;
}
