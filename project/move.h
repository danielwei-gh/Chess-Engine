#ifndef __MOVE_H__
#define __MOVE_H__
#include "square.h"

class Move {
    std::shared_ptr<Piece> movedPiece; // shared_ptr to the moved piece
    Square &startSquare; // Square to which the moved piece was before the move
    Square &endSquare; // Square to which the moved piece is after the move

    // shared_ptr to the captured piece if there is one,
    //  otherwise capturedPiece is a null shared_ptr
    std::shared_ptr<Piece> capturedPiece;

     // Square to which the captured piece is after the move if there is one,
     // otherwise capturedSquare is the same as endSquare (used for en passant)
    Square &capturedSquare;
public:
    Move(std::shared_ptr<Piece> p1, Square &start, Square &end,
         std::shared_ptr<Piece> p2, Square &captured);
    
    // returns a shared_ptr to movedPiece
    std::shared_ptr<Piece> getMovedPiece() const;

    // returns a reference to startSquare
    Square &getStartSquare() const;

    // returns a reference to endSquare
    Square &getEndSquare() const;

    // returns a shared_ptr to capturedPiece
    std::shared_ptr<Piece> getCapturedPiece() const;

    // returns a reference to capturedSquare
    Square &getCapturedSquare() const;
};

#endif
