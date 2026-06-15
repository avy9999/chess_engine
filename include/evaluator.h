#pragma once

#include "position.h"

class Evaluator {
public:
    static int evaluate(const Position& pos);
    static int getPieceValue(char piece);
};