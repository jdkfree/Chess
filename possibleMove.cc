#include "possibleMove.h"

PossibleMove::PossibleMove(Piece* piece, int posFrom, int posTo) : piece {piece}, posFrom {posFrom}, posTo {posTo} {}

int PossibleMove::getPosFrom() const {
    return posFrom;
}

int PossibleMove::getPosTo() const {
    return posTo;
}