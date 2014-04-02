#ifndef VEC2I_H
#define VEC2I_H

#include <iostream>

class Vec2i {
public:
    Vec2i(int X = 0, int Y = 0);
    int getX() const;
    int getY() const;
    void setX(int X);
    void setY(int Y);
    void moveX(int X);
    void moveY(int Y);
    bool operator==(const Vec2i& v);
private:
    int x, y;
};

struct Vec2iComparer {
    bool operator() (const Vec2i& v1, const Vec2i& v2);
};

std::ostream& operator<<(std::ostream& os, const Vec2i& vec);

#endif // VEC2I_H
