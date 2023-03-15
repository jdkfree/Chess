#include "rook.h"
#include "move.h"
#include "gameboard.h"
#include <iostream>

Rook::Rook (int currPos, char symbol, bool white, GameBoard& board) : Piece(currPos, symbol, white, board) {}

bool Rook::isValidMove (int posTo){
    int start = posTo;
    int end = currPos;
    bool leftDown = true;

    if (currPos < posTo) { // rook moving down (assumption is that rook is moving up)
        start = currPos;
        end = posTo;
        leftDown = false; 
    }

    if (board.isOccupied(posTo) && board.getPieceAt(posTo)->isWhite() == white) {
        return false;
    } 

    if (posTo % 8 == currPos % 8) { // the rook is moving along the file
        if (leftDown) {
            for (int i = end - 8; i > start; i -= 8) {
                if (board.isOccupied(i)) // something is in the way
                    return false;
            }

        } else {
            for (int i = start + 8; i < end; i += 8) {
                if (board.isOccupied(i)) // something is in the way
                    return false;
            }
        }
    } else if (posTo / 8 == currPos / 8) { // moving along the rank
        if (leftDown) {
            for (int i = end - 1; i > start; i -= 1) {
                if (board.isOccupied(i)) // something is in the way
                    return false;
            }
        } else {
            for (int i = start + 1; i < end; i += 1) {
                if (board.isOccupied(i)) // something is in the way
                    return false;
            }
        }      
    } else { 
        return false; 
    }

    return true;
}

bool Rook::canCapturePieceAt (int posTo)  {
    return isValidMove(posTo);
}