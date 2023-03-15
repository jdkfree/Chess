#ifndef GRAPHICAL_H
#define GRAPHICAL_H
#include "window.h"
#include "gameboard.h"

class GraphicalDisplay {
    private:
    GameBoard& gameBoard;
    Xwindow *xwindow;
    bool drewBoard = false;

public:
    GraphicalDisplay (GameBoard& gameBoard);
    ~GraphicalDisplay ();
    void drawBoard();
    void createXwindow();
    void drawPiece(int index);
    void redrawSquare(int index);
    void notify();
    void drawPawn(int color, int x, int y, int size);
    void drawKing(int color, int x, int y, int size);
    void drawQueen(int color, int x, int y, int size);
    void drawRook(int color, int x, int y, int size);
    void drawBishop(int color, int x, int y, int size);
    void drawKnight(int color, int x, int y, int size);
    void setDrewBoard(bool drew);
};
#endif