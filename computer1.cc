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

#include "possibleMove.h"
#include "computer1.h"
#include <random>
#include <ctime>

Computer1::Computer1 (bool white, GameBoard& gameBoard) : Player(white, gameBoard) {}

std::vector<PossibleMove*> Computer1::generateMoves(){
    std::vector<PossibleMove*> temp;
    bool garbage = false, garbage2 = false;
    for (Piece* currPiece : gameBoard.getPlayersPieces(getWhite())){
        for (int i = 0; i <= 63; i ++)
            if (currPiece->canMove(i, garbage, garbage2)){
                temp.emplace_back(new PossibleMove(currPiece, currPiece->getCurrPos(), i));
            }
    }
    return temp;
}

Move* Computer1::makeAMove () {
    std::vector<PossibleMove*> moves = generateMoves();
    
    if (moves.size() == 0)
        return nullptr;

    srand(time(0));
    PossibleMove* temp = moves[std::rand() % moves.size()];
    int tempPosTo = temp->getPosTo(), tempPosFrom = temp->getPosFrom();
    for (PossibleMove* possibleMove: moves) {
        delete possibleMove;
    }
    return moveSemantics(tempPosFrom, tempPosTo);
}

bool Computer1::isHuman() const {
    return false;
}