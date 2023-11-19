#include "move.h"

Move::Move(Square &start, Square &end, 
std::shared_ptr<Piece> p1, std::shared_ptr<Piece> p2):
    startSquare{start}, endSquare{end}, movedPiece{p1}, capturedPiece{p2} {}

Square& Move::getStartSquare() const {
    return startSquare;
}

Square& Move::getEndSquare() const {
    return endSquare;
}

std::shared_ptr<Piece> Move::getMovedPiece() const {
    return movedPiece;
}

std::shared_ptr<Piece> Move::getCapturedPiece() const {
    return capturedPiece;
}
