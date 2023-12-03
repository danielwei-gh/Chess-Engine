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

King::King(Colour c): Piece{c, PieceType::King} {}

char King::getSymbol() const {
    return getColour() == Colour::White ? 'K' : 'k';
}

int King::getValue() const {
    return 200;
}

Queen::Queen(Colour c): Piece{c, PieceType::Queen} {}

char Queen::getSymbol() const {
    return getColour() == Colour::White ? 'Q' : 'q';
}

int Queen::getValue() const {
    return 9;
}

Bishop::Bishop(Colour c): Piece{c, PieceType::Bishop} {}

char Bishop::getSymbol() const {
    return getColour() == Colour::White ? 'B' : 'b';
}

int Bishop::getValue() const {
    return 3;
}

Rook::Rook(Colour c): Piece{c, PieceType::Rook} {}

char Rook::getSymbol() const {
    return getColour() == Colour::White ? 'R' : 'r';
}

int Rook::getValue() const {
    return 5;
}

Knight::Knight(Colour c): Piece{c, PieceType::Knight} {}

char Knight::getSymbol() const {
    return getColour() == Colour::White ? 'N' : 'n';
}

int Knight::getValue() const {
    return 3;
}

Pawn::Pawn(Colour c): Piece{c, PieceType::Pawn} {}

char Pawn::getSymbol() const {
    return getColour() == Colour::White ? 'P' : 'p';
}

int Pawn::getValue() const {
    return 1;
}

std::shared_ptr<Piece> generatePiece(Colour c, PieceType type) {
    if (type == PieceType::King)
        return std::make_shared<King>(c);

    else if (type == PieceType::Queen)
        return std::make_shared<Queen>(c);

    else if (type == PieceType::Bishop)
        return std::make_shared<Bishop>(c);

    else if (type == PieceType::Rook)
        return std::make_shared<Rook>(c);

    else if (type == PieceType::Knight)
        return std::make_shared<Knight>(c);
        
    else
        return std::make_shared<Pawn>(c);
}
