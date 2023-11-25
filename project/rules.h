#ifndef __RULES_H__
#define __RULES_H__
#include "board.h"
#include "move.h"

class Rules {
    /*// returns true if the movement from start to end is a pseudo-legal 
    //  straight move on the board, otherwise returns false
    static bool isStraightMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);
    // returns true if the movement from start to end is a pseudo-legal 
    //  diagonal move on the board, otherwise returns false
    static bool isDiagonalMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board);
    */
    
    // returns true if (row, col) is a valid square position on the board
    static bool isValidPos(int row, int col, Board &board);

    // returns true if there is no piece on the square with position end and
    //  adds a Move to moves, otherwise if there is a piece on the square with
    //  position end, if the piece has a different colour than movedPiece, adds
    //  a Move to move and returns false, otherwise the piece has the same 
    //  colour as movedPiece, returns false and does not change moves
    static bool isPseudoLegalMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, Board &board, 
                        std::shared_ptr<Piece> &movedPiece, 
                        std::vector<Move> &moves);
    
    // adds all the straight pseudo-legal moves on the board for piece at the 
    //  square with position start 
    static void addStraightPseudoLegalMoves(const std::pair<int, int> &start, 
                        Board &board, std::shared_ptr<Piece> &piece,
                        std::vector<Move> &moves);
    
    // adds all the diagonal pseudo-legal moves on the board for piece at the 
    //  square with position start 
    static void addDiagonalPseudoLegalMoves(const std::pair<int, int> &start, 
                        Board &board, std::shared_ptr<Piece> &piece,
                        std::vector<Move> &moves);

    // returns a vector of Moves of all the pseudo-legal moves from the piece
    //  on the square with position start
    static std::vector<Move>
    generatePseudoLegalMoves(const std::pair<int, int> &start, Board &board, 
                        const Move &previousMove);

    // returns true if castling for the King with position kingPos is possible
    //  on the board, otherwise returns false
    static bool castling(const std::pair<int, int> &kingPos, const Board &board);

public:
    /*// returns true if the movement from start to end is a pseudo-legal 
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
    */

    static std::vector<Move>
    generateFullyLegalMoves(std::vector<Move> &moves, Board &board);

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
