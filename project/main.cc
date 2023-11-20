#include "board.h"
using namespace std;

int main() {
    Board board{8};
    cout << board << endl;
    cout << endl;
    board.initBoard();
    cout << board << endl;
    // cout << endl;
    // board.placePiece(3, 1, Colour::Black, PieceType::Bishop);
    // cout << board << endl;
    // cout << endl;
    // board.removePiece(0, 0);
    // cout << board << endl;
    // cout << endl;
    // board.removePiece(0, 1);
    // cout << board << endl;
    // cout << endl;
    // board.removePiece(1, 0);
    // cout << board << endl;
    // cout << endl;
    // board.removePiece(3, 1);
    // cout << board << endl;
    // cout << endl;
    // board.removePiece(7, 1);
    // cout << board << endl;
    // cout << endl;
    // board.removePiece(7, 2);
    // cout << board << endl;
}
