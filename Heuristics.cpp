#include "Heuristics.h"

/**
 * @brief Heuristic::getMovementCost x and y cannot be 0 at the same time
 * @param x can only be -1, 0, 1
 * @param y can only be -1, 0, 1
 * @return if its a diagnol node returns the diagnol cost else it is a horizontal or vertical node so return that cost
 */
int Heuristic::getMovementCost(int x, int y) {
    if (x == 0 || y == 0) {
        return HORIZONTAL_OR_VERTICAL;
    }
    return DIAGNOL;
}

/**
 * @brief ManhattanHeuristic::getDistance
 * @param startPosition - current node position in map
 * @param endPosition - desired node position in map
 * @return HORIZONTAL_OR_VERTICAL movement times the absolute between the x's and y's added together
 */
int ManhattanHeuristic::getDistance(const Vec2i& startPosition, const Vec2i& endPosition) {
    return HORIZONTAL_OR_VERTICAL
           * (std::abs(startPosition.getX() - endPosition.getX())
           + std::abs(startPosition.getY() - endPosition.getY()));
}

/**
 * @brief ChebyshevHeuristic::getDistance
 * @param startPosition - current node position in map
 * @param endPosition - desired node position in map
 * @return HORIZONTAL_OR_VERTICAL movement times the max absolute between the x's and y's
 */
int ChebyshevHeuristic::getDistance(const Vec2i& startPosition, const Vec2i& endPosition) {
    return HORIZONTAL_OR_VERTICAL
           * std::max(std::abs(startPosition.getX() - endPosition.getX()),
                      std::abs(startPosition.getY() - endPosition.getY()));
}

/**
 * @brief EuclideanHeuristic::getDistance
 * @param startPosition - current node position in map
 * @param endPosition - desired node position in map
 * @return HORIZONTAL_OR_VERTICAL movement times the magnitude
 */
int EuclideanHeuristic::getDistance(const Vec2i& startPosition, const Vec2i& endPosition) {
    int deltaX = std::abs(startPosition.getX() - endPosition.getX());
    int deltaY = std::abs(startPosition.getY() - endPosition.getY());
    return HORIZONTAL_OR_VERTICAL * std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

/**
 * @brief HeuristicsFactory::getHeuristic
 * if you specify a type outside the bounds it returns manhattan by default
 * @param type
 * @return unique pointer with the heuristic depending on the type
 */
std::unique_ptr<Heuristic> HeuristicsFactory::getHeuristic(HEURISTIC_TYPE type) {
    switch (type) {
        case MANHATTAN:
            return std::unique_ptr<Heuristic>(new ManhattanHeuristic);
        case CHEBYSHEV:
            return std::unique_ptr<Heuristic>(new ChebyshevHeuristic);
        case EUCLIDEAN:
            return std::unique_ptr<Heuristic>(new EuclideanHeuristic);
        default:
            return std::unique_ptr<Heuristic>(new ManhattanHeuristic);
    }
}
