#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
#include "move.h"

class Queen : public Piece {
    public:
    Queen(int currPos, char symbol, bool white, GameBoard& board);
    virtual bool isValidMove (int posTo) override;
    virtual bool canCapturePieceAt (int posTo) override;
};
#endif
