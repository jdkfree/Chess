#include "player.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include <iostream>
#include <cmath>

Player::Player(bool white, GameBoard& gameBoard) : white{white}, gameBoard{gameBoard} {}

void Player::hasWonGame(){
    points ++;
}

void Player::hasDrawnGame() {
    points += 0.5;
}

double Player::getPoints () const {
    return points;
}

bool Player::getWhite() const{
    return white;
}

bool Player::hasValidMove() const {
    std::vector<Piece*> pieces = gameBoard.getPlayersPieces(white);
    bool garbage = false, garbage2 = false;
    for (Piece* currPiece : pieces) {
        for (int i = 0; i <= 63; i ++)
            if (currPiece->canMove(i, garbage, garbage2))
                return true;
    }
    return false;
}

Move* Player::moveSemantics(int posFrom, int posTo) {
    if (posFrom > 63 || posFrom < 0 || posTo > 63 || posTo < 0) {
        std::cout << "You've entered an invalid square. Note that the range of positions is [a-h][1-8].\n";
        return nullptr;
    }

    if (!gameBoard.isOccupied(posFrom)) {
        std::cout << "There's no piece at the indicated starting square.\n" ;
        return nullptr;
    }

    if (gameBoard.getPieceAt(posFrom)->isWhite() == white) {
        Move* move = gameBoard.getPieceAt(posFrom)->move(posTo);

        if (move != nullptr){
            // castling
            if ((gameBoard.getPieceAt(posTo)->getSymbol() == 'K' || gameBoard.getPieceAt(posTo)->getSymbol() == 'k')  && std::abs(posFrom - posTo) == 2){ // castle
                if (posFrom > posTo){
                    gameBoard.setPieceAt(gameBoard.getPieceAt(posFrom - 4), posFrom - 1);
                    gameBoard.removePieceAt(posFrom - 4);
                }
                else {
                    gameBoard.setPieceAt(gameBoard.getPieceAt(posFrom + 3), posFrom + 1);
                    gameBoard.removePieceAt(posFrom + 3);
                }
            }

            // en passant
            if (gameBoard.lastMove() != nullptr && std::abs(gameBoard.lastMove()->getStartPos() - gameBoard.lastMove()->getEndPos()) == 16) { // if the last move was 16 squares
                if (white && gameBoard.getPieceAt(posTo)->getSymbol() == 'P' && (posTo == posFrom + 7 || posTo == posFrom + 9)){ // you are white and took with your pawn
                    if (posTo == gameBoard.lastMove()->getEndPos() + 8) { // you took their pawn that just moved 16 squares
                        gameBoard.removePieceAt(posTo - 8); // remove their pawn
                    }
                } else if (!white && gameBoard.getPieceAt(posTo)->getSymbol() == 'p' && (posTo == posFrom - 7 || posTo == posFrom - 9)){ // you are not and took with your pawn
                    if (posTo == gameBoard.lastMove()->getEndPos() - 8) { // you took their pawn that just moved 16 squares
                        gameBoard.removePieceAt(posTo + 8); // remove their pawn
                    }
                }
            }

            
            // pawn promotion
            if ((posTo / 8 == 0 && gameBoard.getPieceAt(posTo)->getSymbol() == 'p') || (posTo / 8 == 7 && gameBoard.getPieceAt(posTo)->getSymbol() == 'P')) {

                if (isHuman()){
                    char promo;
                    std::cout << "What would you like to promote to? Type in 'q' for queen, 'b' for bishop, 'r' for rook, and 'n' for knight.\n";
                    while (std::cin >> promo) {
                        if (promo == 'q'){
                            gameBoard.setPiece(new Queen(posTo, (posTo / 8 == 7) ? 'Q' : 'q', posTo / 8 == 7, gameBoard));
                            break; 
                        } else if (promo == 'b'){
                            gameBoard.setPiece(new Bishop(posTo, (posTo / 8 == 7) ? 'B' : 'b', posTo / 8 == 7, gameBoard));
                            break; 
                        } else if (promo == 'r'){
                            gameBoard.setPiece(new Rook(posTo, (posTo / 8 == 7) ? 'R' : 'r', posTo / 8 == 7, gameBoard));
                            break; 
                        } else if (promo == 'n'){
                            gameBoard.setPiece(new Knight(posTo, (posTo / 8 == 7) ? 'N' : 'n', posTo / 8 == 7, gameBoard));
                            break; 
                        } else {
                            std::cout << "Sorry, that's not a valid response. Type in 'q' for queen, 'b' for bishop, 'r' for rook, and 'n' for knight.";
                        }
                    }
                } else { // computer will default promote to queen
                    gameBoard.setPiece(new Queen(posTo, (posTo / 8 == 7) ? 'Q' : 'q', posTo / 8 == 7, gameBoard));
                }
            }
            return move;
        }
    } else {
        std::cout << "That piece isn't yours.\n" << std::endl;
    }

    return nullptr;
}

Player::~Player() {}