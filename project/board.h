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

    // the position of the White King on the board if there is one,
    //  otherwise the position is (-1, -1)
    std::pair<int, int> whiteKingPos;

    // the position of the Black King on the board if there is one,
    //  otherwise the position is (-1, -1)
    std::pair<int, int> blackKingPos;

    // inserts the pair (row, col) which represents the position of a piece
    //  with Colour c into one of the sets
    void insertToPieces(int row, int col, Colour c);

    // erases the pair (row, col) which represents the position of a piece
    //  with Colour c from one of the sets
    void eraseFromPieces(int row, int col, Colour c);
public:
    // initializes the board with squares that have no pieces
    explicit Board(int size);

    // returns a reference to the Square with position (row, col)
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

    // returns a reference to whitePieces
    const std::set<std::pair<int, int>> &getWhitePieces() const;

    // returns a reference to blackPieces
    const std::set<std::pair<int, int>> &getBlackPieces() const;

    const std::pair<int, int> &getWhiteKingPos() const;

    const std::pair<int, int> &getBlackKingPos() const;

    // forwards the output of the board from BoardDisplay
    friend std::ostream &operator<<(std::ostream &out, Board &b);
};

#endif
