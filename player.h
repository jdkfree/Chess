#ifndef PLAYER_H
#define PLAYER_H

#include "gameboard.h"
#include "move.h"
#include "piece.h"

class Player {
    protected:
        bool white;
        double points = 0;
        int level;
        GameBoard& gameBoard;


    public:
        Player(bool white, GameBoard& gameBoard);
        void hasWonGame();
        void hasDrawnGame();
        double getPoints () const;
        virtual ~Player() = 0;
        virtual Move* makeAMove () = 0; 
        bool getWhite() const;
        Move* moveSemantics(int posFrom, int posTo);
        virtual bool isHuman() const = 0; 
        bool hasValidMove() const;
};
#endif
