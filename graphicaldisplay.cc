#include "graphicaldisplay.h"
#include "gameboard.h"
#include "piece.h"
#include "move.h"

void GraphicalDisplay::createXwindow() {
    Xwindow* tempXwindow = new Xwindow (450, 450);
    delete xwindow;
    xwindow = tempXwindow;
}

GraphicalDisplay::GraphicalDisplay(GameBoard &gameBoard) : gameBoard{gameBoard} {
    xwindow = new Xwindow(450, 450);
}

GraphicalDisplay::~GraphicalDisplay() {
    delete xwindow;
}

void GraphicalDisplay::setDrewBoard(bool drew) {
    drewBoard = drew;
}

void GraphicalDisplay::drawPawn(int color, int x, int y, int size) {
    int xParam = x - size;
    int yParam = y - size;
    
    xwindow->fillRectangle(xParam + 21, yParam + 5, 8, 4, color);
    xwindow->fillRectangle(xParam + 17, yParam + 9, 16, 8, color);
    xwindow->fillRectangle(xParam + 21, yParam + 17, 8, 12, color);
    xwindow->fillRectangle(xParam + 17, yParam + 29, 16, 8, color);
    xwindow->fillRectangle(xParam + 9, yParam + 37, 32, 8, color);
}

void GraphicalDisplay::drawKing(int color, int x, int y, int size) {
    int xParam = x - size;
    int yParam = y - size;
    
    xwindow->fillRectangle(xParam + 9, yParam + 6, 4, 8, color);
    xwindow->fillRectangle(xParam + 13, yParam + 8, 2, 6, color);
    xwindow->fillRectangle(xParam + 37, yParam + 6, 4, 8, color);
    xwindow->fillRectangle(xParam + 35, yParam + 8, 2, 6, color);
    xwindow->fillRectangle(xParam + 23, yParam + 3, 4, 13, color);
    xwindow->fillRectangle(xParam + 19, yParam + 6, 12, 3, color);
    xwindow->fillRectangle(xParam + 9, yParam + 14, 32, 8, color);
    xwindow->fillRectangle(xParam + 16, yParam + 18, 18, 24, color);
    xwindow->fillRectangle(xParam + 17, yParam + 29, 16, 8, color);
    xwindow->fillRectangle(xParam + 11, yParam + 37, 28, 6, color);
    xwindow->fillRectangle(xParam + 7, yParam + 43, 36, 5, color);
}

void GraphicalDisplay::drawQueen(int color, int x, int y, int size) {
    int xParam = x - size;
    int yParam = y - size;
    xwindow->fillRectangle(xParam + 9, yParam + 10, 4, 10, color);
    xwindow->fillRectangle(xParam + 13, yParam + 12, 2, 10, color);
    xwindow->fillRectangle(xParam + 37, yParam + 10, 4, 10, color);
    xwindow->fillRectangle(xParam + 35, yParam + 12, 2, 10, color);
    xwindow->fillRectangle(xParam + 23, yParam + 10, 4, 10, color);
    xwindow->fillRectangle(xParam + 21, yParam + 12, 2, 10, color);
    xwindow->fillRectangle(xParam + 27, yParam + 12, 2, 10, color);
    xwindow->fillRectangle(xParam + 9, yParam + 18, 32, 16, color);
}

void GraphicalDisplay::drawRook(int color, int x, int y, int size) {
    int xParam = x - size;
    int yParam = y - size;
    
    xwindow->fillRectangle(xParam + 9, yParam + 5, 6, 8, color);
    xwindow->fillRectangle(xParam + 18, yParam + 5, 6, 8, color);
    xwindow->fillRectangle(xParam + 29, yParam + 5, 6, 8, color);
    xwindow->fillRectangle(xParam + 38, yParam + 5, 6, 8, color);
    xwindow->fillRectangle(xParam + 9, yParam + 10, 35, 8, color);
    xwindow->fillRectangle(xParam + 13, yParam + 18, 26, 24, color);
    xwindow->fillRectangle(xParam + 9, yParam + 42, 35, 8, color);
}

void GraphicalDisplay::drawKnight(int color, int x, int y, int size) {
    int xParam = x - size;
    int yParam = y - size;
    
    xwindow->fillRectangle(xParam + 13, yParam + 5, 4, 6, color);
    xwindow->fillRectangle(xParam + 32, yParam + 5, 4, 6, color);
    xwindow->fillRectangle(xParam + 11, yParam + 10, 28, 6, color);
    xwindow->fillRectangle(xParam + 10, yParam + 16, 34, 4, color);
    xwindow->fillRectangle(xParam + 9, yParam + 20, 40, 8, color);
    xwindow->fillRectangle(xParam + 10, yParam + 28, 34, 4, color);
    xwindow->fillRectangle(xParam + 11, yParam + 32, 26, 4, color);
    xwindow->fillRectangle(xParam + 15, yParam + 36, 16, 9, color);
    xwindow->fillRectangle(xParam + 13, yParam + 43, 22, 4, color);
    xwindow->fillRectangle(xParam + 11, yParam + 47, 26, 4, color);
}

void GraphicalDisplay::drawBishop(int color, int x, int y, int size) {
    int xParam = x - size;
    int yParam = y - size;
    
    xwindow->fillRectangle(xParam + 21, yParam + 5, 8, 8, color);
    xwindow->fillRectangle(xParam + 17, yParam + 9, 16, 4, color);
    xwindow->fillRectangle(xParam + 13, yParam + 13, 24, 10, color);
    xwindow->fillRectangle(xParam + 17, yParam + 23, 16, 4, color);
    xwindow->fillRectangle(xParam + 21, yParam + 27, 8, 16, color);
    xwindow->fillRectangle(xParam + 14, yParam + 39, 22, 8, color);
    xwindow->fillRectangle(xParam + 11, yParam + 43, 28, 6, color);
}

void GraphicalDisplay::drawBoard() {
    int size = 50;
    int x = 25;
    int y = 25;
    for(int i = 8; i > 0; i --) {
        xwindow->drawString(x - 10, y + 25, std::to_string(i));
        for(int j = (8 * (i - 1)); j < (8 * i); j ++) {
            if ((i + j) % 2 == 0) {
                xwindow->fillRectangle(x, y, size, size, Xwindow::Red);
            } else {
                xwindow->fillRectangle(x, y, size, size, Xwindow::Green);
            }
            x = x + size;
        }
        x = 25;
        y = y + size;
    }
    xwindow->drawString(50, 440, "A");
    xwindow->drawString(100, 440, "B");
    xwindow->drawString(150, 440, "C");
    xwindow->drawString(200, 440, "D");
    xwindow->drawString(250, 440, "E");
    xwindow->drawString(300, 440, "F");
    xwindow->drawString(350, 440, "G");
    xwindow->drawString(400, 440, "H");
    for (int i = 0; i < 64; i ++) {
        if (gameBoard.isOccupied(i)) {
            drawPiece(i);
        }
    }
    drewBoard = true;
}

void GraphicalDisplay::drawPiece(int index) {
    char symbol = gameBoard.getPieceAt(index)->getSymbol();
    int color = (int)symbol < 91 ? Xwindow::White : Xwindow::Black;
    int x = index % 8;
    int y = index / 8;
    if (symbol == 'K' || symbol == 'k') {
        drawKing(color, 75 + (50) * x, 500 - (75 + (50) * y), 50);
    } else if (symbol == 'Q' || symbol == 'q') {
        drawQueen(color, 75 + (50) * x, 500 - (75 + (50) * y), 50);
    } else if (symbol == 'B' || symbol == 'b') {
        drawBishop(color, 75 + (50) * x, 500 - (75 + (50) * y), 50);
    } else if (symbol == 'P' || symbol == 'p') {
        drawPawn(color, 75 + (50) * x, 500 - (75 + (50) * y), 50);
    } else if (symbol == 'R' || symbol == 'r') {
        drawRook(color, 75 + (50) * x, 500 - (75 + (50) * y), 50);
    } else if (symbol == 'N' || symbol == 'n') {
        drawKnight(color, 75 + (50) * x, 500 - (75 + (50) * y), 50);
    }
}

void GraphicalDisplay::redrawSquare(int index) {
    int x, y;
    x = (index % 8) * 50 + 25;
    y = 400 - ((index / 8) * 50 + 25);
    int color;
    if ((index / 8 ) % 2 == 0) {
        if (index % 2 == 0) {
            color = Xwindow::Green;
        }
        else {
            color = Xwindow::Red;
        }
    } else {
        if (index % 2 == 1) {
            color = Xwindow::Green;
        } else {
            color = Xwindow::Red;
        }
    }
    xwindow->fillRectangle(x, y, 50, 50, color);
}

void GraphicalDisplay::notify() {
    if (!drewBoard) {
        drawBoard();
    }
    Move* moveToDraw = gameBoard.lastMove();
    if (moveToDraw != nullptr) {
        int startPos = moveToDraw->getStartPos();
        int endPos = moveToDraw->getEndPos();
        redrawSquare(startPos);
        redrawSquare(endPos);
        drawPiece(endPos);

        // en passant
        if (gameBoard.lastMove() != nullptr && std::abs(gameBoard.lastMove()->getStartPos() - gameBoard.lastMove()->getEndPos()) == 16) { // if the last move was 16 squares
            if (moveToDraw->getPiece()->isWhite() && gameBoard.getPieceAt(endPos)->getSymbol() == 'P' && (endPos == startPos + 7 || endPos == startPos + 9)){ // you are white and took with your pawn
                if (endPos == gameBoard.lastMove()->getEndPos() + 8) { // you took their pawn that just moved 16 squares
                    redrawSquare(endPos - 8); // remove their pawn
                }
            } else if (!moveToDraw->getPiece()->isWhite() && gameBoard.getPieceAt(endPos)->getSymbol() == 'p' && (endPos == startPos - 7 || endPos == startPos - 9)){ // you are not and took with your pawn
                if (endPos == gameBoard.lastMove()->getEndPos() - 8) { // you took their pawn that just moved 16 squares
                    redrawSquare(endPos + 8); // remove their pawn
                }
            }
        }

        // castling
        if ((gameBoard.getPieceAt(endPos)->getSymbol() == 'K' || gameBoard.getPieceAt(endPos)->getSymbol() == 'k')  && std::abs(startPos - endPos) == 2){ // castle
            if (startPos > endPos){
                drawPiece(startPos - 1);
                redrawSquare(startPos - 4);
            }
            else {
                drawPiece(startPos + 1);
                redrawSquare(startPos + 3);
            }
        }

    }
}
    