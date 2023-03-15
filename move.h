#ifndef MOVE_H
#define MOVE_H

class Piece;

class Move {
    private:
    int startPos;
    int endPos;
    Piece* piece;
    Piece* capturedPiece;

    public:
    Move(int startPos, int endPos, Piece* piece, Piece* capturedPiece);
    ~Move();
    int getStartPos() const;
    int getEndPos() const;
    Piece* getPiece() const;
    Piece* getCapturedPiece() const;
};
#endif
