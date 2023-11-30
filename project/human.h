#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

class HumanPlayer final: public Player {
public:
    explicit HumanPlayer(Colour c);
    virtual Move makeMove(const Board &board) override;
};

#endif
