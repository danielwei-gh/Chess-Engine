#ifndef __PIECE_H__
#define __PIECE_H__
#include "colour.h"
#include <string>
#include <memory>
#include <vector>

enum class PieceType { King, Queen, Bishop, Rook, Knight, Pawn };

class Piece {
    Colour colour;
    PieceType type;
    bool hasMoved = false;
protected:
    std::vector<std::vector<int>> boardVal;
public:
    Piece(Colour c, PieceType pt);

    // returns a char representation of the piece
    virtual char getSymbol() const = 0;

    // returns a unicode string representation of the piece
    virtual std::string getUnicodeSymbol() const = 0;

    virtual int getValue() const = 0;

    Colour getColour() const;
    PieceType getType() const;

    // sets hasMoved to true, used to indicate the piece has been moved
    void firstMove();

    // returns hasMoved
    bool isMoved() const;

    int getboardVal(int row, int col) const;

    virtual ~Piece() = default;
};

class King final: public Piece {
public:
    King(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
    virtual int getValue() const override;

};

class Queen final: public Piece {
public:
    Queen(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
    virtual int getValue() const override;
};

class Bishop final: public Piece {
public:
    Bishop(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
    virtual int getValue() const override;
};

class Rook final: public Piece {
public:
    Rook(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
    virtual int getValue() const override;
};

class Knight final: public Piece {
public:
    Knight(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
    virtual int getValue() const override;
};

class Pawn final: public Piece {
public:
    Pawn(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
    virtual int getValue() const override;
};

// returns a shared_ptr to a newly allocated Piece of specified Colour c
//  and PieceType type
std::shared_ptr<Piece> generatePiece(Colour c, PieceType type);

#endif
