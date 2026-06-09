#include <iostream>
#include "../include/position.h"

int main() {
    Position pos;
    pos.loadFEN("r3kb1r/pp3Bpp/2p3n1/4P1N1/5P2/BP6/P1b3PP/R2R2K1 b - - 0 17");
    pos.printBoard();
}