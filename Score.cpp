#include "Score.h"

Score::Score(int G, int H) : g(G), h(H) {
    f = g + h;
}

int Score::getF() const {
    return f;
}

int Score::getG() const {
    return g;
}

int Score::getH() const {
    return h;
}

/**
 * @brief Score::setG
 * when setting G it updates F too
 * @param newG
 */
void Score::setG(int newG) {
    f -= g;
    g = newG;
    f += g;
}

std::ostream& operator<<(std::ostream& os, const Score& score) {
    os << "G: " << score.getG() << "  H: " << score.getH() << "  F: " << score.getF();
    return os;
}
