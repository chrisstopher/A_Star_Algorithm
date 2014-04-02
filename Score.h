#ifndef SCORE_H
#define SCORE_H

#include <iostream>

class Score {
public:
    Score(int G, int H);
    int getF() const;
    int getG() const;
    int getH() const;
    void setG(int newG);
private:
    int f, g, h;
};

std::ostream& operator<<(std::ostream& os, const Score& score);

#endif // SCORE_H
