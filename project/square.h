#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "subject.h"
#include "piece.h"

class Square final: public Subject {
    Colour colour;
    int row, column;
    std::shared_ptr<Piece> piece;
public:
    Square(Colour colour, int r, int c);
    ~Square() = default;
    Colour getColour() const;
    int getRow() const;
    int getColumn() const;
    
    // returns the piece replaced, if no piece exists, returns nullptr
    std::shared_ptr<Piece> setPiece(std::shared_ptr<Piece> newPiece);
    std::shared_ptr<Piece> getPiece(); // might need const
    virtual void notify() override;
};

#endif
