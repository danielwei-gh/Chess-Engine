#ifndef __GAME_H__
#define __GAME_H__
#include "human.h"
#include "computer.h"
#include "rules.h"
#include <stack>

class Game {
    Board board;

    // unique_ptr to the first player
    std::unique_ptr<Player> player1;

    // unique_ptr to the second player
    std::unique_ptr<Player> player2;

    // keeps track of the score for white player
    double whiteScore;

    // keeps track of the score for black player
    double blackScore;

    // keeps track of the moves made throughout the game
    std::stack<Move> moveHistory;

    // returns the previous move made
    Move previousMove() const;
public:
    explicit Game(int size = 8);

    // starts the command interpreter for the chess program
    void start();
};

#endif
