#include "board.h"

Board::Board(int size): boardSize{size}, display{new BoardDisplay{size}} {
    for (int i = 0; i < boardSize; ++i) {
        board.emplace_back(std::vector<Square>{});
        for (int j = 0; j < boardSize; ++j) {
            Colour c = (i + j) % 2 == 0 ? Colour::White : Colour::Black;
            board[i].emplace_back(c, i, j);
            board[i][j].attach(display);
        }
    }
}

void Board::initBoard() {
    // initializes all black pieces
    board[0][0].setPiece(std::make_shared<Rook>(Colour::Black));
    board[0][1].setPiece(std::make_shared<Knight>(Colour::Black));
    board[0][2].setPiece(std::make_shared<Bishop>(Colour::Black));
    board[0][3].setPiece(std::make_shared<Queen>(Colour::Black));
    board[0][4].setPiece(std::make_shared<King>(Colour::Black));
    board[0][5].setPiece(std::make_shared<Bishop>(Colour::Black));
    board[0][6].setPiece(std::make_shared<Knight>(Colour::Black));
    board[0][7].setPiece(std::make_shared<Rook>(Colour::Black));
    for (int i = 0; i < boardSize; ++i)
        board[1][i].setPiece(std::make_shared<Pawn>(Colour::Black));
    
    // initializes all white pieces
    board[7][0].setPiece(std::make_shared<Rook>(Colour::White));
    board[7][1].setPiece(std::make_shared<Knight>(Colour::White));
    board[7][2].setPiece(std::make_shared<Bishop>(Colour::White));
    board[7][3].setPiece(std::make_shared<Queen>(Colour::White));
    board[7][4].setPiece(std::make_shared<King>(Colour::White));
    board[7][5].setPiece(std::make_shared<Bishop>(Colour::White));
    board[7][6].setPiece(std::make_shared<Knight>(Colour::White));
    board[7][7].setPiece(std::make_shared<Rook>(Colour::White));
    for (int i = 0; i < boardSize; ++i)
        board[6][i].setPiece(std::make_shared<Pawn>(Colour::White));
}

std::shared_ptr<Piece> Board::placePiece(int row, int col, Colour c, PieceType p) {
    // perhaps factory method would have been better, but this works for now
    if (p == PieceType::King)
        return board[row][col].setPiece(std::make_shared<King>(c));
    else if (p == PieceType::Queen)
        return board[row][col].setPiece(std::make_shared<Queen>(c));
    else if (p == PieceType::Bishop)
        return board[row][col].setPiece(std::make_shared<Bishop>(c));
    else if (p == PieceType::Rook)
        return board[row][col].setPiece(std::make_shared<Rook>(c));
    else if (p == PieceType::Knight)
        return board[row][col].setPiece(std::make_shared<Knight>(c));
    else
        return board[row][col].setPiece(std::make_shared<Pawn>(c));
}

std::shared_ptr<Piece> Board::removePiece(int row, int col) {
    return board[row][col].setPiece(std::shared_ptr<Piece>{});
}

std::ostream &operator<<(std::ostream &out, Board &b) {
    out << *b.display;
    return out;
}
