#ifndef __PIECE_H__
#define __PIECE_H__
#include "colour.h"

enum class PieceType { King, Queen, Bishop, Rook, Knight, Pawn };

class Piece {
    Colour colour;
    PieceType type;
    bool hasMoved = false;
public:
    Piece(Colour c, PieceType pt);
    virtual char getSymbol() const = 0;
    Colour getColour() const;
    PieceType getType() const;
    void firstMove();
    bool isMoved() const;
    virtual ~Piece() = default;
};

class King final: public Piece {
public:
    King(Colour c): Piece{c, PieceType::King} {}
    virtual char getSymbol() const override {
        return getColour() == Colour::White ? 'K' : 'k';
    }
};

class Queen final: public Piece {
public:
    Queen(Colour c): Piece{c, PieceType::Queen} {}
    virtual char getSymbol() const override {
        return getColour() == Colour::White ? 'Q' : 'q';
    }
};

class Bishop final: public Piece {
public:
    Bishop(Colour c): Piece{c, PieceType::Bishop} {}
    virtual char getSymbol() const override {
        return getColour() == Colour::White ? 'B' : 'b';
    }
};

class Rook final: public Piece {
public:
    Rook(Colour c): Piece{c, PieceType::Rook} {}
    virtual char getSymbol() const override {
        return getColour() == Colour::White ? 'R' : 'r';
    }
};

class Knight final: public Piece {
public:
    Knight(Colour c): Piece{c, PieceType::Knight} {}
    virtual char getSymbol() const override {
        return getColour() == Colour::White ? 'N' : 'n';
    }
};

class Pawn final: public Piece {
public:
    Pawn(Colour c): Piece{c, PieceType::Pawn} {}
    virtual char getSymbol() const override {
        return getColour() == Colour::White ? 'P' : 'p';
    }
};

#endif
