#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
#include "move.h"

class Bishop : public Piece {
    public:
    Bishop(int currPos, char symbol, bool white, GameBoard& board);
    virtual bool isValidMove (int posTo) override;
    virtual bool canCapturePieceAt (int posTo) override;
};
#endif
