#include "gameboard.h"
#include "piece.h"
#include <iostream>

GameBoard::GameBoard() {}

GameBoard::~GameBoard() {
    for (int i = 0; i < 64; i ++) {
        delete board[i];
    }
    for (Move* move: moves) {
        delete move;
    }
    
    for (Piece* captured: capturedPieces) {
        delete captured;
    }
}

void GameBoard::deleteBoard(){
    for (int i = 0; i < 64; i ++) {
        delete board[i];
        board[i] = nullptr;
    } 
    for (Move* move: moves) {
        delete move;
    }
    moves.clear();
    for (Piece* captured: capturedPieces) {
        delete captured;
    }
}

Piece* GameBoard::getPieceAt (int pos) const {
    return board[pos];
}

void GameBoard::setPieceAt (Piece* piece, int pos) {
    board[pos] = piece;
    piece->setCurrPos(pos);
}

void GameBoard::setPiece (Piece* piece) {
    if (board[piece->getCurrPos()] != nullptr)
        delete removePieceAt(piece->getCurrPos());

    board[piece->getCurrPos()] = piece;
}

Piece* GameBoard::removePieceAt (int pos) {
    Piece* pieceToRemove = board[pos];
    board[pos] = nullptr; 
    return pieceToRemove;
}

    
bool GameBoard::isOccupied (int pos) const {
    return board[pos] != nullptr;
}
    
std::vector<Piece*> GameBoard::getPlayersPieces (bool isWhite) const {
    std::vector<Piece*> playersPieces;
    for (Piece* piece : board) {
        if (piece != nullptr && piece->isWhite() == isWhite) {
            playersPieces.emplace_back(piece);
        }
    }
    return playersPieces;
}
    
std::vector<Piece*> GameBoard::getOpponentsPieces (bool isWhite) const {
    return getPlayersPieces(!isWhite);
}
    
Piece* GameBoard::getPlayersKing (bool isWhite) const {
    for (Piece* piece : board) {
        if (piece != nullptr && ((piece->getSymbol() == 'k' || piece->getSymbol() == 'K') && piece->isWhite() == isWhite)) {
            return piece;
        }
    }
    return nullptr;
}

void GameBoard::addCapturedPiece (Piece* piece) {
    capturedPieces.emplace_back(piece);
}

std::vector<Piece*> GameBoard::getCapturedPieces() const {
    return capturedPieces;
}

bool GameBoard::validBoard () const {
    bool blackK = false, whiteK = false; 
    char symbol;

    for (int i = 0; i <= 63; i++){
        if (isOccupied(i)){
            symbol = getPieceAt(i)->getSymbol();
            if (symbol == 'k') {
                if (blackK){
                    std::cout << "You can only have one black king.\n";
                    return false;
                }
                else {
                    blackK = true;
                    if (getPieceAt(i)->isKingInCheck()){
                        std::cout << "Black's king is in check, cannot start game. ";
                        return false;
                    }
                }
            } else if (symbol == 'K') {
                if(whiteK){
                    std::cout << "You can only have one White king. ";
                    return false;
                }
                else { 
                    whiteK = true;
                     if (getPieceAt(i)->isKingInCheck()){
                        std::cout << "White's king is in check, cannot start game. ";
                        return false;
                    }
                }
            }

            if ((i <= 7 || i >= 56) && (symbol == 'P' || symbol == 'p')){
                std::cout << "There cannot be any pawns on the first or last ranks. ";
                return false;
            }
        }
    }

    if (whiteK == false || blackK == false) {
        std::cout << "Both players must have a king to begin the game. ";
        return false;
    }
    return true; 
    
}

void GameBoard::addMove(Move* move) {
    moves.emplace_back(move);
}

Move* GameBoard::lastMove() const { 
    if (moves.size() == 0)
        return nullptr;
    return moves.back();
}