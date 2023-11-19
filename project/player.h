#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "colour.h"
#include "board.h"

class Player {
    Colour colour;
    double score;
public:
    explicit Player(Colour c);
    Colour getColour() const;
    void setScore(double newScore);
    double getScore() const;
    virtual std::string makeMove(Board &board) = 0;
};

#endif
