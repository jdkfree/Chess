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
#include "computer2.h"
#include <random>
#include <ctime>

Computer2::Computer2 (bool white, GameBoard& gameBoard) : Player(white, gameBoard) {}

std::vector<PossibleMove*> Computer2::generatePreferredMoves(){ 
    std::vector<PossibleMove*> temp;
    bool captureOrCheck = false;
    bool garbage = false;

    for (Piece* currPiece : gameBoard.getPlayersPieces(getWhite())){
        for (int i = 0; i <= 63; i ++){
            if (currPiece->canMove(i, captureOrCheck, garbage)){
                if (captureOrCheck){
                    temp.emplace_back(new PossibleMove(currPiece, currPiece->getCurrPos(), i));
                }
            }
            captureOrCheck = false;
        }
    }
    return temp;
}

std::vector<PossibleMove*> Computer2::generateMoves(){

    std::vector<PossibleMove*> temp = generatePreferredMoves(); 

    if (temp.empty()){
        bool garbage;
        bool garbage2 = false;
        for (Piece* currPiece : gameBoard.getPlayersPieces(getWhite())){
            for (int i = 0; i <= 63; i ++)
                if (currPiece->canMove(i, garbage, garbage2)){
                    temp.emplace_back(new PossibleMove(currPiece, currPiece->getCurrPos(), i));
                }
        }
    }
    
    return temp;
}

Move* Computer2::makeAMove () {
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

bool Computer2::isHuman() const {
    return false;
}