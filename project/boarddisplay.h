#ifndef __BOARD_DISPLAY_H__
#define __BOARD_DISPLAY_H__
#include "observer.h"
#include "window.h"
#include <vector>

class BoardDisplay final: public Observer {
    int boardSize;
    std::vector<std::vector<char>> textDisplay;
    // Xwindow graphicsDisplay;
public:
    explicit BoardDisplay(int size);
    int getBoardSize() const;
    virtual void update(Square &square) override;
    friend std::ostream &operator<<(std::ostream &out, BoardDisplay &d);
};

#endif
