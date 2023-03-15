#include "piece.h"
#include "gameboard.h"
#include "move.h"
#include <iostream>

Piece::Piece(int currPos, char symbol, bool white, GameBoard& board) : 
currPos{currPos}, symbol{symbol}, white{white}, board{board} {}

Piece::Piece(const Piece & other) : currPos{other.currPos}, symbol{other.symbol}, white{other.white}, board{other.board} {}

Piece::~Piece() {}

char Piece::getSymbol() const {
    return symbol;
}

void Piece::setCurrPos(int pos) {
    currPos = pos;
}

int Piece::getCurrPos() const {
    return currPos;
}

bool Piece::isWhite() const {
    return white;
}

bool Piece::isCaptured() const {
    return captured;
}

void Piece::setCaptured(bool beenCaptured) {
    captured = beenCaptured;
}

bool Piece::hasTakenFirstMove() const{
    return takenFirstMove;
}

void Piece::setHasTakenFirstMove(bool hasMoved) {
    takenFirstMove = hasMoved;
}

bool Piece::isKingInCheck(){
    Piece* king = board.getPlayersKing(white);
    std::vector<Piece*> opponentsPieces = board.getOpponentsPieces(white);

    for (Piece* opponentsPiece : opponentsPieces) {
        if (opponentsPiece->canCapturePieceAt(king->getCurrPos())) {
            return true;
        }
    }
    return false;
}

Move* Piece::move (int posTo) {

    // We don't even make a move in this case, so just return null.
    if (posTo == currPos) {
        std::cout << "You're trying to move to the same position. Please enter another move.\n" << std::endl;
        return nullptr;
    }

    if (!isValidMove(posTo)) {
        std::cout << "Sorry, that isn't a valid move. Please enter another move.\n";
        return nullptr;
    }

    // We temporarily make the move, and reverse it if the king will be in check after this move.
    Piece* capturedPiece = nullptr;
    if (board.isOccupied(posTo)) {
        // If we got to this point, its implied that the occupied piece is the opponents.
            board.getPieceAt(posTo)->setCaptured(true);
            capturedPiece = board.removePieceAt(posTo); // Remove the piece from the board.
        // Set opponents piece captured attribute to true.
    }
    Move* move = new Move(currPos, posTo, this, capturedPiece); // Make a move object
    board.setPieceAt(this, posTo); // Move the pointer in the array to posTo index.
    // So the move is completed here.
    board.removePieceAt(move->getStartPos());
    if (isKingInCheck()) {
            std::cout << "Sorry, that move puts your king in check. Please enter antoher move.\n";
            board.removePieceAt(move->getEndPos());

            if (capturedPiece != nullptr) {
                // If there was a captured piece, set its current position to the end position of the move.
                capturedPiece->setCurrPos(move->getEndPos());
                board.setPiece(capturedPiece);
            }
            currPos = move->getStartPos(); // Switch the current position to the moves start position.
            // Put the two pieces back on the board.
            board.setPieceAt(this, currPos);
            delete move;
            return nullptr;
    }
    
    if (!takenFirstMove) {
        takenFirstMove = true;
    }
    if (capturedPiece != nullptr) {
        board.addCapturedPiece(capturedPiece);
    }

    return move;
}

bool Piece::canMove(int posTo, bool &captureOrCheck, bool &avoidsCapture) {
    if (posTo == currPos || !isValidMove(posTo)) {
        return false;
    }

    Piece* capturedPiece = nullptr;
    if (board.isOccupied(posTo)) {
        captureOrCheck = true; // check if this is a capturing move
        board.getPieceAt(posTo)->setCaptured(true);
        capturedPiece = board.removePieceAt(posTo); // Remove the piece from the board.
    }

    Move* move = new Move(currPos, posTo, this, capturedPiece); // Make a move object
    board.setPieceAt(this, posTo); // Move the pointer in the array to posTo index.
    board.removePieceAt(move->getStartPos());

    bool temp = true;

    if (isKingInCheck()) {
        temp = false;
    }

    if (board.getPlayersKing(!white)->isKingInCheck()){
        captureOrCheck = true;
    }

    if (avoidsCapture){ // if we care if a move avoids capture or not
        for (Piece* oppPiece : board.getOpponentsPieces(white)){
            for (Piece* playerPiece : board.getPlayersPieces(white)){
                if (oppPiece->canCapturePieceAt(playerPiece->getCurrPos())){
                    avoidsCapture = false;
                    break;
                }
            }

            if (!avoidsCapture){
                break;
            }
        }
    }

    //undo the move
    board.removePieceAt(move->getEndPos());

    if (capturedPiece != nullptr) {
        capturedPiece->setCurrPos(move->getEndPos());
        board.setPiece(capturedPiece);
    }

    currPos = move->getStartPos(); // Switch the current position to the moves start position.
    board.setPieceAt(this, currPos);

    //std::cout << "move is " << currPos << " " << posTo << " " << temp << std::endl;
    delete move;
    return temp;
}