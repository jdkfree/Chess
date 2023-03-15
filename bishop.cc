#include "bishop.h"
#include "piece.h"
#include <iostream>
#include <cmath>

Bishop::Bishop (int currPos, char symbol, bool white, GameBoard& board) : Piece(currPos, symbol, white, board) {}

bool Bishop::isValidMove (int posTo) {
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

    int rankDiff = end / 8 - start / 8;

    if (std::abs(start - end) == (9 * rankDiff)) {
        if (leftDown) {
            for (int i = end - 9; i > start; i -= 9) {
                if (board.isOccupied(i)) {
                    return false;
                }
            }
        } else {
            for (int i = start + 9; i < end; i += 9) {
                if (board.isOccupied(i)) {
                   return false;
                }
            }
        }
    } else if (std::abs(start - end) == (7 * rankDiff)) {
        if (leftDown) {
            for (int i = end - 7; i > start; i -= 7) {
                if (board.isOccupied(i)) {
                   return false;
                }
            }
        } else {
            for (int i = start + 7; i < end; i += 7) {
                if (board.isOccupied(i)) {
                   return false;
                }
            }
        }
    } else { 
        return false; 
    }
    return true;
}

bool Bishop::canCapturePieceAt (int posTo) {
    return isValidMove(posTo);
}