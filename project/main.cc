#include "board.h"
using namespace std;

int main() {
    Board board{8};
    cout << board << endl;
    cout << endl;
    board.initBoard();
    cout << board << endl;
}
