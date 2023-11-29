#include "board.h"
#include "rules.h"
using namespace std;

int main() {
    Board board{8};

    // board.initBoard();
    
    board.placePiece(1, 2, make_shared<King>(Colour::Black));
    
    board.placePiece(4, 2, make_shared<Queen>(Colour::White));
    board.placePiece(7, 1, make_shared<Rook>(Colour::White));
    board.placePiece(7, 3, make_shared<Rook>(Colour::White));
    board.placePiece(7, 6, make_shared<King>(Colour::White));


    cout << board << endl << endl;

    Move previousMove{nullptr, {-1,-1}, {-1,-1}};

    if (Rules::check(Colour::Black, board, previousMove)) {
        cout << "Board in check" << endl;
        if (Rules::checkmate(Colour::Black, board, previousMove))
            cout << "Board in checkmate" << endl;
    }

    cout << board << endl << endl;

    // auto fullyLegalMoves = Rules::generateFullyLegalMoves({4,4}, board, previousMove);

    // for (auto &move : fullyLegalMoves)
    //     cout << move << std::endl;
    
    // cout << fullyLegalMoves.size() << endl;
    // cout << board << endl << endl;
}
