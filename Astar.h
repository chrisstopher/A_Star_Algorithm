#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <map>
#include <memory>
#include <stack>
#include "Node.h"
#include "Map.h"
#include "Heuristics.h"

class A_Star {
    public:
        A_Star(HeuristicsFactory::HEURISTIC_TYPE type = HeuristicsFactory::MANHATTAN);
        ~A_Star();
        void clear();
        std::stack<std::shared_ptr<Node>> findRoute(Map& map,
                                                    const Vec2i& startPosition,
                                                    const Vec2i& endPosition);
    private:
        std::map<Vec2i, std::shared_ptr<Node>, Vec2iComparer> openList;
        std::map<Vec2i, std::shared_ptr<Node>, Vec2iComparer> closedList;
        std::unique_ptr<Heuristic> heuristic;

        std::shared_ptr<Node> findPath(Map& map,
                                       const Vec2i& startPosition,
                                       const Vec2i& endPosition);

        std::shared_ptr<Node> getLowestFScoreNode();

        void takeOffOpenListPutInClosedList(const std::shared_ptr<Node>& node);

        std::vector<std::shared_ptr<Node>> getAdjacentNodesAround(Map& map,
                                                                  const std::shared_ptr<Node>& node,
                                                                  const Vec2i& endPosition);

        bool traversableNode(Map& map,
                             const std::shared_ptr<Node>& currentNode,
                             const Vec2i& adjacentNodesPos,
                             int x, int y);

        bool inClosedList(const Vec2i& position);

        bool cuttingCorners(Map& map,
                            const Vec2i& position,
                            int x, int y);

        void reCalculateNode(const std::shared_ptr<Node>& currentNode,
                             std::shared_ptr<Node>& nodeInOpenList,
                             int x, int y);
};

#endif // ASTAR_H
