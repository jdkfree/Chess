#ifndef COMPUTER3_H
#define COMPUTER3_H

#include "player.h"
#include "gameboard.h"
#include "move.h"
#include "possibleMove.h"

class Computer3 : public Player {
    public:
    Computer3(bool white, GameBoard& gameBoard);
    virtual Move* makeAMove() override;
    std::vector<PossibleMove*> generateMoves(); 
    std::vector<PossibleMove*> generatePreferredMoves();
    virtual bool isHuman() const override; 
};
#endif