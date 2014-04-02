#ifndef NODE_H
#define NODE_H

#include <memory>
#include "Score.h"
#include "Vec2i.h"

class Node {
public:
    Node(Vec2i pos, Score scor, std::shared_ptr<Node> par);
    Vec2i& getPosition();
    const Vec2i& getPosition() const;
    Score& getScore();
    void setParent(const std::shared_ptr<Node>& newParent);
    std::shared_ptr<Node>& getParent();

    friend std::ostream& operator<<(std::ostream& os, const Node& node);
private:
    Vec2i position;
    Score score;
    std::shared_ptr<Node> parent;
    friend void swap(Node& node1, Node& node2);
};

#endif // NODE_H
