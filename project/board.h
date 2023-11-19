#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "boarddisplay.h"

class Board {
    int boardSize;
    std::vector<std::vector<Square>> board;
    std::shared_ptr<BoardDisplay> display;
public:
    explicit Board(int size);
    void initBoard();
    friend std::ostream &operator<<(std::ostream &out, Board &b);
};

#endif
