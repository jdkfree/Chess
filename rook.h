#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {
    public:
    Rook(int currPos, char symbol, bool white, GameBoard& board);
    virtual bool isValidMove (int posTo) override;
    virtual bool canCapturePieceAt (int posTo) override;
};
#endif
