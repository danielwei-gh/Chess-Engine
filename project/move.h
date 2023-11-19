#ifndef __MOVE_H__
#define __MOVE_H__
#include "square.h"

class Move {
    Square &startSquare;
    Square &endSquare;
    std::shared_ptr<Piece> movedPiece;
    std::shared_ptr<Piece> capturedPiece;
public:
    Move(Square &start, Square &end, 
        std::shared_ptr<Piece> p1, std::shared_ptr<Piece> p2);
    Square &getStartSquare() const;
    Square &getEndSquare() const;
    std::shared_ptr<Piece> getMovedPiece() const;
    std::shared_ptr<Piece> getCapturedPiece() const;
};

#endif
