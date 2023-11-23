#include "rules.h"

bool Rules::isStraightMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board)
{
    int startRow = start.first, startCol = start.second;
    int endRow = end.first, endCol = end.second;

    int rowMovement = endRow - startRow;
    int colMovement = endCol - startCol;

    // if the movement is not a straight line or there's no movement at all,
    //  return false
    if ((rowMovement != 0 && colMovement != 0) || (rowMovement == 0 && colMovement == 0))
        return false;

    if (rowMovement == 0) {

        // gets an increment value depending on the direction of movement 
        //  in the horizontal 
        int colInc = colMovement > 0 ? 1 : -1;
        int currCol = startCol + colInc;
        while (currCol != endCol) {

            // if the path towards endCol is blocked, return false
            if (board.getSquare(startRow, currCol).getPiece())
                return false;

            // otherwise increment and keep checking
            currCol += colInc;
        }
    } else if (colMovement == 0) {

        // gets an increment value depending on the direction of movement 
        //  in the vertical 
        int rowInc = rowMovement > 0 ? 1 : -1;
        int currRow = startRow + rowInc;
        while (currRow != endRow) {

            // if the path towards endRow is blocked, return false
            if (board.getSquare(currRow, startCol).getPiece())
                return false;
            
            // otherwise increment and keep checking
            currRow += rowInc;
        }
    }
    auto movedPiece = board.getSquare(startRow, startCol).getPiece();
    auto capturePiece = board.getSquare(endRow, endCol).getPiece();

    // if the potential capture piece has the same colour as the moved piece,
    //  return false
    if (capturePiece && capturePiece->getColour() == movedPiece->getColour())
        return false;

    return true;
}

bool Rules::isDiagonalMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board)
{
    int startRow = start.first, startCol = start.second;
    int endRow = end.first, endCol = end.second;

    int rowMovement = endRow - startRow;
    int colMovement = endCol - startCol;

    // if there's no movement in either one of the horizontal or vertical
    //  direction, return false
    if (rowMovement == 0 || colMovement == 0)
        return false;
    
    // if the movement is not strictly diagonal, return false
    if (std::abs(rowMovement) != std::abs(colMovement))
        return false;

    // gets the increment values depending on the direction of movement 
    //  in the horizontal and vertical
    int rowInc = rowMovement > 0 ? 1 : -1;
    int colInc = colMovement > 0 ? 1 : -1;

    int currRow = startRow + rowInc;
    int currCol = startCol + colInc;
    while (currRow != endRow && currCol != endCol) {

        // if the path towards (endRow, endCol) is blocked, return false
        if (board.getSquare(currRow, currCol).getPiece())
            return false;
        
        // otherwise keep checking
        currRow += rowInc;
        currCol += colInc;
    }
    auto movedPiece = board.getSquare(startRow, startCol).getPiece();
    auto capturePiece = board.getSquare(endRow, endCol).getPiece();

    // if the potential capture piece has the same colour as the moved piece,
    //  return false
    if (capturePiece && capturePiece->getColour() == movedPiece->getColour())
        return false;
    
    return true;
}

bool Rules::isValidPos(int row, int col, Board &board) {
    return 0 <= row && row < board.getSize() && 0 <= col && col < board.getSize();
}

void Rules::isAttackSquare(int row, int col, Board &board, 
    std::shared_ptr<Piece> &piece, std::vector<std::pair<int, int>> &squares)
{
    if (isValidPos(row, col, board)) {
        auto capturePiece = board.getSquare(row, col).getPiece();
        if (!capturePiece || capturePiece->getColour() != piece->getColour())
            squares.emplace_back(row, col);
    }
}

bool Rules::isKingMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board)
{
    int startRow = start.first, startCol = start.second;
    int endRow = end.first, endCol = end.second;

    int rowMovement = endRow - startRow;
    int colMovement = endCol - startCol;

    // if the movement in any direction is greater than 1, return false
    if (std::abs(rowMovement) > 1 || std::abs(colMovement) > 1)
        return false;

    auto movedPiece = board.getSquare(startRow, startCol).getPiece();
    auto capturePiece = board.getSquare(endRow, endCol).getPiece();

    // if the potential capture piece has the same colour as the moved piece,
    //  return false
    if (capturePiece && capturePiece->getColour() == movedPiece->getColour())
        return false;
    
    return true;
}

bool Rules::isQueenMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board)
{
    return isStraightMove(start, end, board) || isDiagonalMove(start, end, board);
}

bool Rules::isBishopMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board)
{
    return isDiagonalMove(start, end, board);
}

bool Rules::isRookMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board)
{
    return isStraightMove(start, end, board);
}

bool Rules::isKnightMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board)
{
    int startRow = start.first, startCol = start.second;
    int endRow = end.first, endCol = end.second;
    
    int rowMovement = std::abs(endRow - startRow);
    int colMovement = std::abs(endCol - startCol);

    // if the movement is in an L-shape or inverted L-shape
    if (rowMovement == 2 && colMovement == 1 || 
        rowMovement == 1 && colMovement == 2) {
        
        auto movedPiece = board.getSquare(startRow, startCol).getPiece();
        auto capturePiece = board.getSquare(endRow, endCol).getPiece();

        // if the potential capture piece has the same colour as the moved piece,
        //  return false
        if (capturePiece && capturePiece->getColour() == movedPiece->getColour())
            return false;
        
        return true;
    }
    return false;
}

bool Rules::isPawnMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board, const Move &previousMove)
{
    int startRow = start.first, startCol = start.second;
    int endRow = end.first, endCol = end.second;
    
    int rowMovement = endRow - startRow;
    int colMovement = endCol - startCol;

    // if the movement in the horizontal direction is greater than 1,
    //  return false
    if (std::abs(colMovement) > 1)
        return false;

    auto movedPiece = board.getSquare(startRow, startCol).getPiece();

    if (movedPiece->getColour() == Colour::White) {

        // if the white pawn moved down the board, return false
        if (rowMovement == 1)
            return false;

        // if the move is a possible capture or en passant
        if (rowMovement == -1 && std::abs(colMovement) == 1) {
            auto capturePiece = board.getSquare(endRow, endCol).getPiece();

            // if there is a piece to be captured and it has the same colour
            //  as the white pawn, return false, otherwise return true if 
            //  the colour is different
            if (capturePiece) 
                return capturePiece->getColour() == Colour::White ? false : true;

            auto previousPiece = previousMove.getMovedPiece();
            int previousPieceStartRow = previousMove.getStartSquare().getRow();
            int previousPieceEndRow = previousMove.getEndSquare().getRow();
            int previousPieceEndCol = previousMove.getEndSquare().getColumn();

            // if the previous piece that moved has moved two squares down,
            //  is a pawn, and is now side by side with the white pawn, 
            //  return true (no need to check for colour difference since it
            //  is ensured that the previous piece that movedhas a different 
            //  colour than the white pawn)
            if (previousPieceEndRow - previousPieceStartRow == 2 &&
                previousPiece->getType() == PieceType::Pawn &&
                previousPieceEndCol == endCol && 
                previousPieceEndRow == startRow)
                return true;
            
            return false;
        }

        // if the move is not a capture or if the white pawn hasn't moved yet
        //  and wants to move 2 squares up, then if there is no piece on the
        //  square (endRow, endCol), return true, otherwise if there is a
        //  piece, return false
        if (rowMovement == -1 || rowMovement == -2 && !movedPiece->isMoved())
            return !board.getSquare(endRow, endCol).getPiece() ? true : false;

        return false;

    } else {

        // if the black pawn moved up the board, return false
        if (rowMovement == -1)
            return false;
        
        // if the move is a possible capture or en passant
        if (rowMovement == 1 && std::abs(colMovement) == 1) {
            auto capturePiece = board.getSquare(endRow, endCol).getPiece();

            // if there is a piece to be captured and it has the same colour
            //  as the black pawn, return false, otherwise return true if 
            //  the colour is different
            if (capturePiece)
                return capturePiece->getColour() == Colour::Black ? false : true;

            auto previousPiece = previousMove.getMovedPiece();
            int previousPieceStartRow = previousMove.getStartSquare().getRow();
            int previousPieceEndRow = previousMove.getEndSquare().getRow();
            int previousPieceEndCol = previousMove.getEndSquare().getColumn();

            // if the previous piece that moved has moved two squares up,
            //  is a pawn, and is now side by side with the black pawn, 
            //  return true (no need to check for colour difference since it
            //  is ensured that the previous piece that movedhas a different 
            //  colour than the black pawn)
            if (previousPieceEndRow - previousPieceStartRow == -2 &&
                previousPiece->getType() == PieceType::Pawn &&
                previousPieceEndCol == endCol && 
                previousPieceEndRow == startRow)
                return true;

            return false;
        }

        // if the move is not a capture or if the black pawn hasn't moved yet
        //  and wants to move 2 squares down, then if there is no piece on the
        //  square (endRow, endCol), return true, otherwise if there is a
        //  piece, return false
        if (rowMovement == 1 || rowMovement == 2 && !movedPiece->isMoved())
            return !board.getSquare(endRow, endCol).getPiece() ? true : false;

        return false;
    }
}

std::vector<std::pair<int, int>> 
Rules::allAttackingSquares(const std::pair<int, int> &pos, Board &board, 
    const Move &previousMove) 
{
    std::vector<std::pair<int, int>> squares;

    int row = pos.first, col = pos.second;
    auto piece = board.getSquare(row, col).getPiece();

    if (piece->getType() == PieceType::King) {
        isAttackSquare(row - 1, col, board, piece, squares);
        isAttackSquare(row + 1, col, board, piece, squares);
        isAttackSquare(row, col - 1, board, piece, squares);
        isAttackSquare(row, col + 1, board, piece, squares);
        isAttackSquare(row - 1, col - 1, board, piece, squares);
        isAttackSquare(row - 1, col - 1, board, piece, squares);
        isAttackSquare(row + 1, col + 1, board, piece, squares);
        isAttackSquare(row - 1, col + 1, board, piece, squares);
        isAttackSquare(row + 1, col - 1, board, piece, squares);
    }
    else if (piece->getType() == PieceType::Queen) {
        
    }
}
