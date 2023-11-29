#ifndef __MOVE_H__
#define __MOVE_H__
#include "piece.h"
#include <memory>
#include <map>

struct Move {
    // shared_ptr that points to the moved piece (if castling occured, 
    //  movedPiece would point to the castled King)
    std::shared_ptr<Piece> movedPiece;

    // pair that represents the row and column of the Square to which
    //  the moved piece was before the move (if castling occured, startPos
    //  represents the row and column of the Square to which the castled King
    //  was before the castle)
    std::pair<int, int> startPos;

    // pair that represents the row and column of the Square to which
    //  the moved piece was after the move (if castling occured, startPos
    //  represents the row and column of the Square to which the castled King
    //  was after the castle)
    std::pair<int, int> endPos;

    // shared_ptr that points to the captured piece if there is one, otherwise
    //  capturedPiece is nullptr
    std::shared_ptr<Piece> capturedPiece;

    // pair that represents the row and column of the Square to which
    //  the captured Pawn was before the enPassant if enPassant occured,
    //  otherwise enPassantPos is (-1, -1)
    std::pair<int, int> enPassantPos;

    // shared_ptr that points the to the castled Rook if castling occured, 
    //  otherwise castledRook is nullptr
    std::shared_ptr<Piece> castledRook;

    // pair that represents the row and column of the Square to which
    //  the castled Rook was before the castling if castling occured,
    //  otherwise rookStartPos is (-1, -1)
    std::pair<int, int> rookStartPos;

    // pair that represents the row and column of the Square to which
    //  the castled Rook was after the castling if castling occured,
    //  otherwise rookStartPos is (-1, -1)
    std::pair<int, int> rookEndPos;

    // constructor for Move
    Move(std::shared_ptr<Piece> movedPiece, 
        const std::pair<int, int> &startPos, 
        const std::pair<int, int> &endPos,
        std::shared_ptr<Piece> capturedPiece = nullptr,
        const std::pair<int, int> &enPassantPos = {-1, -1},
        std::shared_ptr<Piece> castledRook = nullptr,
        const std::pair<int, int> &rookStartPos = {-1, -1},
        const std::pair<int, int> &rookEndPos = {-1, -1});
};

std::ostream &operator<<(std::ostream &out, const Move &move);

#endif
