#include "square.h"

Square::Square(Colour colour, int r, int c): 
    colour{colour}, row{r}, column{c}, piece{nullptr} {}

Colour Square::getColour() const {
    return colour;
}

int Square::getRow() const {
    return row;
}

int Square::getColumn() const {
    return column;
}

std::shared_ptr<Piece> Square::setPiece(std::shared_ptr<Piece> newPiece) {
    std::shared_ptr<Piece> tmp = piece;
    piece = newPiece;
    notify();
    return tmp;
}

std::shared_ptr<Piece> Square::getPiece() {
    return piece;
}

void Square::notify() {
    for (auto o : observers)
        o->update(*this);
}
