#include "Heuristics.h"

/**
 * @brief getMovementCost x and y cannot be 0 at the same time
 * @param x can only be -1, 0, 1
 * @param y can only be -1, 0, 1
 * @return if its a diagnol node returns the diagnol cost else it is a horizontal or vertical node so return that cost
 */
int getMovementCost(int x, int y) {
    if (x == 0 || y == 0) {
        return HORIZONTAL_OR_VERTICAL;
    }
    return DIAGNOL;
}
/**
 * @brief getManhattanDistance
 * @param startPosition - current node position in map
 * @param endPosition - desired node position in map
 * @return manhattan distance between 2 points times the HORIZONTAL_OR_VERTICAL movement
 */
int getManhattanDistance(const Vec2i& startPosition, const Vec2i& endPosition) {
    return HORIZONTAL_OR_VERTICAL
           * (std::abs(startPosition.getX() - endPosition.getX())
           + std::abs(startPosition.getY() - endPosition.getY()));
}
