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
