#include "move.h"
#include "piece.h"

Move::Move(int startPos, int endPos, Piece* piece, Piece* capturedPiece) : 
startPos{startPos}, endPos{endPos}, piece{piece}, capturedPiece{capturedPiece} {}

Move::~Move() {}

int Move::getStartPos() const {
    return startPos;
}

int Move::getEndPos() const {
    return endPos;
}

Piece* Move::getPiece() const {
    return piece;
}

Piece* Move::getCapturedPiece() const {
    return capturedPiece;
}