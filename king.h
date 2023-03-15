#ifndef KING_H
#define KING_H
#include "piece.h"
#include "move.h"

class King : public Piece {
    public:
    King(int currPos, char symbol, bool white, GameBoard& board);
    virtual bool isValidMove (int posTo) override;
    virtual bool canCapturePieceAt (int posTo) override;
    bool canCastle(int posTo); 
};
#endif
