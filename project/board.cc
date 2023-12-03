#include "board.h"

void Board::insertToPieces(int row, int col, Colour c) {
    if (c == Colour::White)
        whitePieces.insert({row, col});
    else
        blackPieces.insert({row, col});
}

void Board::eraseFromPieces(int row, int col, Colour c) {
    if (c == Colour::White)
        whitePieces.erase({row, col});
    else
        blackPieces.erase({row, col});
}

Board::Board(int size): boardSize{size}, display{new BoardDisplay{size}}, 
whiteKingPos{-1, -1}, blackKingPos{-1, -1} {
    for (int i = 0; i < boardSize; ++i) {
        board.emplace_back(std::vector<Square>{});
        for (int j = 0; j < boardSize; ++j) {
            Colour c = (i + j) % 2 == 0 ? Colour::White : Colour::Black;
            board[i].emplace_back(c, i, j);
            board[i][j].attach(display);
        }
    }
}

Board::Board(const Board &other): boardSize{other.boardSize}, 
    board{other.board}, display{other.display}, whitePieces{other.whitePieces},
    blackPieces{other.blackPieces}, whiteKingPos{other.whiteKingPos},
    blackKingPos{other.blackKingPos}
{
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j)
            board[i][j].detach(display);
    }
}

int Board::getSize() const {
    return boardSize;
}

const Square& Board::getSquare(int row, int col) const {
    return board[row][col];
}

void Board::initBoard() {
    // initializes all black pieces
    board[0][0].setPiece(std::make_shared<Rook>(Colour::Black));
    board[0][1].setPiece(std::make_shared<Knight>(Colour::Black));
    board[0][2].setPiece(std::make_shared<Bishop>(Colour::Black));
    board[0][3].setPiece(std::make_shared<Queen>(Colour::Black));
    board[0][4].setPiece(std::make_shared<King>(Colour::Black));
    blackKingPos = {0, 4};
    board[0][5].setPiece(std::make_shared<Bishop>(Colour::Black));
    board[0][6].setPiece(std::make_shared<Knight>(Colour::Black));
    board[0][7].setPiece(std::make_shared<Rook>(Colour::Black));
    for (int i = 0; i < boardSize; ++i) {
        board[1][i].setPiece(std::make_shared<Pawn>(Colour::Black));

        // inserts all positions of black pieces into blackPieces
        insertToPieces(0, i, Colour::Black);
        insertToPieces(1, i, Colour::Black);
    }

    // initializes all white pieces
    board[7][0].setPiece(std::make_shared<Rook>(Colour::White));
    board[7][1].setPiece(std::make_shared<Knight>(Colour::White));
    board[7][2].setPiece(std::make_shared<Bishop>(Colour::White));
    board[7][3].setPiece(std::make_shared<Queen>(Colour::White));
    board[7][4].setPiece(std::make_shared<King>(Colour::White));
    whiteKingPos = {7, 4};
    board[7][5].setPiece(std::make_shared<Bishop>(Colour::White));
    board[7][6].setPiece(std::make_shared<Knight>(Colour::White));
    board[7][7].setPiece(std::make_shared<Rook>(Colour::White));
    for (int i = 0; i < boardSize; ++i) {
        board[6][i].setPiece(std::make_shared<Pawn>(Colour::White));

        // inserts all positions of white pieces into whitePieces
        insertToPieces(6, i, Colour::White);
        insertToPieces(7, i, Colour::White);
    }
}

void Board::placePiece(int row, int col, std::shared_ptr<Piece> newPiece) {
    
    // if newPiece is a null shared_ptr, return
    if (!newPiece)
        return;

    // inserts the position of the new piece into one of the sets
    insertToPieces(row, col, newPiece->getColour());

    // if newPiece is a King, update square positions for the King
    if (newPiece->getType() == PieceType::King) {
        if (newPiece->getColour() == Colour::White)
            whiteKingPos = {row, col};
        else
            blackKingPos = {row, col};
    }
    board[row][col].setPiece(newPiece);
}

std::shared_ptr<Piece> Board::removePiece(int row, int col) {
    std::shared_ptr<Piece> piece = board[row][col].getPiece();

    // erases the position if piece is not null
    if (piece) {
        Colour c = piece->getColour();
        eraseFromPieces(row, col, c);

        // if piece is a King, reset the square positions to (-1, -1)
        if (piece->getType() == PieceType::King) {
            if (c == Colour::White)
                whiteKingPos = {-1, -1};
            else
                blackKingPos = {-1, -1};
        }
    }
    return board[row][col].setPiece(std::shared_ptr<Piece>{});
}

const std::set<std::pair<int, int>>& Board::getWhitePieces() const {
    return whitePieces;
}

const std::set<std::pair<int, int>>& Board::getBlackPieces() const {
    return blackPieces;
}

const std::pair<int, int>& Board::getWhiteKingPos() const {
    return whiteKingPos;
}

const std::pair<int, int>& Board::getBlackKingPos() const {
    return blackKingPos;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
    out << *b.display;
    return out;
}
