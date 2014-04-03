#include "Astar.h"

/**
 * @brief A_Star::A_Star
 * Create heuristic factory
 * use the type to get the right heuristic  from the factory
 * @param type default is HeuristicsFactory::MANHATTAN
 */
A_Star::A_Star(HeuristicsFactory::HEURISTIC_TYPE type) {
    HeuristicsFactory heuristicFactory;
    heuristic = heuristicFactory.getHeuristic(type);
}

A_Star::~A_Star() {
    clear();
}

void A_Star::clear() {
    openList.clear();
    closedList.clear();
}

/**
 * @brief A_Star::findRoute
 * gets the ending node from find path function
 * creates a stack of nodes
 * walks backwards by the nodes parent
 * puts the nodes in the stack
 * @param map
 * @param startPosition - starting position in the map
 * @param endPosition - desired position
 * @return if node was found
 *           stack of routes to the desired node
 *         if node was NOT found
 *           returns the starting nodes position
 */
std::stack<std::shared_ptr<Node>> A_Star::findRoute(Map& map,
                                                    const Vec2i& startPosition,
                                                    const Vec2i& endPosition) {
    auto endNode = findPath(map, startPosition, endPosition);
    std::stack<std::shared_ptr<Node>> route;
    while (endNode->getParent().get()) {
        route.push(endNode);
        endNode = endNode->getParent();
    }
    return route;
}

/**
 * @brief A_Star::findPath
 * insert the starting position, and node with score of 0 and no parent
 * while open list is not empty
 *   get the node with the lowest F score
 *   if that node is at the ending positio node
 *     return that node
 *   take the node off of open list and put it on the closed list
 *   get the traversable nodes
 *   put them in the open list
 * find the node you are on
 * return that node
 * @param map
 * @param startPosition  - starting position in the map
 * @param endPosition - desired position in the map
 * @return if node is reachable
 *           returns that node
 *         if node is not reachable
 *           returns the starting node
 */
std::shared_ptr<Node> A_Star::findPath(Map& map,
                                     const Vec2i& startPosition,
                                     const Vec2i& endPosition) {
    openList.insert({startPosition,
                   std::shared_ptr<Node>(new Node(startPosition,
                                                  Score(0, 0),
                                                  nullptr))});
    while (!openList.empty()) {
        auto currentNode = getLowestFScoreNode();
        if (currentNode->getPosition() == endPosition) {
            return currentNode;
        }
        takeOffOpenListPutInClosedList(currentNode);
        map.setOnClosedList(currentNode->getPosition());//Make this position closed on the map
        auto traversableAdjacentNodes = getAdjacentNodesAround(map,
                                                               currentNode,
                                                               endPosition);
        for (auto& i : traversableAdjacentNodes) {
            openList.insert({i->getPosition(), i});
            map.setOnOpenList(i->getPosition());//Make this position open on the map
        }
//For debugging and seeing how A* works
//std::cout << "Closed list: " << closedList.size() << "\n";
//for (auto& i : closedList) {
//    std::cout << *i.second << "\n";
//}
//std::cout << "\n\nOpen list: " << openList.size() << "\n";
//for (auto& i : openList) {
//    std::cout << *i.second << "\n";
//}
//std::cout << map << "\n";
//std::cin.get();
    }//while open list is not empty
    //did not find the desired node
    auto startNode = closedList.find(startPosition);
    return startNode->second;
}

/**
 * @brief A_Star::getLowestFScoreNode
 * Loops through all nodes in the open list
 * finds the one with the lowest F score
 * @return the last node with the lowest F score
 */
std::shared_ptr<Node> A_Star::getLowestFScoreNode() {
    std::shared_ptr<Node> currentNode = openList.begin()->second;
    for (auto& i : openList) {
        if (i.second->getScore().getF() <= currentNode->getScore().getF()) {
            currentNode = i.second;
        }
    }
    return currentNode;
}

void A_Star::takeOffOpenListPutInClosedList(const std::shared_ptr<Node>& node) {
    openList.erase(node->getPosition());
    closedList.insert({node->getPosition(), node});
}

/**
 * @brief A_Star::getAdjacentNodesAround
 * traverses the adjacent nodes in the map
 *   if you cannot traverse it
 *     continue
 *   else
 *     create the node and put in the returning list
 * @param map
 * @param node - current node with lowest F score
 * @param endPosition - desired position in the map
 * @return traversable nodes not already in the open list
 */
std::vector<std::shared_ptr<Node>> A_Star::getAdjacentNodesAround(Map& map,
                                                                  const std::shared_ptr<Node>& node,
                                                                  const Vec2i& endPosition) {
    std::vector<std::shared_ptr<Node>> adjacentPositions;
    static const Vec2i adjacentMapPositions[] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1,  0},          {1,  0},//does not test {0, 0} that is the nodes position you are on
        {-1,  1}, {0,  1}, {1,  1},
    };
    for (auto& i : adjacentMapPositions) {
        Vec2i adjacentNodesPos(node->getPosition().getX() + i.getX(),
                               node->getPosition().getY() + i.getY());
        if (!traversableNode(map, node, adjacentNodesPos, i.getX(), i.getY())) {
            continue;
        }
        adjacentPositions.push_back(std::shared_ptr<Node>(new Node(adjacentNodesPos,
                                                                   {heuristic->getMovementCost(i.getX(), i.getY()) + node->getScore().getG(),
                                                                    heuristic->getDistance(adjacentNodesPos, endPosition)},
                                                                   node)));
    }
    return adjacentPositions;
}

/**
 * @brief A_Star::traversableNode
 * does NOT check for out of bounds in the map
 * checks if position is traversal and in the closed list
 * checks if you are cutting any corners
 * checks if node is already in openlist
 * @param map
 * @param currentNode
 * @param adjacentNodesPos
 * @param x can only be -1, 0, 1
 * @param y can only be -1, 0, 1
 * x, y cannot be 0, 0
 * @return true if traversable, false if not traversable
 */
bool A_Star::traversableNode(Map& map,
                             const std::shared_ptr<Node>& currentNode,
                             const Vec2i& adjacentNodesPos,
                             int x, int y) {
    if (!map.isTraversable(adjacentNodesPos)
        || inClosedList(adjacentNodesPos)) {
        return false;
    }
    if (cuttingCorners(map, adjacentNodesPos, x, y)) {
        return false;
    }
    auto nodeInOpenListIt = openList.find(adjacentNodesPos);
    if (nodeInOpenListIt != openList.end()) {
        reCalculateNode(currentNode, nodeInOpenListIt->second, x, y);
        return false;
    }
    return true;
}

/**
 * @brief A_Star::inClosedList
 * @param position
 * @return true if position is in closed list else false
 */
bool A_Star::inClosedList(const Vec2i& position) {
    return closedList.find(position) != closedList.end();
}

/**
 * @brief A_Star::cuttingCorners
 * Example of what this code does:
 * W = wall, T = traverser, - = traversable, # = traverser cannot traverse to there from where it is
 *  #W#
 *  -T-
 *  #W#
 *
 *  #-#
 *  WTW
 *  #-#
 *
 *  #W#
 *  WTW
 *  #W#
 *
 * If you change all the ||'s to &&'s then it would allow you to cut corners
 * but not if the node will go through 2 or more corners
 * @param map
 * @param position
 * @param x can only be -1, 0, 1
 * @param y can only be -1, 0, 1
 * x, y cannot be 0, 0
 * @return true if cutting around a corner and false if not
 */
bool A_Star::cuttingCorners(Map& map, const Vec2i& position, int x, int y) {
    if (x == -1 && y == -1) {//north west
        return (!map.isTraversable(Vec2i(position.getX(), position.getY() + 1))//below it
            || !map.isTraversable(Vec2i(position.getX() + 1, position.getY())));//to the right of it
    }
    if (x == 1 && y == -1) {//north east
        return (!map.isTraversable(Vec2i(position.getX(), position.getY() + 1))//below it
            || !map.isTraversable(Vec2i(position.getX() - 1, position.getY())));//to the left of it
    }
    if (x == -1 && y == 1) {//south west
        return (!map.isTraversable(Vec2i(position.getX(), position.getY() - 1))//above it
            || !map.isTraversable(Vec2i(position.getX() + 1, position.getY())));//to the right of it
    }
    if (x == 1 && y == 1) {//south east
       return (!map.isTraversable(Vec2i(position.getX(), position.getY() - 1))//above it
            || !map.isTraversable(Vec2i(position.getX() - 1, position.getY())));//to the left of it
    }
    return false;
}

/**
 * @brief A_Star::reCalculateNode
 * if currentNode G score + movement cost at(x, y) < node in open list G score
 *   set the node in open lists parent to the current node
 *   set the node in open lists G score to the new score
 * @param currentNode
 * @param nodeInOpenList
 * @param x can only be -1, 0, 1
 * @param y can only be -1, 0, 1
 * x, y cannot be 0, 0
 */
void A_Star::reCalculateNode(const std::shared_ptr<Node>& currentNode,
                             std::shared_ptr<Node>& nodeInOpenList,
                             int x, int y) {
    int newGScore = currentNode->getScore().getG() + heuristic->getMovementCost(x, y);
    if (newGScore < nodeInOpenList->getScore().getG()) {
        nodeInOpenList->setParent(currentNode);
        nodeInOpenList->getScore().setG(newGScore);
    }
}
