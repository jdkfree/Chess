CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = chess
OBJECTS = main.o bishop.o gameboard.o king.o knight.o pawn.o piece.o queen.o rook.o textdisplay.o move.o player.o human.o computer1.o possibleMove.o graphicaldisplay.o window.o computer2.o computer3.o game.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
