#include "move.h"

Move::Move(std::shared_ptr<Piece> p1, Square &start, Square &end,
std::shared_ptr<Piece> p2, Square &captured):
    movedPiece{p1}, startSquare{start}, endSquare{end}, 
    capturedPiece{p2}, capturedSquare{captured} {}

std::shared_ptr<Piece> Move::getMovedPiece() const {
    return movedPiece;
}

Square& Move::getStartSquare() const {
    return startSquare;
}

Square& Move::getEndSquare() const {
    return endSquare;
}

std::shared_ptr<Piece> Move::getCapturedPiece() const {
    return capturedPiece;
}

Square& Move::getCapturedSquare() const {
    return capturedSquare;
}
