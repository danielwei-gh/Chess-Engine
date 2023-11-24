#include "move.h"

Move::Move(const std::shared_ptr<Piece> movedPiece, 
    const std::pair<int, int> &startPos, 
    const std::pair<int, int> &endPos,
    const std::shared_ptr<Piece> capturedPiece, 
    const std::pair<int, int> &enPassantPos, 
    const std::shared_ptr<Piece> castledRook,
    const std::pair<int, int> &rookStartPos, 
    const std::pair<int, int> &rookEndPos): movedPiece{movedPiece}, 
        startPos{startPos}, endPos{endPos}, capturedPiece{capturedPiece}, 
        enPassantPos{enPassantPos}, castledRook{castledRook},
        rookStartPos{rookStartPos}, rookEndPos{rookEndPos} {}
