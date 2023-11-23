#ifndef __RULES_H__
#define __RULES_H__
#include "board.h"
#include "move.h"

class Rules {
    // returns true if the movement from start to end is a pseudo-legal 
    //  straight move on the board, otherwise returns false
    static bool isStraightMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);
    // returns true if the movement from start to end is a pseudo-legal 
    //  diagonal move on the board, otherwise returns false
    static bool isDiagonalMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);
    
    // returns true if (row, col) is a valid square position on the board
    static bool isValidPos(int row, int col, Board &board);

    //
    static void isAttackSquare(int row, int col, Board &board, 
                        std::shared_ptr<Piece> &piece, 
                        std::vector<std::pair<int, int>> &squares);
public:
    // returns true if the movement from start to end is a pseudo-legal 
    //  King move (excluding castling) on the board, otherwise returns false
    static bool isKingMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);

    // returns true if the movement from start to end is a pseudo-legal 
    //  Queen move on the board, otherwise returns false
    static bool isQueenMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);
    
    // returns true if the movement from start to end is a pseudo-legal 
    //  Bishop move on the board, otherwise returns false
    static bool isBishopMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);
    
    // returns true if the movement from start to end is a pseudo-legal 
    //  Rook move on the board, otherwise returns false
    static bool isRookMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);
    
    // returns true if the movement from start to end is a pseudo-legal 
    //  Knight move on the board, otherwise returns false
    static bool isKnightMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);

    // returns true if the movement from start to end is a pseudo-legal 
    //  Pawn move on the board, otherwise returns false
    static bool isPawnMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board,
                        const Move &previousMove);
    
    // returns a vector of pairs that represent the position of
    //  all the pseudo-legal attacking squares from the piece on the square
    //  with position pos
    static std::vector<std::pair<int, int>>
    allAttackingSquares(const std::pair<int, int> &pos, Board &board, 
                        const Move &previousMove);

    // returns true if castling for the King with position kingPos is possible
    //  on the board, otherwise returns false
    static bool castling(const std::pair<int, int> &kingPos, const Board &board);

    // returns true if the King with position kingPos is in check on the
    //  board, otherwise returns false
    static bool check(const std::pair<int, int> &kingPos, const Board &board);

    // returns true if the King with position kingPos is in checkmate on the
    //  board, otherwise returns false
    static bool checkmate(const std::pair<int, int> &kingPos, const Board &board);

    // returns true if there are no more legal moves on the board, otherwise 
    //  returns false
    static bool statemate(const Board &board);
};

#endif
