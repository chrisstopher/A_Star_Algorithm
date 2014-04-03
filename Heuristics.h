#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "Vec2i.h"
#include <memory>
#include <cmath>

class Heuristic {
    public:
        int getMovementCost(int x, int y);
        virtual int getDistance(const Vec2i& startPosition, const Vec2i& endPosition) = 0;
    protected:
        enum MOVEMENT_SCORE {
            HORIZONTAL_OR_VERTICAL = 10,
            DIAGNOL = 14
        };
};

class ManhattanHeuristic : public Heuristic {
    public:
        int getDistance(const Vec2i& startPosition, const Vec2i& endPosition);
};

class ChebyshevHeuristic : public Heuristic {
    public:
        int getDistance(const Vec2i& startPosition, const Vec2i& endPosition);
};

class EuclideanHeuristic : public Heuristic {
    public:
        int getDistance(const Vec2i& startPosition, const Vec2i& endPosition);
};

class HeuristicsFactory {
    public:
        enum HEURISTIC_TYPE {
            MANHATTAN = 0,
            CHEBYSHEV,
            EUCLIDEAN
        };
        std::unique_ptr<Heuristic> getHeuristic(HEURISTIC_TYPE type);
};

#endif // HEURISTICS_H
