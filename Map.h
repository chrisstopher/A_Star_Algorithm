#ifndef MAP_H
#define MAP_H

#include <fstream>
#include "Vec2i.h"
#include "Dynamic2dArray.h"

class Map {
public:
    Map(std::ifstream& ifstream);
    //is walkable terrain
    bool isTraversable(const Vec2i& position);

    char at(unsigned x, unsigned y) const;

    //All of these setters do not have anything to do with the algorithm at all
    //they are all for debugging and visualizing what the algorithm is doing
    void setOnOpenList(const Vec2i& position);
    void setOnClosedList(const Vec2i& position);
    void setStart(const Vec2i& position);
    void setEnd(const Vec2i& position);
    void setWall(const Vec2i& position);

    unsigned getWidth() const;
    unsigned getHeight() const;
private:
    //easily changable to whatever someone wants to use
    static const char START = 'S', END = 'E',
                      OPEN = '-', WALL = '#',
                      ON_OPEN_LIST = 'O', ON_CLOSED_LIST = 'X';
    Dynamic2dArray<char> map;
};

std::ostream& operator<<(std::ostream& os, const Map& map);

#endif // MAP_H
