#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
#include "gameboard.h"
#include "move.h"

class Human : public Player {
    public:
    Human(bool white, GameBoard& gameBoard);
    virtual Move* makeAMove() override;
    virtual bool isHuman() const override; 
};
#endif