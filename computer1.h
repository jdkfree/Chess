#ifndef COMPUTER1_H
#define COMPUTER1_H

#include "player.h"
#include "gameboard.h"
#include "move.h"
#include "possibleMove.h"

class Computer1 : public Player {
    public:
    Computer1(bool white, GameBoard& gameBoard);
    virtual Move* makeAMove() override;
    std::vector<PossibleMove*> generateMoves(); 
    virtual bool isHuman() const override; 
};
#endif