#include "board.h"
#include "rules.h"
using namespace std;

int main() {
    Board board{8};

    board.initBoard();
    auto blackPawn = board.removePiece(1, 3);
    board.placePiece(3, 3, blackPawn);
    auto whitePawn = board.removePiece(6, 4);
    board.placePiece(3, 4, whitePawn);

    cout << board << endl << endl;

    Move previousMove{blackPawn, {1, 3}, {3, 3}};

    auto fullyLegalMoves = Rules::generateFullyLegalMoves({3,4}, board, previousMove);

    for (auto &move : fullyLegalMoves)
        cout << move << std::endl;
    
    cout << fullyLegalMoves.size() << endl;
    cout << board << endl << endl;
}
