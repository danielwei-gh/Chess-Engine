#include "move.h"

Move::Move(std::shared_ptr<Piece> movedPiece, 
    const std::pair<int, int> &startPos, 
    const std::pair<int, int> &endPos,
    std::shared_ptr<Piece> capturedPiece, 
    const std::pair<int, int> &enPassantPos, 
    std::shared_ptr<Piece> castledRook,
    const std::pair<int, int> &rookStartPos, 
    const std::pair<int, int> &rookEndPos): movedPiece{movedPiece}, 
        startPos{startPos}, endPos{endPos}, capturedPiece{capturedPiece}, 
        enPassantPos{enPassantPos}, castledRook{castledRook},
        rookStartPos{rookStartPos}, rookEndPos{rookEndPos} {}

std::ostream &operator<<(std::ostream &out, const Move &move) {
    std::map<PieceType, std::string> pieceTypeMap{
        {PieceType::King, "King"}, {PieceType::Queen, "Queen"},
        {PieceType::Bishop, "Bishop"}, {PieceType::Rook, "Rook"},
        {PieceType::Knight, "Knight"}, {PieceType::Pawn, "Pawn"}
    };
    
    std::map<Colour, std::string> colourMap{
        {Colour::White, "White"}, {Colour::Black, "Black"}
    };

    std::map<int, std::string> posRowMap{
        {0, "8"}, {1, "7"}, {2, "6"}, {3, "5"}, {4, "4"}, {5, "3"}, {6, "2"}, {7, "1"}
    };

    std::map<int, std::string> posColMap{
        {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}
    };

    if (move.movedPiece) {
        out << "Moved Piece: " << colourMap[move.movedPiece->getColour()] << " "
            << pieceTypeMap[move.movedPiece->getType()] << std::endl;
    }
    if (move.startPos.first != -1 && move.startPos.second != -1) {
        out << "Moved Piece start: " << posColMap[move.startPos.second]
            << posRowMap[move.startPos.first] << std::endl;
    }
    if (move.endPos.first != -1 && move.endPos.second != -1) {
        out << "Moved Piece end: " << posColMap[move.endPos.second]
            << posRowMap[move.endPos.first] << std::endl;
    }
    if (move.capturedPiece) {
        out << "Captured Piece: " << colourMap[move.capturedPiece->getColour()] << " "
            << pieceTypeMap[move.capturedPiece->getType()] << std::endl;
    }
    if (move.enPassantPos.first != -1 && move.enPassantPos.second != -1) {
        out << "EnPassant Captured Pawn end: " << posColMap[move.enPassantPos.second]
            << posRowMap[move.enPassantPos.first] << std::endl;
    }
    if (move.castledRook) {
        out << "Castled Rook: " << colourMap[move.castledRook->getColour()] << " "
            << pieceTypeMap[move.castledRook->getType()] << std::endl;
    }
    if (move.rookStartPos.first != -1 && move.rookStartPos.second != -1) {
        out << "Castled Rook start: " << posColMap[move.rookStartPos.second]
            << posRowMap[move.rookStartPos.first] << std::endl;
    }
    if (move.rookEndPos.first != -1 && move.rookEndPos.second != -1) {
        out << "Castled Rook end: " << posColMap[move.rookEndPos.second]
            << posRowMap[move.rookEndPos.first] << std::endl;
    }
    return out;
}
