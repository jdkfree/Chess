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
#include "computer3.h"
#include <random>
#include <ctime>

Computer3::Computer3 (bool white, GameBoard& gameBoard) : Player(white, gameBoard) {}


// will first try to see if there are moves that avoid capture AND capture opposing piece or check, and if not just goes for the latter.
std::vector<PossibleMove*> Computer3::generatePreferredMoves(){ 
    std::vector<PossibleMove*> temp;
    bool captureOrCheck = false;
    bool avoidsCapture = true;

    for (Piece* currPiece : gameBoard.getPlayersPieces(getWhite())){
        for (int i = 0; i <= 63; i ++){
            avoidsCapture = true;
            if (currPiece->canMove(i, captureOrCheck, avoidsCapture)){
                if (captureOrCheck && avoidsCapture){ // avoids capture AND capture/checks
                    temp.emplace_back(new PossibleMove(currPiece, currPiece->getCurrPos(), i));
                }
            }
            captureOrCheck = false;
        }
    }

    //std::cout <<"OOGA BOOGA BOOGA\n";
    if (!temp.empty()){
        return temp;
    }

    std::cout << "\n\n\n";
    avoidsCapture = false;
    for (Piece* currPiece : gameBoard.getPlayersPieces(getWhite())){
        for (int i = 0; i <= 63; i ++){
            avoidsCapture = true;
            if (currPiece->canMove(i, captureOrCheck, avoidsCapture)){
                if (captureOrCheck || avoidsCapture){ //avoids capture OR capture/check
                    temp.emplace_back(new PossibleMove(currPiece, currPiece->getCurrPos(), i));
                }
            }
            captureOrCheck = false;
        }
    }

    return temp;
}

std::vector<PossibleMove*> Computer3::generateMoves(){
    std::vector<PossibleMove*> temp = generatePreferredMoves(); 

    if (temp.empty()){
        bool garbage, garbage2 = false;
        for (Piece* currPiece : gameBoard.getPlayersPieces(getWhite())){
            for (int i = 0; i <= 63; i ++)
                if (currPiece->canMove(i, garbage, garbage2)){
                    temp.emplace_back(new PossibleMove(currPiece, currPiece->getCurrPos(), i));
                }
        }
    }
    
    return temp;
}

Move* Computer3::makeAMove () {
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

bool Computer3::isHuman() const {
    return false;
}