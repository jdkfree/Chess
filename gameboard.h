#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include "move.h"

class Piece;

class GameBoard {
    private:
    Piece* board[64] = {};
    std::vector<Piece*> capturedPieces;
    std::vector<Move*> moves;

    public:
    GameBoard();
    ~GameBoard();
    Piece* getPieceAt (int pos) const;
    void setPieceAt (Piece* piece, int pos);
    void setPiece (Piece* piece);
    Piece* removePieceAt (int pos);
    bool isOccupied (int pos) const;
    std::vector<Piece*> getPlayersPieces (bool isWhite) const;
    std::vector<Piece*> getOpponentsPieces (bool isWhite) const;
    std::vector<Piece*> getCapturedPieces () const;
    Piece* getPlayersKing (bool isWhite) const;
    void addCapturedPiece (Piece* piece);
    bool validBoard() const; 

    void addMove(Move* move);
    Move* lastMove() const;
    void deleteBoard();
};
#endif
