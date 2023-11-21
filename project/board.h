#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "boarddisplay.h"
#include <set>

class Board {
    int boardSize;
    std::vector<std::vector<Square>> board;
    std::shared_ptr<BoardDisplay> display;

    // set of pairs which represent the position (row, column) 
    //  of all white pieces on the board
    std::set<std::pair<int, int>> whitePieces;

    // set of pairs which represent the position (row, column) 
    //  of all black pieces on the board
    std::set<std::pair<int, int>> blackPieces;

    void insertToPieces(std::pair<int, int> pos, Colour c);

    void eraseFromPieces(std::pair<int, int> pos, Colour c);
public:
    // initializes the board with squares that have no pieces
    explicit Board(int size);

    Square &getSquare(int row, int col);

    // places all needed pieces for a default chess game 
    void initBoard();

    // places a piece of PieceType p and Colour c on the board, 
    //  returns a shared_ptr to the piece that was replaced, 
    //  otherwise returns a null shared_ptr
    std::shared_ptr<Piece> placePiece(int row, int col, Colour c, PieceType p);

    // removes a piece from the board, returns a shared_ptr to the piece 
    //  that was removed, otherwise returns a null shared_ptr
    std::shared_ptr<Piece> removePiece(int row, int col);

    // outputs the board
    friend std::ostream &operator<<(std::ostream &out, Board &b);
};

#endif
