#ifndef COMPUTER2_H
#define COMPUTER2_H

#include "player.h"
#include "gameboard.h"
#include "move.h"
#include "possibleMove.h"

class Computer2 : public Player {
    public:
    Computer2(bool white, GameBoard& gameBoard);
    virtual Move* makeAMove() override;
    std::vector<PossibleMove*> generateMoves(); 
    std::vector<PossibleMove*> generatePreferredMoves();
    virtual bool isHuman() const override; 
};
#endif