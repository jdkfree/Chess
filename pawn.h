#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include "move.h"

class Pawn : public Piece {
    public:
    Pawn(int currPos, char symbol, bool white, GameBoard& board);
    virtual bool isValidMove (int posTo) override;
    virtual bool canCapturePieceAt (int posTo) override;
    bool enpassant(int posTo); 
};
#endif
