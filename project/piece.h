#ifndef __PIECE_H__
#define __PIECE_H__
#include "colour.h"
#include <memory>

enum class PieceType { King, Queen, Bishop, Rook, Knight, Pawn };

class Piece {
    Colour colour;
    PieceType type;
    bool hasMoved = false;
public:
    Piece(Colour c, PieceType pt);
    virtual char getSymbol() const = 0;
    virtual int getValue() const = 0;
    Colour getColour() const;
    PieceType getType() const;
    void firstMove();
    bool isMoved() const;
    virtual ~Piece() = default;
};

class King final: public Piece {
public:
    King(Colour c);
    virtual char getSymbol() const override;
    virtual int getValue() const override;
};

class Queen final: public Piece {
public:
    Queen(Colour c);
    virtual char getSymbol() const override;
    virtual int getValue() const override;
};

class Bishop final: public Piece {
public:
    Bishop(Colour c);
    virtual char getSymbol() const override;
    virtual int getValue() const override;
};

class Rook final: public Piece {
public:
    Rook(Colour c);
    virtual char getSymbol() const override;
    virtual int getValue() const override;
};

class Knight final: public Piece {
public:
    Knight(Colour c);
    virtual char getSymbol() const override;
    virtual int getValue() const override;
};

class Pawn final: public Piece {
public:
    Pawn(Colour c);
    virtual char getSymbol() const override;
    virtual int getValue() const override;
};

// returns a shared_ptr to a newly allocated Piece of specified Colour c
//  and PieceType type
std::shared_ptr<Piece> generatePiece(Colour c, PieceType type);

#endif
