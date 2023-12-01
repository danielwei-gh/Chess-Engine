#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

class HumanPlayer final: public Player {
    // std::map<char, int> rowMap;
    // std::map<char, int> columnMap;
    std::map<std::string, std::pair<int, int>> squareMap;
public:
    explicit HumanPlayer(Colour c);

    // returns a Move by prompting the human player
    virtual Move
        makeMove(const Board &board, const Move &previousMove) override;
        
    virtual PieceType promotionPiece() override;
};

#endif
