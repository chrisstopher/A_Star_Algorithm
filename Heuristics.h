#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "Vec2i.h"

static const int DIAGNOL = 14, HORIZONTAL_OR_VERTICAL = 10;
int getMovementCost(int x, int y);
int getManhattanDistance(const Vec2i& startPosition, const Vec2i& endPosition);

#endif // HEURISTICS_H
