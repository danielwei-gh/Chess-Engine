#include "computer.h"
#include "rules.h"

ComputerPlayer::ComputerPlayer(Colour c, int level) : 
    Player{c}, difficultyLevel{level} {};

Move ComputerPlayer::makeMove(const Board &board, const Move &previousMove) {

    // random seed for moves
    srand(time(nullptr));

    std::set<std::pair<int, int>> pieces;

    // gets current player colour
    if (getColour() == Colour::White) {
        pieces = board.getWhitePieces();
    } else {
        pieces = board.getBlackPieces();
    }
    
    std::vector<Move> moves;

    // gets all moves for all pieces for player colour
    for (std::pair<int, int> i : pieces) {
        std::vector<Move> pieceMoves = Rules::generateFullyLegalMoves(i, board, previousMove);
        moves.insert(moves.begin(), pieceMoves.begin(), pieceMoves.end());
    }
    int length = moves.size();
    if (difficultyLevel == 1) {
        int moveNum = rand() % length;
        return moves[moveNum];
    }

    // evaluation of moves with another board
    Board tempboard{board};
    std::vector<Move> bestMoves;
    int val = INT_MIN;
    for (auto i : moves) {
        int curVal = Rules::evalMove(difficultyLevel, getColour(), tempboard, i, previousMove);
        if (curVal > val) { // if the move is better, replace all moves in the vector
            bestMoves.clear();
            bestMoves.emplace_back(i);
            val = curVal;
        } else if (curVal == val) { // if the move is equal, add it to the vector
            bestMoves.emplace_back(i);
        }
    }
    
    length = bestMoves.size();
    int moveNum = rand() % length;
    return bestMoves[moveNum];
}

PieceType ComputerPlayer::promotionPiece() {
    PieceType pt = PieceType::Queen; // default promotion to queen if not level 1
    if (difficultyLevel == 1) {
        pt = static_cast<PieceType>(rand() % static_cast<int>(PieceType::Knight) + static_cast<int>(PieceType::Queen));
    }
    return pt;
}
