#include "game.h"
#include "gameboard.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "textdisplay.h"
#include "piece.h"
#include "computer1.h"
#include "computer2.h"
#include "computer3.h"
#include "player.h"
#include "human.h"
#include "graphicaldisplay.h"
#include "move.h"

int findBoardIndex(std::string s){
    return ((int)s[0] - 97)  + ((int)s[1] - 49) * 8;
}

Game::Game() : gameBoard{}{
    white = nullptr;
    black = nullptr; 
    whitesTurn = true; 
    gameRunning = false;
    setupDone = false;
}

Game::~Game() {
    delete white;
    delete black;
}

bool Game::isWhitesTurn() const {
    return whitesTurn;
}

bool Game::isGameRunning() const {
    return gameRunning;
}

bool Game::isSetupDone() const {
    return setupDone;
}

void Game::setWhitesTurn(bool white) {
    whitesTurn = white;
}

void Game::setGameRunning(bool game) {
    gameRunning = game;
}

void Game::setSetupDone (bool done) {
    setupDone = done;
}

void Game::endGame() {
    gameRunning = false;
    setupDone = false;
    gameBoard.deleteBoard();
    graphicalDisplay.createXwindow();
    // delete xwindow too
    whitesTurn = true;
    graphicalDisplay.setDrewBoard(false);
    boardExists = false;
}

bool Game::initializePlayers(std::string whitePlayer, std::string blackPlayer) {
    if (whitePlayer == "human") {
        Player* tempWhite = new Human(true, gameBoard);
        delete white;
        white = tempWhite;
    } else if (whitePlayer == "computer1"){
        Player* tempWhite = new Computer1(true, gameBoard);
        delete white;
        white = tempWhite;
    } else if (whitePlayer == "computer2"){
        Player* tempWhite = new Computer2(true, gameBoard);
        delete white;
        white = tempWhite;
    } else if (whitePlayer == "computer3"){
        Player* tempWhite = new Computer3(true, gameBoard);
        delete white;
        white = tempWhite;
    } else {
        return false;
    }

    if (blackPlayer == "human") {
        Player* tempBlack = new Human(false, gameBoard);
        delete black;
        black = tempBlack;
    } else if (blackPlayer == "computer1"){
        Player* tempBlack = new Computer1(false, gameBoard);
        delete black;
        black = tempBlack;
    } else if (blackPlayer == "computer2"){
        Player* tempBlack = new Computer2(false, gameBoard);
        delete black;
        black = tempBlack;
    } else if (blackPlayer == "computer3"){
        Player* tempBlack = new Computer3(false, gameBoard);
        delete black;
        black = tempBlack;
    } else {
        return false;
    }
    ////////////
    return true;
}

void Game::initializeDefaultGame() {
    gameBoard.setPiece(new Rook(0, 'R', true, gameBoard));
    gameBoard.setPiece(new Rook(7, 'R', true, gameBoard));
    gameBoard.setPiece(new Knight(1, 'N', true, gameBoard));
    gameBoard.setPiece(new Knight(6, 'N', true, gameBoard));
    gameBoard.setPiece(new Bishop(2, 'B', true, gameBoard));
    gameBoard.setPiece(new Bishop(5, 'B', true, gameBoard));
    gameBoard.setPiece(new Queen(3, 'Q', true, gameBoard));
    gameBoard.setPiece(new King(4, 'K', true, gameBoard));

    for (int i = 8; i < 16; i++){
        gameBoard.setPiece(new Pawn(i, 'P', true, gameBoard));
    }

    gameBoard.setPiece(new Rook(56, 'r', false, gameBoard));
    gameBoard.setPiece(new Rook(63, 'r', false, gameBoard));
    gameBoard.setPiece(new Knight(57, 'n', false, gameBoard));
    gameBoard.setPiece(new Knight(62, 'n', false, gameBoard));
    gameBoard.setPiece(new Bishop(58, 'b', false, gameBoard));
    gameBoard.setPiece(new Bishop(61, 'b', false, gameBoard));
    gameBoard.setPiece(new Queen(59, 'q', false, gameBoard));
    gameBoard.setPiece(new King(60, 'k', false, gameBoard));

    for (int i = 48; i < 56; i++){
        gameBoard.setPiece(new Pawn(i, 'p', false, gameBoard));
    }
}

void Game::makeMove() {
    Move *move;
    if (whitesTurn)
        move = white->makeAMove();
    else
        move = black->makeAMove();
    
    if (move != nullptr) {
        if (gameRunning) {
            gameBoard.addMove(move);
            display();
           // gameBoard.addMove(move);
        }
        if (gameBoard.getPlayersKing(!whitesTurn)->isKingInCheck()){ // if the opposing player is in check
            if (whitesTurn){ // if its whites turn, check black
                if (black->hasValidMove()) {
                    std::cout << "Black is in check.\n";
                } else {
                    std::cout << "Checkmate! White wins!\n";
                    white->hasWonGame();
                    endGame();
                }
            } else {
                if (white->hasValidMove()) {
                    std::cout << "White is in check.\n";
                } else {
                    std::cout << "Checkmate! Black wins!\n";
                    black->hasWonGame();
                    endGame();
                }
            }
        } else {
            if (whitesTurn){ // if its whites turn, check black
                if (!black->hasValidMove()) {
                    std::cout << "Stalemate!";
                    white->hasDrawnGame();
                    black->hasDrawnGame();
                    endGame();
                }
            } else {
                if (!white->hasValidMove()) {
                    std::cout << "Stalemate!";
                    white->hasDrawnGame();
                    black->hasDrawnGame();
                    endGame();
                }
            }
        }
        if (gameRunning) {
            whitesTurn = !whitesTurn;
        }
    }
}

bool Game::addPiece(std::string piece, std::string pos) {
    bool isWhite;
    ((int)piece[0] <= 90) ? isWhite = true : isWhite = false;

    if (piece == "R" || piece == "r") 
        gameBoard.setPiece(new Rook(findBoardIndex(pos), piece[0], isWhite, gameBoard));
    else if (piece == "B" || piece == "b")
        gameBoard.setPiece(new Bishop(findBoardIndex(pos), piece[0], isWhite, gameBoard));
    else if (piece == "N" || piece == "n")
        gameBoard.setPiece(new Knight(findBoardIndex(pos), piece[0], isWhite, gameBoard));
    else if (piece == "K" || piece == "k")
        gameBoard.setPiece(new King(findBoardIndex(pos), piece[0], isWhite, gameBoard));
    else if (piece == "Q" || piece == "q")
        gameBoard.setPiece(new Queen(findBoardIndex(pos), piece[0], isWhite, gameBoard));
    else if (piece == "P" || piece == "p")
        gameBoard.setPiece(new Pawn(findBoardIndex(pos), piece[0], isWhite, gameBoard));
    else {
       return false;
    }
    if (boardExists){
        graphicalDisplay.redrawSquare(findBoardIndex(pos));
        graphicalDisplay.drawPiece(findBoardIndex(pos));
    }
    boardExists = true;
    return true;
}

void Game::removePiece(std::string pos) {
    if (gameBoard.isOccupied(findBoardIndex(pos))) {
        gameBoard.removePieceAt(findBoardIndex(pos));
        graphicalDisplay.redrawSquare(findBoardIndex(pos));
        display();
    }
}

void Game::resign() {
    if (whitesTurn){
        std::cout << "Black Wins!\n";
        black->hasWonGame();
    } else {
        std::cout << "White Wins!\n";
        white->hasWonGame();
    }
    endGame();
}

void Game::printScoreboard() {
    std::cout << "Final Score: \nWhite: ";

    if (white != nullptr)
        std::cout << white->getPoints();
    else
        std::cout << "0";
    
    std::cout << "\nBlack: ";

    if (black != nullptr)
        std::cout << black->getPoints() << std::endl;
    else 
        std::cout << "0" << std::endl;
}

void Game::display() {
    textDisplay.notify();
    graphicalDisplay.notify();
}

void Game::switchTurns() {
    whitesTurn = !whitesTurn;
}

bool Game::canExitSetupMode() {
    return gameBoard.validBoard();
}