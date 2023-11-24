#ifndef __GAME_H__
#define __GAME_H__
#include "player.h"
#include "move.h"
#include <stack>

class Game {
    Board board;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    std::stack<Move> moveHistory;
    Move previousMove();
public:
    explicit Game(int size = 8);
    void start();
};

#endif
