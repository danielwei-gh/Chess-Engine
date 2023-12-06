#include "boarddisplay.h"
#include "square.h"

BoardDisplay::BoardDisplay(int size): boardSize{size},graphicsDisplay{700, 700} {
    for (int i = 0; i < boardSize; ++i) {
        textDisplay.emplace_back(std::vector<char>{});
        for (int j = 0; j < boardSize; ++j) {
            char c = (i + j) % 2 == 0 ? ' ' : '_';
            textDisplay[i].emplace_back(c);
        }
    }
    graphicsDisplay.fillRectangle(39, 39, 602, 602, Xwindow::Green);
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            if((i+j) % 2 == 0){
                graphicsDisplay.fillRectangle(40+75*i, 40+75*j, 75, 75, Xwindow::White);
            } else {
                graphicsDisplay.fillRectangle(40+75*i, 40+75*j, 75, 75, Xwindow::Green);
            }
        }
    }
    
    for(int i = 0; i < 8; ++i){
        char x = 'a' + i;
        std::string xaxis = std::string(1, x);
        
        graphicsDisplay.drawString(78 + 75 * i, 26, xaxis, Xwindow::Black);
        graphicsDisplay.drawString(78 + 75 * i, 655, xaxis, Xwindow::Black);
    }

    for(int i = 0; i < 8; ++i){
        char x = '1'+ 7-i;
        std::string yaxis = std::string(1, x);
        graphicsDisplay.drawString(26, 78 + 75 * i, yaxis, Xwindow::Black);
        graphicsDisplay.drawString(649, 78 + 75 * i, yaxis, Xwindow::Black);
    }
}

int BoardDisplay::getBoardSize() const {
    return boardSize;
}

void BoardDisplay::update(Square &square) {
    int row = square.getRow(), col = square.getColumn();
    char symbol;
    std::string dsymbol;
    if (square.getPiece()) {
        symbol = square.getPiece()->getSymbol();
        dsymbol = std::string(1, symbol);
    }
    else {
        symbol = square.getColour() == Colour::White ? ' ' : '_';
    }
    textDisplay[row][col] = symbol;
    
    if(dsymbol != "" && dsymbol[0] < 91) graphicsDisplay.drawString(76 + 75 * col, 80 + 75 * row, dsymbol, Xwindow::Blue);
    else if(dsymbol != "" && dsymbol[0] > 96 ) graphicsDisplay.drawString(76 + 75 * col, 80 + 75 * row, dsymbol, Xwindow::Red);
    else if((row+col) % 2 == 0){
        graphicsDisplay.fillRectangle(40+75*col, 40+75*row, 75, 75, Xwindow::White);
    } else {
        graphicsDisplay.fillRectangle(40+75*col, 40+75*row, 75, 75, Xwindow::Green);
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

BoardDisplay::~BoardDisplay(){
    
}

