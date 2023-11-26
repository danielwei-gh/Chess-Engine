#include "rules.h"

bool Rules::isValidPos(int row, int col, Board &board) {
    return 0 <= row && row < board.getSize() && 0 <= col && col < board.getSize();
}

bool Rules::addPseudoLegalMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, Board &board, 
    std::shared_ptr<Piece> &movedPiece, std::vector<Move> &moves)
{
    // if end is a valid square position on the board
    if (isValidPos(end.first, end.second, board)) {
        auto capturedPiece = board.getSquare(end.first, end.second).getPiece();

        // if there is no piece on the square with position end, adds to Move
        //  and return true
        if (!capturedPiece) {
            moves.emplace_back(movedPiece, start, end);
            return true;
        }

        // if the piece on the square with position end has a different colour
        //  than movedPiece, adds to Move and return false
        if (capturedPiece->getColour() != movedPiece->getColour()) {
            moves.emplace_back(movedPiece, start, end, capturedPiece);
            return false;
        }

        // otherwise the the piece on the square with position end has the same
        //  colour as movedPiece, so only return false
        return false;
    }
    return false;
}

void Rules::addStraightPseudoLegalMoves(const std::pair<int, int> &start, 
    Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    int boardSize = board.getSize();

    // adds all the horizontal pseudo-legal moves
    for (int i = col + 1; i < boardSize; ++i) {
        if (!addPseudoLegalMove(start, {row, i}, board, piece, moves))
            break;
    }
    for (int i = col - 1; i >= 0; --i) {
        if (!addPseudoLegalMove(start, {row, i}, board, piece, moves))
            break;
    }

    // adds all the vertical pseudo-legal moves
    for (int i = row + 1; i < boardSize; ++i) {
        if (!addPseudoLegalMove(start, {i, col}, board, piece, moves))
            break;
    }
    for (int i = row - 1; i >= 0; ++i) {
        if (!addPseudoLegalMove(start, {i, col}, board, piece, moves))
            break;
    }
}

void Rules::addDiagonalPseudoLegalMoves(const std::pair<int, int> &start, 
    Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    int boardSize = board.getSize();

    for (int i = row + 1, j = col + 1; i < boardSize && j < boardSize; ++i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < boardSize; --i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row + 1, j = col - 1; i < boardSize && j >= 0; ++i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
}

void Rules::addPawnStandardMoves(const std::pair<int, int> &start, 
    Board &board, std::shared_ptr<Piece> &pawn, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;

    // gets an increment value based on the Pawn's colour
    int rowInc = pawn->getColour() == Colour::White ? -1 : 1;

    // determines if the Pawn's standard move is pseudo-legal
    if (isValidPos(row + rowInc, col, board)) {
        auto piece1 = board.getSquare(row + rowInc, col).getPiece();
        
        // if there is no piece on the square with position (row + rowInc, col)
        if (!piece1) {
            moves.emplace_back(pawn, start, 
                std::pair<int, int>{row + rowInc, col});
            
            // if the Pawn hasn't moved yet
            if (isValidPos(row + rowInc * 2, col, board) && !pawn->isMoved()) {
                auto piece2 = board.getSquare(row + rowInc * 2, col).getPiece();

                // if there is no piece on the square with position
                //  (row + rowInc * 2, col)
                if (!piece2) 
                    moves.emplace_back(pawn, start, 
                        std::pair<int, int>{row + rowInc * 2, col});
            }
        }
    }
}

void Rules::addPawnCaptureMoves(const std::pair<int, int> &start, 
    Board &board, std::shared_ptr<Piece> &pawn, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;

    // gets an increment value based on the Pawn's colour
    int rowInc = pawn->getColour() == Colour::White ? -1 : 1;

    // if the Pawn's left capture move is a valid square position
    if (isValidPos(row + rowInc, col - 1, board)) {
        auto capturePiece = board.getSquare(row + rowInc, col - 1).getPiece();

        // if there is a piece on the square with position
        //  (row + rowInc, col - 1) and that piece has a different colour
        //  than the Pawn
        if (capturePiece && capturePiece->getColour() != pawn->getColour())
            moves.emplace_back(pawn, start, 
                std::pair<int, int>{row + rowInc, col - 1}, capturePiece);
    }

    // if the Pawn's right capture move is a valid square position
    if (isValidPos(row + rowInc, col + 1, board)) {
        auto capturePiece = board.getSquare(row + rowInc, col + 1).getPiece();

        // if there is a piece on the square with position
        //  (row + rowInc, col + 1) and that piece has a different colour
        //  than the Pawn
        if (capturePiece && capturePiece->getColour() != pawn->getColour())
            moves.emplace_back(pawn, start, 
                std::pair<int, int>{row + rowInc, col + 1}, capturePiece);
    }
}

void Rules::addEnPassant(const std::pair<int, int> &start, Board &board, 
    std::shared_ptr<Piece> &pawn, const Move &previousMove, 
    std::vector<Move> &moves)
{
    int row = start.first, col = start.second;

    // gets an increment value based on the Pawn's colour
    int rowInc = pawn->getColour() == Colour::White ? -1 : 1;

    auto previousPiece = previousMove.movedPiece;

    int previousPieceStartRow = previousMove.startPos.first;
    int previousPieceEndRow = previousMove.endPos.first;
    int previousPieceEndCol = previousMove.endPos.second;

    // if previousPiece is a Pawn AND if the colour of previousPiece is
    //  different than the colour of pawn AND if previousPiece moved 2
    //  squares vertically AND if previousPiece is now on the same row as
    //  pawn AND if previousPiece is now on the column right next to the
    //  the column that pawn is on
    if (previousPiece->getType() == PieceType::Pawn &&
        previousPiece->getColour() != pawn->getColour() &&
        std::abs(previousPieceEndRow - previousPieceStartRow) == 2 &&
        previousPieceEndRow == row && 
        std::abs(previousPieceEndCol - col) == 1) {
        
        // gets an increment value based on whether previousPiece is to the
        //  right or left of pawn (colInc is either -1 or 1)
        int colInc = previousPieceEndCol - col;
        moves.emplace_back(pawn, start, 
            std::pair<int, int>{row + rowInc, col + colInc}, previousPiece,
            previousMove.endPos);
    }
}

std::vector<Move> 
Rules::generatePseudoLegalMoves(const std::pair<int, int> &start, Board &board, 
    const Move &previousMove)
{
    std::vector<Move> moves;

    int row = start.first, col = start.second;
    auto piece = board.getSquare(row, col).getPiece();

    if (piece->getType() == PieceType::King) {
        addPseudoLegalMove(start, {row - 1, col}, board, piece, moves);
        addPseudoLegalMove(start, {row + 1, col}, board, piece, moves);
        addPseudoLegalMove(start, {row, col - 1}, board, piece, moves);
        addPseudoLegalMove(start, {row, col + 1}, board, piece, moves);
        addPseudoLegalMove(start, {row - 1, col - 1}, board, piece, moves);
        addPseudoLegalMove(start, {row + 1, col + 1}, board, piece, moves);
        addPseudoLegalMove(start, {row - 1, col + 1}, board, piece, moves);
        addPseudoLegalMove(start, {row + 1, col - 1}, board, piece, moves);
    }
    else if (piece->getType() == PieceType::Queen) {
        addStraightPseudoLegalMoves(start, board, piece, moves);
        addDiagonalPseudoLegalMoves(start, board, piece, moves);
    }
    else if (piece->getType() == PieceType::Bishop) {
        addDiagonalPseudoLegalMoves(start, board, piece, moves);
    }
    else if (piece->getType() == PieceType::Rook) {
        addStraightPseudoLegalMoves(start, board, piece, moves);
    }
    else if (piece->getType() == PieceType::Knight) {
        addPseudoLegalMove(start, {row + 1, col + 2}, board, piece, moves);
        addPseudoLegalMove(start, {row + 1, col - 2}, board, piece, moves);
        addPseudoLegalMove(start, {row - 1, col + 2}, board, piece, moves);
        addPseudoLegalMove(start, {row - 1, col - 2}, board, piece, moves);
        addPseudoLegalMove(start, {row + 2, col + 1}, board, piece, moves);
        addPseudoLegalMove(start, {row + 2, col - 1}, board, piece, moves);
        addPseudoLegalMove(start, {row - 2, col + 1}, board, piece, moves);
        addPseudoLegalMove(start, {row - 2, col - 1}, board, piece, moves);
    } 
    else if (piece->getType() == PieceType::Pawn) {
        addPawnStandardMoves(start, board, piece, moves);
        addPawnCaptureMoves(start, board, piece, moves);
        addEnPassant(start, board, piece, previousMove, moves);
    }
    return moves;
}

bool Rules::isUnderAttack(Colour c, const std::pair<int, int> &pos, 
    Board &board, const Move &previousMove)
{
    if (c == Colour::White) {

        // gets a reference to the set of all positions of squares that have
        //  white pieces
        auto &whitePieces = board.getWhitePieces();
        for (auto &start : whitePieces) {

            // generate all pseudo-legal moves for the white piece on the
            //  square with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // if the end position of the move is the same as pos,
                //  return true
                if (move.endPos == pos)
                    return true;
            }
        }
        return false;
    }
    else {

        // gets a reference to the set of all positions of squares that have
        //  black pieces
        auto &blackPieces = board.getBlackPieces();

        for (auto &start : blackPieces) {

            // generate all pseudo-legal moves for the black piece on the
            //  square with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // if the end position of the move is the same as pos,
                //  return true
                if (move.endPos == pos)
                    return true;
            }
        }
        return false;
    }
}

void Rules::addCastling(const std::pair<int, int> &start, Board &board, 
    std::shared_ptr<Piece> &king, std::vector<Move> &moves, 
    const Move &previousMove)
{
    // if the King has moved, return
    if (king->isMoved())
        return;
    
    int row = start.first, col = start.second; 

    if (king->getColour() == Colour::White) {
        int rookCol = col + 3;
        auto rook = board.getSquare(row, rookCol).getPiece();

        // if the Rook to right is on the square with position (row, rookCol)
        //  and hasn't moved
        if (rook && !rook->isMoved()) {
            for (int i = col + 1; i < rookCol; ++i) {

                // if there is a piece between the King and the Rook to the
                //  right, return
                if (board.getSquare(row, i).getPiece())
                    return;
            }
            for (int i = col; i < rookCol; ++i) {

                // if the starting position, final position, or the positions
                //  in between the castle are under attack, return
                if (isUnderAttack(Colour::White, {row, i}, board, previousMove))
                    return;
            }
            moves.emplace_back(king, start, std::pair<int, int>{row, col + 2},
                nullptr, std::pair<int, int>{-1, -1}, rook, 
                std::pair<int, int>{row, rookCol}, std::pair<int, int>{row, col + 1});
        }

        rookCol = col - 4;
        rook = board.getSquare(row, rookCol).getPiece();

        // if the Rook to left is on the square with position (row, rookCol)
        //  and hasn't moved
        if (rook && !rook->isMoved()) {
            for (int i = col - 1; i > rookCol; --i) {

                // if there is a piece between the King and the Rook to the
                //  right, return
                if (board.getSquare(row, i).getPiece())
                    return;
            }
            for (int i = col; i > rookCol + 1; --i) {

                // if the starting position, final position, or the positions
                //  in between the castle are under attack, return
                if (isUnderAttack(Colour::White, {row, i}, board, previousMove))
                    return;
            }
            moves.emplace_back(king, start, std::pair<int, int>{row, col - 2},
                nullptr, std::pair<int, int>{-1, -1}, rook,
                std::pair<int, int>{row, rookCol}, std::pair<int, int>{row, col - 1});
        }
    }
}

bool Rules::check(Colour c, Board &board, const Move &previousMove) {
    if (c == Colour::White) {

        // gets a reference to the set of all positions of squares that have
        //  black pieces
        auto &blackPieces = board.getBlackPieces();
        for (auto &start : blackPieces) {

            // generate all pseudo-legal moves for the black piece on the
            //  square with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // gets a reference to the captured piece of the move
                auto &piece = move.capturedPiece;

                // if the captured piece is a King, return true
                if (piece && piece->getType() == PieceType::King)
                    return true;
            }
        }
        return false;
    }
    else {

        // gets a reference to the set of all positions of squares that have
        //  white pieces
        auto &whitePieces = board.getWhitePieces();

        for (auto &start : whitePieces) {

            // generate all pseudo-legal moves for the white piece on the
            //  square with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // gets a reference to the captured piece of the move
                auto &piece = move.capturedPiece;

                // if the captured piece is a King, return true
                if (piece && piece->getType() == PieceType::King)
                    return true;
            }
        }
        return false;
    }
}

