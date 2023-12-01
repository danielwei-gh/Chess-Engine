#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"
#include "rules.h"
class Computer : public Player {
    int level;

    float evalMove(Move &move);
    
public:
    Computer(Colour c, int level);
    virtual Move makeMove(Board &board) override;
    int getLevel() const;
};

#endif