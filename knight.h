#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
#include "move.h"

class Knight : public Piece {
    public:
    Knight(int currPos, char symbol, bool isWhite, GameBoard& board);
    virtual bool isValidMove (int posTo) override;
    virtual bool canCapturePieceAt (int posTo) override;
};
#endif
