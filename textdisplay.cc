#include "textdisplay.h"
#include <iostream>
#include "piece.h"

TextDisplay::TextDisplay(GameBoard& gameBoard) : gameBoard{gameBoard} {}

void TextDisplay::notify () {
    for(int i = 8; i > 0; i --) {
        std::cout << i << " ";
        for(int j = (8 * (i - 1)); j < (8 * i); j ++) {
            if (gameBoard.isOccupied(j)) {
                std::cout << gameBoard.getPieceAt(j)->getSymbol();
            }
            else if ((i + j) % 2 == 0) {
                std::cout << " ";
            } else {
                std::cout << "_";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n  abcdefgh\n";
}