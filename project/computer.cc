#include "computer.h"
#include "rules.h"

ComputerPlayer::ComputerPlayer(Colour c, int level) : 
    Player{c}, difficultyLevel{level} {};

Move ComputerPlayer::makeMove(const Board &board, const Move &previousMove) {

    srand(time(nullptr));

    std::set<std::pair<int, int>> pieces;
    if (getColour() == Colour::White) {
        pieces = board.getWhitePieces();
    } else {
        pieces = board.getBlackPieces();
    }
    
    std::vector<Move> moves;
    for (std::pair<int, int> i : pieces) {
        std::vector<Move> pieceMoves = Rules::generateFullyLegalMoves(i, board, previousMove);
        moves.insert(moves.begin(), pieceMoves.begin(), pieceMoves.end());
    }
    int length = moves.size();
    if (difficultyLevel == 1) {
        int moveNum = rand() % length;
        return moves[moveNum];
    }

    Board tempboard{board};
    std::vector<Move> bestMoves;
    float val = -1;
    for (auto i : moves) {
        float curVal = Rules::evalMove(difficultyLevel, getColour(), tempboard, i, previousMove);
        if (curVal > val) {
            bestMoves.clear();
            bestMoves.emplace_back(i);
            val = curVal;
        } else if (curVal == val) {
            bestMoves.emplace_back(i);
        }
    }

    length = bestMoves.size();
    int moveNum = rand() % length;
    return bestMoves[moveNum];
}

PieceType ComputerPlayer::promotionPiece() {
    PieceType pt = PieceType::Queen;
    if (difficultyLevel == 1) {
        pt = static_cast<PieceType>(rand() % static_cast<int>(PieceType::Knight) + static_cast<int>(PieceType::Queen));
    }
    return pt;
}
