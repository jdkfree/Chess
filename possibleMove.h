#ifndef POSSIBLEMOVE_H
#define POSSIBLEMOVE_H

#include "piece.h"

class PossibleMove {
    Piece *piece; 
    int posFrom, posTo;

    public:
        PossibleMove(Piece* piece, int posFrom, int posTo);
        int getPosFrom() const;
        int getPosTo() const;
        Piece* getPiece() const;
};

#endif