#include "boarddisplay.h"
#include "square.h"

BoardDisplay::BoardDisplay(int size): boardSize{size} {
    for (int i = 0; i < boardSize; ++i) {
        textDisplay.emplace_back(std::vector<char>{});
        for (int j = 0; j < boardSize; ++j) {
            char c = (i + j) % 2 == 0 ? ' ' : '_';
            textDisplay[i].emplace_back(c);
        }
    }
}

int BoardDisplay::getBoardSize() const {
    return boardSize;
}

void BoardDisplay::update(Square &square) {
    int row = square.getRow(), col = square.getColumn();
    char symbol;
    if (square.getPiece())
        symbol = square.getPiece()->getSymbol();
    else
        symbol = square.getColour() == Colour::White ? ' ' : '_';
    textDisplay[row][col] = symbol;
}

std::ostream &operator<<(std::ostream &out, BoardDisplay &d) {
    for (int i = 0; i < d.getBoardSize(); ++i) {
        out << d.getBoardSize() - i << " ";
        for (int j = 0; j < d.getBoardSize(); ++j)
            out << d.textDisplay[i][j];
        out << std::endl;
    }
    out << std::endl << "  abcdefgh";
    return out;
}
