#include "human.h"
#include "player.h"
#include "gameboard.h"
#include "move.h"
#include <iostream>
#include <string>
#include <cmath>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"

Human::Human (bool white, GameBoard& gameBoard) : Player(white, gameBoard) {}

Move* Human::makeAMove () {
    std::string readPosFrom, readPosTo; 
    std::cin >> readPosFrom >> readPosTo;
    int posFrom, posTo;

    posFrom = ((int)readPosFrom[0] - 97)  + ((int)readPosFrom[1] - 49) * 8;
    posTo = ((int)readPosTo[0] - 97)  + ((int)readPosTo[1] - 49) * 8;

    return moveSemantics(posFrom, posTo);
}

bool Human::isHuman() const {
    return true;
}