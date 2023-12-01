#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class ComputerPlayer final: public Player {
    int difficultyLevel;

    float evalMove(const Move &move, int level) const;
public:
    ComputerPlayer(Colour c, int level);
    
    virtual Move
        makeMove(const Board &board, const Move &previousMove) override;

    virtual PieceType promotionPiece();
};

#endif
