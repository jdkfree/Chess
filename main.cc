#include <iostream>
#include <string>
#include "game.h"

int main () {
    Game game = Game();
    std::string cmd;

    while (std::cin >> cmd){
        if (cmd == "game"){ // make so cant start game while game is running i think
            if (game.isGameRunning()){
                std::cout << "Sorry, a game is already running. Finish the current game first by checkmate, stalemate, or resignation to start a new game.\n";
                continue;
            }
            std::string whiteP, blackP;
            std::cin >> whiteP >> blackP;

            if (!game.initializePlayers(whiteP, blackP)) {
                std::cout << "Sorry, couldn't start game. Please enter in 'game white-player black-player', with white-player and black-player " 
                            << "each being 'human', 'computer1', computer2', or 'computer3'.\n\n";
                continue;
            }
            if (!game.isSetupDone()){
                game.initializeDefaultGame();
            }
            game.setGameRunning(true);
            game.display();
        } else if (cmd == "move") { // no input error checking done
            if (game.isGameRunning()){
                game.makeMove();
            } else {
                std::cout << "Sorry, no game is currently running.\n";
            }
        } else if (cmd == "setup") {
            if (game.isGameRunning()) {
                std::cout << "Sorry, cannot enter setup while a game is already runningg. Finish the current game first by checkmate, stalemate, or resignation to start a new game.\n";
                continue;
            } else {
                game.setSetupDone(true);
                std::cout << "Welcome to setup. To add a piece, enter '+ [piece] [square]'. To remove a piece, enter '- [square]'.\n"
                          << " [piece] is 'P' or 'p' for pawn, 'B' or 'b' for bishop, 'R' or'r' for rook, 'N' or'n' for knight, 'Q' or 'q' for queen,"
                          << " or 'K' or 'k' for king.\n Note that a captial letter corresponds to a white piece, and a lowercase letter corresponds to a black piece."
                          << " [square] represents the board position in traditional chess mapping (i.e. e4, b8 , f1).\n"
                          << " To set which player will go first, enter '= [colour]', where [colour] is white or black.\n";
                while (cmd != "done"){
                    std::cin >> cmd;
                    if (cmd == "+"){
                        std::string piece;
                        std::string pos;
                        std::cin >> piece >> pos;
                        if (!game.addPiece(piece,pos)) {
                            std::cout << "Sorry, that isn't a valid piece. Please enter 'P' or 'p' for pawn, 'B' or 'b' for bishop, 'R' or'r' for rook, 'N' or'n' for knight, 'Q' or 'q' for queen,\n"
                                      << " or 'K' or 'k' for king. Note that a captial letter corresponds to a white piece, and a lowercase letter corresponds to a black piece.\n";
                            continue;
                        }
                        game.display();
                    } else if (cmd == "-"){
                        std::string pos;
                        std::cin >> pos;
                        game.removePiece(pos);
                    } else if (cmd == "=") {
                        std::string color;
                        std::cin >> color;
                        if (color == "white") {
                            std::cout << " White goes first.\n";
                            game.setWhitesTurn(true);
                        } else if (color == "black") {
                            std::cout << "Black goes first.\n";
                            game.setWhitesTurn(false);
                        } else {
                            std::cout << "Please enter 'white' or 'black' after the  '='.\n";
                        }
                    } else if (cmd == "done"){
                        if (!game.canExitSetupMode()) {
                            std::cout << "Please continue setup.\n";
                            cmd = "";
                        }
                    }
                }
            }
        } else if (cmd == "resign"){
            if (game.isGameRunning()) {
                game.resign();
            } else {
                std::cout << "Sorry, there is no game running.\n";
            }
        } else {
            std::cout << "Sorry, that isn't a valid command.\n";
        }
    }
    game.printScoreboard();
}
