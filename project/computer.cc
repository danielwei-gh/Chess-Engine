#include "computer.h"
#include "rules.h"

float ComputerPlayer::evalMove(const Move &move, int level) const {

}

ComputerPlayer::ComputerPlayer(Colour c, int level) : 
    Player{c}, difficultyLevel{level} {};

Move ComputerPlayer::makeMove(const Board &board, const Move &previousMove) {

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
}
