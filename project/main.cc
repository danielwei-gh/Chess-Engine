#include "board.h"
using namespace std;

int main() {
    Board board{8};
    board.initBoard();
    cout << board << endl;
}
