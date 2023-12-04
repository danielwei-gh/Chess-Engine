#include "rules.h"

bool Rules::isValidPos(int row, int col, const Board &board) 
{
    return 0 <= row && row < board.getSize() && 0 <= col && col < board.getSize();
}

bool Rules::addPseudoLegalMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, const Board &board, 
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
    const Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
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
    for (int i = row - 1; i >= 0; --i) {
        if (!addPseudoLegalMove(start, {i, col}, board, piece, moves))
            break;
    }
}

void Rules::addDiagonalPseudoLegalMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
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
    const Board &board, std::shared_ptr<Piece> &pawn, std::vector<Move> &moves)
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
    const Board &board, std::shared_ptr<Piece> &pawn, std::vector<Move> &moves)
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

void Rules::addEnPassant(const std::pair<int, int> &start, const Board &board,
    std::shared_ptr<Piece> &pawn, const Move &previousMove, 
    std::vector<Move> &moves)
{
    int row = start.first, col = start.second;

    // gets an increment value based on the Pawn's colour
    int rowInc = pawn->getColour() == Colour::White ? -1 : 1;

    auto previousPiece = previousMove.movedPiece;

    // if there was no previous move
    if (!previousPiece)
        return;

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
        std::abs(previousPieceEndCol - col) == 1) 
    {    
        // gets an increment value based on whether previousPiece is to the
        //  right or left of pawn (colInc is either -1 or 1)
        int colInc = previousPieceEndCol - col;
        moves.emplace_back(pawn, start, 
            std::pair<int, int>{row + rowInc, col + colInc}, previousPiece,
            previousMove.endPos);
    }
}

std::vector<Move> 
Rules::generatePseudoLegalMoves(const std::pair<int, int> &start, 
    const Board &board, const Move &previousMove)
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
    const Board &board, const Move &previousMove)
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

void Rules::addLeftCastling(const std::pair<int, int> &start, const Board &board, 
    std::shared_ptr<Piece> &king, std::vector<Move> &moves, 
    const Move &previousMove)
{
    int row = start.first, col = start.second;

    int rookCol = col - 4;
    auto rook = board.getSquare(row, rookCol).getPiece();

    // if there is no Rook on the square with position (row, rookCol), return
    if (!rook)
        return;

    // if the Rook has a different colour than the King, return
    if (rook->getColour() != king->getColour())
        return;

    // if the Rook to left is on the square with position (row, rookCol)
    //  and hasn't moved
    if (!rook->isMoved()) {
        for (int i = col - 1; i > rookCol; --i) {

            // if there is a piece between the King and the Rook to the
            //  right, return
            if (board.getSquare(row, i).getPiece())
                return;
        }

        // gets the colour that is opposite the King's colour
        Colour enemyColour = king->getColour() == Colour::White ? 
            Colour::Black : Colour::White;

        for (int i = col; i > rookCol + 1; --i) {

            // if the starting position, final position, or the positions
            //  in between the castle are under attack, return
            if (isUnderAttack(enemyColour, {row, i}, board, previousMove))
                return;
        }
        moves.emplace_back(king, start, std::pair<int, int>{row, col - 2},
            nullptr, std::pair<int, int>{-1, -1}, rook,
            std::pair<int, int>{row, rookCol}, std::pair<int, int>{row, col - 1});
    }
}

void Rules::addRightCastling(const std::pair<int, int> &start, const Board &board, 
    std::shared_ptr<Piece> &king, std::vector<Move> &moves, 
    const Move &previousMove)
{   
    int row = start.first, col = start.second; 
    
    int rookCol = col + 3;
    auto rook = board.getSquare(row, rookCol).getPiece();

    // if there is no Rook on the square with position (row, rookCol), return
    if (!rook)
        return;

    // if the Rook has a different colour than the King, return
    if (rook->getColour() != king->getColour())
        return;

    // if the Rook to right is on the square with position (row, rookCol)
    //  and hasn't moved
    if (!rook->isMoved()) {
        for (int i = col + 1; i < rookCol; ++i) {

            // if there is a piece between the King and the Rook to the
            //  right, return
            if (board.getSquare(row, i).getPiece())
                return;
        }

        // gets the colour that is opposite the King's colour
        Colour enemyColour = king->getColour() == Colour::White ? 
            Colour::Black : Colour::White;
        
        for (int i = col; i < rookCol; ++i) {

            // if the starting position, final position, or the positions
            //  in between the castle are under attack, return
            if (isUnderAttack(enemyColour, {row, i}, board, previousMove))
                return;
        }
        moves.emplace_back(king, start, std::pair<int, int>{row, col + 2},
            nullptr, std::pair<int, int>{-1, -1}, rook, 
            std::pair<int, int>{row, rookCol}, std::pair<int, int>{row, col + 1});
    }
}

void Rules::addCastling(const std::pair<int, int> &start, const Board &board, 
    std::shared_ptr<Piece> &king, std::vector<Move> &moves, 
    const Move &previousMove)
{
    // if the King is not on the starting square for castling, return
    if (start != std::pair<int, int>{0, 4} && start != std::pair<int, int>{7, 4})
        return;

    // if the King has moved, return
    if (king->isMoved())
        return;
    
    addLeftCastling(start, board, king, moves, previousMove);
    addRightCastling(start, board, king, moves, previousMove);
}

void Rules::addSquarePosBetween(const std::pair<int, int> &start,
    const std::pair<int, int> &end, std::vector<std::pair<int, int>> &posVec)
{
    int startRow = start.first, startCol = start.second;
    int endRow = end.first, endCol = end.second;

    // gets an increment value based on the value of endRow and startRow
    int rowInc = endRow > startRow ? 1 : -1;

    // gets an increment value based on the value of endCol and startCol
    int colInc = endCol > startCol ? 1 : -1;

    // if the two squares are on the same row
    if (startRow == endRow) {
        int currCol = startCol + colInc;

        while (currCol != endCol) {
            posVec.emplace_back(startRow, currCol);
            currCol += colInc;
        }
    }
    // if the two squares are on the same column
    else if (startCol == endCol) {
        int currRow = startRow + rowInc;
        
        while (currRow != endRow) {
            posVec.emplace_back(currRow, startCol);
            currRow += rowInc;
        }
    }
    // if the two squares are on the same diagonal
    else if (std::abs(endRow - startRow) == std::abs(endCol - startCol)) {
        int currRow = startRow + rowInc;
        int currCol = startCol + colInc;

        while (currRow != endRow && currCol != endCol) {
            posVec.emplace_back(currRow, currCol);
            currRow += rowInc;
            currCol += colInc;
        }
    }
}

bool Rules::checkmateHelper(const Board &board, const Move &previousMove,
    const std::pair<int, int> &allyKingPos, const std::pair<int, int> &enemyKingPos,
    const std::set<std::pair<int, int>> &allyPieces,
    const std::set<std::pair<int, int>> &enemyPieces)
{
    // since Rules::checkmate is called only called after Rules::check
    //  returns true, if the ally King has any legal moves on the board, 
    //  return false
    if (generateFullyLegalMoves(allyKingPos, board, previousMove).size() > 0)
        return false;
    
    std::vector<std::pair<int, int>> attackers;
        
    for (auto &start : enemyPieces) {

        // if the enemy piece is the enemy King, continue to the next enemy
        //  piece (since the enemy King should never have a move to capture 
        //  the ally King)
        if (start == enemyKingPos)
            continue;
        
        // generate all pseudo-legal moves for the enemy piece on the
        //  square with position start
        auto enemyPieceMoves = generatePseudoLegalMoves(start, board, previousMove);

        for (auto &move : enemyPieceMoves) {
            
            // if the enemy piece has a move that can capture the ally
            //  King, add the position of the enemy piece to attackers
            if (move.endPos == allyKingPos) {
                attackers.emplace_back(start.first, start.second);
                break;
            }
        }
    }

    // if there is more than one enemy attacker to the ally King, return
    //  false (since the ally King has no legal moves)
    if (attackers.size() > 1)
        return false;
    
    // gets the piece type of the only enemy attacker
    PieceType attackerType = board.getSquare(
        attackers[0].first, attackers[0].second).getPiece()->getType();

    std::vector<std::pair<int, int>> squaresBetween;

    // if the enemy attacker is a Queen, Bishop, or Rook, add all the 
    //  position of squares between the ally King and the enemy attacker
    //  into squaresBetween
    if (attackerType == PieceType::Queen || 
        attackerType == PieceType::Bishop ||
        attackerType == PieceType::Rook)
    {   
        addSquarePosBetween(allyKingPos, attackers[0], squaresBetween);
    }

    for (auto &start : allyPieces) {

        // if the ally piece is the ally King, continue to the next
        //  ally piece
        if (start == allyKingPos)
            continue;
        
        auto allyPieceMoves = generateFullyLegalMoves(start, board, previousMove);

        for (auto &move : allyPieceMoves) {
            
            // if the ally piece can capture the only enemy attacker,
            //  return false
            if (move.endPos == attackers[0])
                return false;
        }

        // if the enemy attacker is a Queen, Bishop, or Rook
        if (attackerType == PieceType::Queen ||
            attackerType == PieceType::Bishop ||
            attackerType == PieceType::Rook) 
        {
            for (auto &squarePos : squaresBetween) {
                for (auto &move : allyPieceMoves) {
                    
                    // if the square between the ally King and the enemy
                    //  attacker is attacked by the ally piece, return
                    //  false (this means that the check can be blocked)
                    if (squarePos == move.endPos)
                        return false;
                }
            }
        }
    }
    return true;
}

std::vector<Move> 
Rules::generateFullyLegalMoves(const std::pair<int, int> &start, 
    const Board &board, const Move &previousMove)
{
    int row = start.first, col = start.second;
    auto piece = board.getSquare(row, col).getPiece();

    // if there is no piece on the square with position start, return no moves
    if (!piece)
        return std::vector<Move>{};

    std::vector<Move> moves{generatePseudoLegalMoves(start, board, previousMove)};

    // gets a copy of the current board
    Board tmpBoard{board};

    auto it = moves.begin();
    while (it != moves.end()) {
        int endRow = it->endPos.first, endCol = it->endPos.second;
        int enPassantRow = it->enPassantPos.first;
        int endPassantCol = it->enPassantPos.second;
        bool inCheck;

        // if the move was enPassant
        if (enPassantRow != -1 && endPassantCol != -1) {
            
            // make the move
            auto attackingPiece = tmpBoard.removePiece(row, col);
            auto capturedPiece = tmpBoard.removePiece(enPassantRow, endPassantCol);
            tmpBoard.placePiece(endRow, endCol, attackingPiece);

            // check if the King with the same colour as piece is in check
            //  on tmpBoard
            inCheck = check(piece->getColour(), tmpBoard, *it);

            // undo the move
            attackingPiece = tmpBoard.removePiece(endRow, endCol);
            tmpBoard.placePiece(enPassantRow, endPassantCol, capturedPiece);
            tmpBoard.placePiece(row, col, attackingPiece);
        } else {

            // make the move
            auto attackingPiece = tmpBoard.removePiece(row, col);
            auto capturedPiece = tmpBoard.removePiece(endRow, endCol);
            tmpBoard.placePiece(endRow, endCol, attackingPiece);

            // check if the King with the same colour as piece is in check
            //  on tmpBoard
            inCheck = check(piece->getColour(), tmpBoard, *it);

            // undo the move
            attackingPiece = tmpBoard.removePiece(endRow, endCol);
            tmpBoard.placePiece(endRow, endCol, capturedPiece);
            tmpBoard.placePiece(row, col, attackingPiece);
        }

        // if the King with the same colour as piece is in check on tmpBoard,
        //  erase the move, otherwise check the next move
        if (inCheck)
            it = moves.erase(it);
        else
            ++it;
    }
    
    // if piece is a King, add all castling moves for piece
    if (piece->getType() == PieceType::King)
        addCastling(start, board, piece, moves, previousMove);
    
    return moves;
}

bool Rules::check(Colour c, const Board &board, const Move &previousMove) 
{
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

bool Rules::checkmate(Colour c, const Board &board, const Move &previousMove)
{
    std::pair<int, int> whiteKingPos = board.getWhiteKingPos();
    std::pair<int, int> blackKingPos = board.getBlackKingPos();

    // gets a reference to the set of all positions of squares that have
    //  white pieces
    auto &whitePieces = board.getWhitePieces();

    // gets a reference to the set of all positions of squares that have
    //  black pieces
    auto &blackPieces = board.getBlackPieces();

    if (c == Colour::White)
        return checkmateHelper(board, previousMove, whiteKingPos, blackKingPos,
            whitePieces, blackPieces);
    else
        return checkmateHelper(board, previousMove, blackKingPos, whiteKingPos,
            blackPieces, whitePieces);
}

bool Rules::stalemate(Colour c, const Board &board, const Move &previousMove) 
{
    // gets a reference to the set of all positions of squares that have
    //  white pieces
    auto &whitePieces = board.getWhitePieces();
    
    // gets a reference to the set of all positions of squares that have
    //  black pieces
    auto &blackPieces = board.getBlackPieces();

    // if the board has only one white piece and one black piece
    if (whitePieces.size() == 1 && blackPieces.size() == 1)
        return true;
    
    if (whitePieces.size() == 2 && blackPieces.size() == 1) {
        std::pair<int, int> piecePos;
        for (auto &start : whitePieces) {

            // get the position of the only other white piece
            if (start != board.getWhiteKingPos()) {
                piecePos = start;
                break;
            }    
        }
        auto piece = board.getSquare(piecePos.first, piecePos.second).getPiece();

        // if the only other white piece is a Bishop or a Knight
        if (piece->getType() == PieceType::Bishop || 
            piece->getType() == PieceType::Knight)
        {
            return true;
        }
    }

    if (whitePieces.size() == 1 && blackPieces.size() == 2) {
        std::pair<int, int> piecePos;
        for (auto &start : blackPieces) {

            // get the position of the only other black piece
            if (start != board.getBlackKingPos()) {
                piecePos = start;
                break;
            }    
        }
        auto piece = board.getSquare(piecePos.first, piecePos.second).getPiece();

        // if the only other black piece is a Bishop or a Knight
        if (piece->getType() == PieceType::Bishop || 
            piece->getType() == PieceType::Knight)
        {
            return true;
        }
    }

    if (whitePieces.size() == 2 && blackPieces.size() == 2) {
        std::pair<int, int> whitePiecePos, blackPiecePos;
        for (auto &start : whitePieces) {

            // get the position of the only other white piece
            if (start != board.getWhiteKingPos()) {
                whitePiecePos = start;
                break;
            }    
        }
        for (auto &start : blackPieces) {

            // get the position of the only other black piece
            if (start != board.getBlackKingPos()) {
                blackPiecePos = start;
                break;
            }    
        }
        auto whitePiece = 
            board.getSquare(whitePiecePos.first, whitePiecePos.second).getPiece();
        auto blackPiece = 
            board.getSquare(blackPiecePos.first, blackPiecePos.second).getPiece();

        // if the only other white piece is a Bishop or a Knight AND if the
        //  only other black piece is a Bishop or a Knight
        if ((whitePiece->getType() == PieceType::Bishop ||
            whitePiece->getType() == PieceType::Knight) &&
            (blackPiece->getType() == PieceType::Bishop ||
            blackPiece->getType() == PieceType::Knight))
        {
            return true;
        }
    }

    if (c == Colour::White) {
        for (auto &start : whitePieces) {
            
            // if the white player has any legal moves, return true
            if (generateFullyLegalMoves(start, board, previousMove).size() > 0)
                return false;
        }
    }
    else {
        for (auto &start : blackPieces) {
            
            // if the black player has any legal moves, return true
            if (generateFullyLegalMoves(start, board, previousMove).size() > 0)
                return false;
        }
    }
    return true;
}

int Rules::evalMove(int level, Colour c, Board &board, const Move &move, const Move &previousMove) {
    float val = 0;
    Colour op_col = (c == Colour::Black ? Colour::White : Colour::Black);

    if (level == 2) {

        // simulating the move
        if (move.capturedPiece != nullptr) {
            val += move.capturedPiece->getValue();
            board.removePiece(move.endPos.first, move.endPos.second);
        }
        board.placePiece(move.endPos.first, move.endPos.second, move.movedPiece);
        board.removePiece(move.startPos.first, move.startPos.second);
        if (Rules::check(op_col, board, previousMove)) val += 50;

        // undoing the move
        board.placePiece(move.startPos.first, move.startPos.second, move.movedPiece);
        board.removePiece(move.endPos.first, move.endPos.second);
        if (move.capturedPiece != nullptr) {
            board.placePiece(move.endPos.first, move.endPos.second, move.capturedPiece);
        }

    } else if (level == 3) {

        bool wasunderAttack = isUnderAttack(op_col, move.startPos, board, previousMove);

        // simulating the move
        if (move.capturedPiece != nullptr) {
            // prefers check
            val += move.capturedPiece->getValue();
            board.removePiece(move.endPos.first, move.endPos.second);
        }
        board.placePiece(move.endPos.first, move.endPos.second, move.movedPiece);
        board.removePiece(move.startPos.first, move.startPos.second);
        // does check?
        if (Rules::check(op_col, board, previousMove)) val += 50;

        bool isunderAttack = isUnderAttack(op_col, move.endPos, board, move);

        // avoiding check
        if (wasunderAttack && !isunderAttack) {
            val += move.movedPiece->getValue();
        } else if (!wasunderAttack && isunderAttack) {
            val -= move.movedPiece->getValue();
        }

        // undoing the move
        board.placePiece(move.startPos.first, move.startPos.second, move.movedPiece);
        board.removePiece(move.endPos.first, move.endPos.second);
        if (move.capturedPiece != nullptr) {
            board.placePiece(move.endPos.first, move.endPos.second, move.capturedPiece);
        }

    } else {
        bool wasunderAttack = isUnderAttack(op_col, move.startPos, board, previousMove);

        // simulating the move
        if (move.capturedPiece != nullptr) {
            // prefers check
            val += move.capturedPiece->getValue();
            board.removePiece(move.endPos.first, move.endPos.second);
        }
        board.placePiece(move.endPos.first, move.endPos.second, move.movedPiece);
        board.removePiece(move.startPos.first, move.startPos.second);
        // does check?
        if (Rules::check(op_col, board, previousMove)) val += 50;

        bool isunderAttack = isUnderAttack(op_col, move.endPos, board, move);

        // avoiding check
        if (wasunderAttack && !isunderAttack) {
            val += move.movedPiece->getValue();
        } else if (!wasunderAttack && isunderAttack) {
            val -= move.movedPiece->getValue();
        }

        // undoing the move
        board.placePiece(move.startPos.first, move.startPos.second, move.movedPiece);
        board.removePiece(move.endPos.first, move.endPos.second);
        if (move.capturedPiece != nullptr) {
            board.placePiece(move.endPos.first, move.endPos.second, move.capturedPiece);
        }

        // positional advantage
        int r1 = move.startPos.first;
        int c1 = move.startPos.second;
        int r2 = move.endPos.first;
        int c2 = move.endPos.second;

        val += move.movedPiece->getboardVal(r2, c2);
        val -= move.movedPiece->getboardVal(r1, c1);

    }

    return val;
}
