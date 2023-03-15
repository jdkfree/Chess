#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "gameboard.h"

class TextDisplay {
    private:
    GameBoard& gameBoard;

    public:
    TextDisplay(GameBoard& gameBoard);
    void notify ();
};
#endif