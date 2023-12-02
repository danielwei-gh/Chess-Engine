#include "computer.h"

ComputerPlayer::ComputerPlayer(Colour c, int level): 
    Player{c}, difficultyLevel{level} {}

Move ComputerPlayer::makeMove(const Board &board, const Move &previousMove)
{   
    // for compile purposes only, remove when merging/overwritting
    return Move();
}

PieceType ComputerPlayer::promotionPiece()
{
    return PieceType::King;
}
