#include "Node.h"

Node::Node(Vec2i pos, Score scor, std::shared_ptr<Node> par)
    : position(pos), score(scor), parent(par) {
}

Vec2i& Node::getPosition() {
    return position;
}

const Vec2i& Node::getPosition() const {
    return position;
}

Score& Node::getScore() {
    return score;
}

std::shared_ptr<Node>& Node::getParent() {
    return parent;
}

void Node::setParent(const std::shared_ptr<Node>& newParent) {
    parent = newParent;
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "\n"
       << "Pos: " << node.position
       << "    Score: " << node.score
       << "    Me: " << &node
       << "    Parent: " << node.parent.get()
       << "\n";
    return os;
}


