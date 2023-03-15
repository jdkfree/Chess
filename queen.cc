#include "queen.h"
#include "move.h"
#include <iostream>

Queen::Queen (int currPos, char symbol, bool white, GameBoard& board) : Piece(currPos, symbol, white, board) {}

bool Queen::isValidMove (int posTo) {
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

    int rankDiff = end/8 - start/8;

    if (std::abs(start - end) == (9 * rankDiff)) { // moving bottom left to top right (or vice versa)
        if (leftDown) {
            for (int i = end - 9; i > start; i -= 9) {
                if (board.isOccupied(i)) 
                    return false;
            }
        } else {
            for (int i = start + 9; i < end; i += 9) {
                if (board.isOccupied(i)) 
                    return false;
            }
        }
    } else if (std::abs(start - end) == (7 * rankDiff)) { // moving bottom right to top left (or vv)
        if (leftDown) {
            for (int i = end - 7; i > start; i -= 7) {
                if (board.isOccupied(i)) // something is in the way
                    return false;
            }

        } else {
            for (int i = start + 7; i < end; i +=7) {
                if (board.isOccupied(i)) // something is in the way
                    return false;
            }
        }
    } else if (posTo % 8 == currPos % 8) { // the q is moving along the file
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
            for (int i = start + 1; i < end; i -= 1) {
                if (board.isOccupied(i)) // something is in the way
                    return false;
            }
            
        }
    } else { return false; }
        
    return true;
}

bool Queen::canCapturePieceAt (int posTo) {
    // temporary remove piece at pos to
    // store result in variable
    // put the piece back at pos to
    return isValidMove(posTo);
}