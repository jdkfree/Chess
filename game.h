#ifndef GAME_H
#define GAME_H
#include <string>
#include "gameboard.h"
#include "textdisplay.h"
#include "graphicaldisplay.h"
#include "player.h"

class Game {
    private:
    GameBoard gameBoard = GameBoard();
    TextDisplay textDisplay = TextDisplay(gameBoard);
    GraphicalDisplay graphicalDisplay = GraphicalDisplay(gameBoard);
    Player* white;
    Player* black; 
    bool whitesTurn; 
    bool gameRunning;
    bool setupDone;
    bool boardExists = false;
    
    public:
    Game();
    ~Game();
    void endGame();
    bool isWhitesTurn() const;
    bool isGameRunning() const;
    bool isSetupDone() const;
    void setWhitesTurn(bool white);
    void setGameRunning(bool game);
    void setSetupDone (bool done);
    bool initializePlayers(std::string whitePlayer, std::string blackPlayer);
    void initializeDefaultGame();
    void makeMove();
    void resign();
    void printScoreboard();
    void display();
    bool addPiece (std::string piece, std::string pos);
    void removePiece(std::string pos);
    void switchTurns();
    bool canExitSetupMode();
    
};
#endif