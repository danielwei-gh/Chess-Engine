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

King::King(Colour c): Piece{c, PieceType::King} {
    if (c == Colour::White) {
        boardVal = {{-30,-40,-40,-50,-50,-40,-40,-30},
                {-30,-40,-40,-50,-50,-40,-40,-30},
                {-30,-40,-40,-50,-50,-40,-40,-30},
                {-30,-40,-40,-50,-50,-40,-40,-30},
                {-20,-30,-30,-40,-40,-30,-30,-20},
                {-10,-20,-20,-20,-20,-20,-20,-10},
                {20, 20,  0,  0,  0,  0, 20, 20},
                {20, 30, 10,  0,  0, 10, 30, 20}};
    } else {
        boardVal = {{20, 30, 10,  0,  0, 10, 30, 20},
                 {20, 20,  0,  0,  0,  0, 20, 20},
                 {-10,-20,-20,-20,-20,-20,-20,-10},
                 {-20,-30,-30,-40,-40,-30,-30,-20},
                 {-30,-40,-40,-50,-50,-40,-40,-30},
                 {-30,-40,-40,-50,-50,-40,-40,-30},
                 {-30,-40,-40,-50,-50,-40,-40,-30},
                 {-30,-40,-40,-50,-50,-40,-40,-30}};
    }
}

char King::getSymbol() const {
    return getColour() == Colour::White ? 'K' : 'k';
}

std::string King::getUnicodeSymbol() const {
    return getColour() == Colour::White ? "\u265a" : "\u2654";
}
  
int King::getValue() const {
    return 20000;
}

Queen::Queen(Colour c): Piece{c, PieceType::Queen} {
    if (c == Colour::White) {
        boardVal = {{-20,-10,-10, -5, -5,-10,-10,-20},
                    {-10,  0,  0,  0,  0,  0,  0,-10},
                    {-10,  0,  5,  5,  5,  5,  0,-10},
                    {-5,  0,  5,  5,  5,  5,  0, -5},
                    {0,  0,  5,  5,  5,  5,  0, -5},
                    {-10,  5,  5,  5,  5,  5,  0,-10},
                    {-10,  0,  5,  0,  0,  0,  0,-10},
                    {-20,-10,-10, -5, -5,-10,-10,-20}};
    } else {
        boardVal = {{-20,-10,-10, -5, -5,-10,-10,-20},
                    {-10,  0,  0,  0,  0,  5,  0,-10},
                    {-10,  0,  5,  5,  5,  5,  5,-10},
                    {-5,  0,  5,  5,  5,  5,  0, 0},
                    {-5,  0,  5,  5,  5,  5,  0, -5},
                    {-10,  0,  5,  5,  5,  5,  0,-10},
                    {-10,  0,  0,  0,  0,  0,  0,-10},
                    {-20,-10,-10, -5, -5,-10,-10,-20}};
    }
}

char Queen::getSymbol() const {
    return getColour() == Colour::White ? 'Q' : 'q';
}

std::string Queen::getUnicodeSymbol() const {
    return getColour() == Colour::White ? "\u265b" : "\u2655";
}

int Queen::getValue() const {
    return 900;
}

Bishop::Bishop(Colour c): Piece{c, PieceType::Bishop} {
    if (c == Colour::White) {
        boardVal = {{-20, -10, -10, -10, -10, -10, -10, -20},
                    {-10,   0,   0,   0,   0,   0,   0, -10},
                    {-10,   0,   5,  10,  10,   5,   0, -10},
                    {-10,   5,   5,  10,  10,   5,   5, -10},
                    {-10,   0,  10,  10,  10,  10,   0, -10},
                    {-10,  10,  10,  10,  10,  10,  10, -10},
                    {-10,   5,   0,   0,   0,   0,   5, -10},
                    {-20, -10, -10, -10, -10, -10, -10, -20}};

    } else {
        boardVal = {{-20, -10, -10, -10, -10, -10, -10, -20},
                    {-10,   5,   0,   0,   0,   0,   5, -10},
                    {-10,  10,  10,  10,  10,  10,  10, -10},
                    {-10,   0,  10,  10,  10,  10,   0, -10},
                    {-10,   5,   5,  10,  10,   5,   5, -10},
                    {-10,   0,   5,  10,  10,   5,   0, -10},
                    {-10,   0,   0,   0,   0,   0,   0, -10},
                    {-20, -10, -10, -10, -10, -10, -10, -20}};
    }
}

char Bishop::getSymbol() const {
    return getColour() == Colour::White ? 'B' : 'b';
}

std::string Bishop::getUnicodeSymbol() const {
    return getColour() == Colour::White ? "\u265d" : "\u2657";
}

int Bishop::getValue() const {
    return 330;
}

Rook::Rook(Colour c): Piece{c, PieceType::Rook} {
    if (c == Colour::White) {
        boardVal = {{ 0,  0,  0,  0,  0,  0,  0,  0},
                    { 5, 10, 10, 10, 10, 10, 10,  5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    { 0,  0,  0,  5,  5,  0,  0,  0}};
    } else {
        boardVal = {{ 0,  0,  0,  5,  5,  0,  0,  0},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    { 5, 10, 10, 10, 10, 10, 10,  5},
                    { 0,  0,  0,  0,  0,  0,  0,  0}};
    }
}


char Rook::getSymbol() const {
    return getColour() == Colour::White ? 'R' : 'r';
}

std::string Rook::getUnicodeSymbol() const {
    return getColour() == Colour::White ? "\u265c" : "\u2656";
}

int Rook::getValue() const {
    return 500;
}

Knight::Knight(Colour c): Piece{c, PieceType::Knight} {
    if (c == Colour::White) {
        boardVal = {{-50,-40,-30,-30,-30,-30,-40,-50},
                    {-40,-20,  0,  0,  0,  0,-20,-40},
                    {-30,  0, 10, 15, 15, 10,  0,-30},
                    {-30,  5, 15, 20, 20, 15,  5,-30},
                    {-30,  0, 15, 20, 20, 15,  0,-30},
                    {-30,  5, 10, 15, 15, 10,  5,-30},
                    {-40,-20,  0,  5,  5,  0,-20,-40},
                    {-50,-40,-30,-30,-30,-30,-40,-50}};
    } else {
        boardVal = {{-50,-40,-30,-30,-30,-30,-40,-50},
                    {-40,-20,  0,  5,  5,  0,-20,-40},
                    {-30,  5, 15, 20, 20, 15,  5,-30},
                    {-30,  0, 15, 20, 20, 15,  0,-30},
                    {-30,  5, 15, 20, 20, 15,  5,-30},
                    {-30,  0, 15, 20, 20, 15,  0,-30},
                    {-40,-20,  0,  0,  0,  0,-20,-40},
                    {-50,-40,-30,-30,-30,-30,-40,-50}};
    }
}

char Knight::getSymbol() const {
    return getColour() == Colour::White ? 'N' : 'n';
}

std::string Knight::getUnicodeSymbol() const {
    return getColour() == Colour::White ? "\u265e" : "\u2658";
}

int Knight::getValue() const {
    return 320;
}

Pawn::Pawn(Colour c): Piece{c, PieceType::Pawn} {
    if (c == Colour::White) {
        boardVal = {{800, 800, 800, 800, 800, 800, 800, 800},
                    {50, 50, 50, 50, 50, 50, 50, 50},
                    {10, 10, 20, 30, 30, 20, 10, 10},
                    {5, 5, 10, 25, 25, 10, 5, 5},
                    {0, 0, 0, 20, 20, 0, 0, 0},
                    {5, -5, -10, 0, 0, -10, -5, 5},
                    {5, 10, 10, -20, -20, 10, 10, 5},
                    {0, 0, 0, 0, 0, 0, 0, 0}};   
    } else {
        boardVal = {{0, 0, 0, 0, 0, 0, 0, 0},
                    {5, 10, 10, -20, -20, 10, 10, 5},
                    {5, -5, -10, 0, 0, -10, -5, 5},
                    {0, 0, 0, 20, 20, 0, 0, 0},
                    {5, 5, 10, 25, 25, 10, 5, 5},
                    {10, 10, 20, 30, 30, 20, 10, 10},
                    {50, 50, 50, 50, 50, 50, 50, 50},
                    {800, 800, 800, 800, 800, 800, 800, 800}};
    }
}

char Pawn::getSymbol() const {
    return getColour() == Colour::White ? 'P' : 'p';
}

std::string Pawn::getUnicodeSymbol() const {
    return getColour() == Colour::White ? "\u265f" : "\u2659";
}

int Pawn::getValue() const {
    return 100;
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
