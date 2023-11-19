#include "piece.h"

Piece::Piece(Colour c, PieceType pt): colour{c}, type{pt} {}

Colour Piece::getColour() const {
    return colour;
}

PieceType Piece::getType() const {
    return type;
}

void Piece::firstMove() {
    hasMoved = true;
}

bool Piece::isMoved() const {
    return hasMoved;
}
