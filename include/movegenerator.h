#pragma once
#include <vector>
#include "move.h"
#include "position.h"

class MoveGenerator {
    public:
        std::vector<Move> generateKnightMoves(const Position& pos);
        std::vector<Move> generateKingMoves(const Position& pos);
        std::vector<Move> generatePawnMoves(const Position& pos);
        std::vector<Move> generateBishopMoves(const Position& pos);
        std::vector<Move> generateRookMoves(const Position& pos);
        std::vector<Move> generateQueenMoves(const Position& pos);
};