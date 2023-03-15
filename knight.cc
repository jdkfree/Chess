#include "knight.h"
#include "move.h"
#include "gameboard.h"
#include <iostream>

Knight::Knight (int currPos, char symbol, bool white, GameBoard& board) : Piece(currPos, symbol, white, board) {}

bool Knight::isValidMove (int posTo) {
    int start = posTo; // (start always lower)
    int end = currPos; // moving up 

    if (posTo > currPos){ 
        start = currPos; // moving down  
        end = posTo;
    }

    if (board.isOccupied(posTo) && board.getPieceAt(posTo)->isWhite() == white) {
            return false;
    }


    if (start + 6 == end || start + 10 == end){ // move should be one row above
        if (end/8 != start/8 + 1) {
            return false;
        }
    } else if (start + 15 == end || start + 17 == end){ // should be two rows above
        if (end/8 != start/8 + 2) {
            return false;
        }
    } else { 
        return false; 
    }
    return true;
}

bool Knight::canCapturePieceAt (int posTo) {
    return isValidMove(posTo);
}