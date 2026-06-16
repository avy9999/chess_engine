#pragma once

#include "position.h"

class Evaluator {
public:
    static int evaluate(const Position& pos);
    static int getPieceValue(char piece);
    static bool isPassedPawn(
        const Position& pos,
        int row,
        int col
    );
    static const int passedPawnBonus[8];
};