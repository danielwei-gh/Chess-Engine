#ifndef __RULES_H__
#define __RULES_H__
#include "board.h"
#include "move.h"

class Rules {
    
    // returns true if (row, col) is a valid square position on the board
    static bool isValidPos(int row, int col, const Board &board);

    // returns true if there is no piece on the square with position end and
    //  adds a Move to moves, otherwise if there is a piece on the square with
    //  position end, if the piece has a different colour than movedPiece, adds
    //  a Move to move and returns false, otherwise the piece has the same 
    //  colour as movedPiece, returns false and does not change moves
    static bool addPseudoLegalMove(const std::pair<int, int> &start, 
                        const std::pair<int, int> &end, const Board &board, 
                        std::shared_ptr<Piece> &movedPiece, 
                        std::vector<Move> &moves);
    
    // adds all the straight pseudo-legal moves on the board for piece at the 
    //  square with position start 
    static void addStraightPseudoLegalMoves(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &piece,
                        std::vector<Move> &moves);
    
    // adds all the diagonal pseudo-legal moves on the board for piece at the 
    //  square with position start 
    static void addDiagonalPseudoLegalMoves(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &piece,
                        std::vector<Move> &moves);
    
    // adds all standard (non-capture) moves on the board for the Pawn at the
    //  square with position start
    static void addPawnStandardMoves(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &pawn, 
                        std::vector<Move> &moves);
                        
    // adds all capture (excluding enPassant) moves on the board for the Pawn
    //  at the square with position start
    static void addPawnCaptureMoves(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &pawn, 
                        std::vector<Move> &moves);

    // adds all enPassant moves on the board for the Pawn at the square
    //  with position start
    static void addEnPassant(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &pawn, 
                        const Move &previousMove, std::vector<Move> &moves);

    // returns a vector of Moves of all the pseudo-legal moves from the piece
    //  on the square with position start
    static std::vector<Move>
    generatePseudoLegalMoves(const std::pair<int, int> &start, 
                        const Board &board, const Move &previousMove);
    
    // returns true if the square with position pos is under attack by pieces
    //  with Colour c on the board, otherwise returns false
    static bool isUnderAttack(Colour c, const std::pair<int, int> &pos, 
                        const Board &board, const Move &previousMove);

    // adds the move of castling with the left Rook on the board for the King 
    //  at the square with position start (Rules::addLeftCastling should only
    //  be called by Rules::addCastling as a subprocedure)
    static void addLeftCastling(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &king, 
                        std::vector<Move> &moves, const Move &previousMove);
    
    // adds the move of castling with the right Rook on the board for the King 
    //  at the square with position start (Rules::addRightCastling should only
    //  be called by Rules::addCastling as a subprocedure)
    static void addRightCastling(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &king, 
                        std::vector<Move> &moves, const Move &previousMove);

    // adds all castling moves on the board for the King at the square with 
    //  position start
    static void addCastling(const std::pair<int, int> &start, 
                        const Board &board, std::shared_ptr<Piece> &king, 
                        std::vector<Move> &moves, const Move &previousMove);
    
public:

    // returns a vector of Moves of all the fully legal moves from the piece
    //  on the square with position start
    static std::vector<Move>
    generateFullyLegalMoves(const std::pair<int, int> &start, 
                        const Board &board, const Move &previousMove);

    // returns true if the King of Colour c is in check on the board,
    //  otherwise returns false
    static bool check(Colour c, const Board &board, const Move &previousMove);

    // returns true if the King of Colour c is in checkmate on the board,
    //  otherwise returns false (should be called only after Rules::check 
    //  returns true)
    static bool checkmate(Colour c, const Board &board, const Move &previousMove);

    // returns true if there are no more legal moves for the player of Colour
    //  c, otherwise returns false (also returns true if the board has one of
    //  the following piece combinations: 
    //  one white King and one black King;
    //  one white King, one white Bishop/Knight, and one black King;
    //  one white King, one black King, and one black Bishop/Knight;
    //  one white King, one white Bishop/Knight, one black King, and one black Bishop/Knight)
    static bool stalemate(Colour c, const Board &board, const Move &previousMove);

    // returns a valuation for a move for a computer of colour c given level
    static float evalMove(int level, Colour c, Board &board, const Move &move, const Move &previousMove);
};

#endif
