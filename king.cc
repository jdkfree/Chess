#include "king.h"
#include "move.h"
#include "gameboard.h"
#include <iostream>

King::King (int currPos, char symbol, bool white, GameBoard& board) : Piece(currPos, symbol, white, board) {}

bool King::canCastle (int posTo) { // check if path is empty
    if (isKingInCheck())
        return false;

    if (!takenFirstMove && currPos - 2 == posTo && board.isOccupied(currPos -4) && !board.getPieceAt(currPos - 4)->hasTakenFirstMove()) {
        for (int i = currPos - 1; i > currPos - 4; i --) // in between must be clear
            if (board.isOccupied(i))
                return false;
        
        board.setPieceAt(this, currPos - 1); // one over not in check
        if (isKingInCheck()) {
            board.setPieceAt (this, currPos + 1);
            board.removePieceAt(currPos - 1);
            return false;
        } else {
            board.setPieceAt(this, currPos - 1);
            if (isKingInCheck()) {
                board.setPieceAt (this, currPos + 2);
                board.removePieceAt(currPos - 2);
                return false;
            }
            board.setPieceAt (this, currPos + 2);
            board.removePieceAt(currPos - 2);
        }
    } else if (!takenFirstMove && currPos + 2 == posTo && board.isOccupied(currPos + 3) && !board.getPieceAt(currPos + 3)->hasTakenFirstMove()){
        for (int i = currPos + 1; i < currPos + 3; i ++)
            if (board.isOccupied(i))
                return false;

        board.setPieceAt(this, currPos + 1);
        if (isKingInCheck()) {
            board.setPieceAt (this, currPos - 1);
            board.removePieceAt(currPos + 1);
            return false;
        } else {
            board.setPieceAt(this, currPos + 1);
            if (isKingInCheck()) {
                board.setPieceAt (this, currPos - 2);
                board.removePieceAt(currPos + 2);
                return false;
            }
            board.setPieceAt (this, currPos - 2);
            board.removePieceAt(currPos + 2);
        }
    } else {
        return false;
    }

    return true;
}

bool King::isValidMove (int posTo) {
    return (canCapturePieceAt (posTo) || canCastle(posTo));
}

bool King::canCapturePieceAt (int posTo) {
    int start = posTo;
    int end = currPos;

    if (currPos < posTo) { // rook moving down (assumption is that rook is moving up)
        start = currPos;
        end = posTo;
    }

    int rankDiff = end/8 - start/8;

    if (((start + 1 != end || rankDiff != 0) && ((start + 7 != end && start + 8 != end && start + 9 != end) || rankDiff != 1))
        || (board.isOccupied(posTo) && board.getPieceAt(posTo)->isWhite() == white)) {
            return false;
    }
    
    return true;
}