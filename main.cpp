#include <iostream>
#include <stack>
#include "Vec2i.h"
#include "Map.h"
#include "Astar.h"

/**
 * @brief main
 * create map from file
 * create starting position and ending position
 * create any walls needed
 * run the A* and get the route
 * print out the nodes in order of traversable
 * @return
 */
int main() {
    std::ifstream file("map.txt", std::ifstream::in);
    if (!file) {
        std::cout << "Could not open map.txt\n";
        return 1;
    }
    Map map(file);
    file.close();
    Vec2i startPosition(3, 5),
          endPosition(7, 5);
    map.setStart(startPosition);
    map.setEnd(endPosition);
    for (int i = 4; i < 7; i++) {
        map.setWall(Vec2i(5, i));
    }
    A_Star aStar;
    std::cout << "Before running A*\n" << map << std::endl;
//std::cin.get();
    auto route = aStar.findRoute(map, startPosition, endPosition);
    aStar.clear();
    std::cout << "After running A*\n" << map << std::endl;
    map.setStart(startPosition);
    map.setEnd(endPosition);
    std::cout << "Showing the start and end positions\n" << map << std::endl;
    std::cout << "Routes length: " << route.size() << std::endl;
    while (!route.empty()) {
        std::cout << *route.top();
        map.setRoute(route.top()->getPosition());
        route.pop();
    }
    std::cout << "\nShowing the route\n" << map << std::endl;
    std::cin.get();
    return 0;
}
