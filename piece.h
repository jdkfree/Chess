#ifndef PIECE_H
#define PIECE_H
#include "gameboard.h"
#include "move.h"

//class Move;

class Piece {
    protected:
    int currPos;
    char symbol;
    bool white;
    bool captured = false;
    bool takenFirstMove = false;
    GameBoard& board;

    public:
    Piece(int currPos, char symbol, bool white, GameBoard& board);
    Piece(const Piece & other);
    virtual ~Piece() = 0;
    bool isKingInCheck();
    Move* move (int posTo);
    virtual bool isValidMove (int posTo) = 0;
    virtual bool canCapturePieceAt (int posTo) = 0;
    char getSymbol() const;
    void setCurrPos(int pos);
    int getCurrPos() const;
    bool isWhite() const;
    bool isCaptured() const;
    void setCaptured(bool captured);
    bool hasTakenFirstMove() const;
    void setHasTakenFirstMove(bool hasMoved);
    bool canMove(int posTo, bool &captureOrCheck, bool &avoidsCapture);
};
#endif
