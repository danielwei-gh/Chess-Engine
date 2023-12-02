#include "boarddisplay.h"
#include "square.h"

BoardDisplay::BoardDisplay(int size): boardSize{size},graphicsDisplay{2000, 2400} {
    for (int i = 0; i < boardSize; ++i) {
        textDisplay.emplace_back(std::vector<char>{});
        for (int j = 0; j < boardSize; ++j) {
            char c = (i + j) % 2 == 0 ? ' ' : '_';
            textDisplay[i].emplace_back(c);
        }
    }
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            if((8*i+j) % 2 == 0){
                graphicsDisplay.fillRectangle(100+250*i, 300+250*j, 250, 250, Xwindow::White);
            } else {
                graphicsDisplay.fillRectangle(100+250*i, 300+250*j, 250, 250, Xwindow::Black);
            }
        }
    }
    graphicsDisplay.setFont();
}

int BoardDisplay::getBoardSize() const {
    return boardSize;
}

void BoardDisplay::update(Square &square) {
    int row = square.getRow(), col = square.getColumn();
    char symbol;
    std::string ssymbol = "";
    if (square.getPiece()) {
        symbol = square.getPiece()->getSymbol(); 
        ssymbol = "" + symbol;
    }
    else {
        symbol = square.getColour() == Colour::White ? ' ' : '_';
    }
    textDisplay[row][col] = symbol;
    if(ssymbol != "") graphicsDisplay.drawString(225 + 250 * row, 225 + 250 * col, ssymbol);
    else if((8*row+col) % 2 == 0){
        graphicsDisplay.fillRectangle(100+250*row, 300+250*col, 250, 250, Xwindow::White);
    } else {
        graphicsDisplay.fillRectangle(100+250*row, 300+250*col, 250, 250, Xwindow::Black);
    }
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


