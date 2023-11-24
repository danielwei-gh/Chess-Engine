#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "colour.h"
#include "board.h"
#include "move.h"

class Player {
    Colour colour;
    double score;
public:
    explicit Player(Colour c);
    Colour getColour() const;
    void setScore(double newScore);
    double getScore() const;
    virtual Move makeMove(Board &board) = 0;
};

#endif
