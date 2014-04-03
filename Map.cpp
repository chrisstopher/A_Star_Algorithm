#include "Map.h"

/**
 * @brief Map::Map
 * reads in from a file
 * number of columns
 * number of rows
 * creates the map
 * reads in the values of each map position (x, y)
 * @param ifstream
 */
Map::Map(std::ifstream& ifstream) {
    unsigned rowCount, columnCount;
    ifstream >> columnCount >> rowCount;
    map.create(columnCount, rowCount);
    for (unsigned y = 0; y < getHeight(); y++) {
        for (unsigned x = 0; x < getWidth(); x++) {
            ifstream >> map(x, y);
        }
    }
}

bool Map::isTraversable(const Vec2i& position) {
    return at(position.getX(), position.getY()) != WALL;
}

char Map::at(unsigned x, unsigned y) const {
    return map(x, y);
}

unsigned Map::getWidth() const {
    return map.maxColumns();
}

unsigned Map::getHeight() const {
    return map.maxRows();
}

void Map::setOnOpenList(const Vec2i& position) {
    map(position.getX(), position.getY()) = ON_OPEN_LIST;
}

void Map::setOnClosedList(const Vec2i& position) {
    map(position.getX(), position.getY()) = ON_CLOSED_LIST;
}

void Map::setStart(const Vec2i& position) {
    map(position.getX(), position.getY()) = START;
}

void Map::setEnd(const Vec2i& position) {
    map(position.getX(), position.getY()) = END;
}

void Map::setWall(const Vec2i& position) {
    map(position.getX(), position.getY()) = WALL;
}

void Map::setRoute(const Vec2i& position) {
    map(position.getX(), position.getY()) = ROUTE;
}

/**
 * @brief operator <<
 * SCALE can only be greater than 0
 * scales how the map looks in the x and y direction
 * 1 is default
 * @param os
 * @param map
 * @return
 */
std::ostream& operator<<(std::ostream& os, const Map& map) {
    static const unsigned SCALE = 1;
    for (unsigned y = 0; y < map.getHeight(); y++) {
        for (unsigned i = 0; i < SCALE; i++) {
            for (unsigned x = 0; x < map.getWidth(); x++) {
                for (unsigned j = 0; j < SCALE; j++) {
                    os << map.at(x, y);
                }
            }
            os << std::endl;
        }
    }
    return os;
}
