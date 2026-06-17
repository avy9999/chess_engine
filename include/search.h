#pragma once

#include "position.h"
#include "move.h"

class Search{
public:
    static long long nodes;

    static int alphabeta(Position& pos, int depth, int alpha, int beta);
    static Move findBestMove(Position pos, int depth);
    static Move findBestMoveAtDepth(Position pos, int depth, const Move& pvmove);
    static int scoreMove(const Position& pos, const Move& move);
    static int quiescence(
        Position& pos,
        int alpha,
        int beta
    );
};