#pragma once

#include "position.h"
#include "move.h"

class Search{
public:
    static long long nodes;

    static int minimax(Position pos, int depth);
    static Move findBestMove(Position pos, int depth);
};