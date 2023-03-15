#include "pawn.h"
#include "gameboard.h"
#include <cmath>
#include <iostream>

Pawn::Pawn (int currPos, char symbol, bool white, GameBoard& board) : Piece(currPos, symbol, white, board) {}

bool Pawn::isValidMove (int posTo) {
    int start = posTo; // (start always lower)
    int end = currPos; // moving up 
    
    if (white && end > start) {
        return false;
    }
    else if (!white && end < start) {
        return false;
    }

    if (posTo > currPos) { 
        start = currPos; // moving down  
        end = posTo;
    }

    if (canCapturePieceAt(posTo)) {
        return true;
    } else if (start + 8 != end) {
        if (takenFirstMove || start + 16 != end || board.isOccupied((start + end) / 2) || board.isOccupied(posTo))
            return false;
    } else if (start + 8 == end && !board.isOccupied(posTo)) {
        return true;
    }
    else { 
        return false; 
    }
    return true;
}

bool Pawn::enpassant(int posTo){
    if (board.lastMove() == nullptr)
        return false;
        
    if (std::abs(board.lastMove()->getStartPos() - board.lastMove()->getEndPos()) == 16
        && (board.lastMove()->getEndPos() == currPos + 1 || board.lastMove()->getEndPos() == currPos - 1)
        && board.lastMove()->getEndPos() / 8 == currPos / 8) {
            if ((white && (currPos + 7 == posTo || currPos + 9 == posTo)) || (!white && (currPos - 7 == posTo || currPos - 9 == posTo))) {
                return true;
            } 
            // std::cout << "last move start pos" << board.lastMove()->getStartPos() 
            // << " last move end pos " << board.lastMove()->getEndPos() << std::endl;
    }
    return false;
}


bool Pawn::canCapturePieceAt (int posTo) {
    if (white && (currPos + 7 == posTo || currPos + 9 == posTo) && board.isOccupied(posTo) && !board.getPieceAt(posTo)->isWhite()
        && posTo / 8 == currPos / 8 + 1) {
        return true;
    }
    if (!white && (currPos - 7 == posTo || currPos - 9 == posTo) && board.isOccupied(posTo) && board.getPieceAt(posTo)->isWhite()
        && posTo / 8 == currPos / 8 - 1) {
        return true;
    }
    if (enpassant(posTo)){
        return true;
    }
    return false;
}