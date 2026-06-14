#include "iostream"
#include "algorithm"
#include "../include/search.h"
#include "../include/evaluator.h"
#include "../include/movegenerator.h"

long long Search::nodes = 0;


// minimax algorithm for a given depth
int Search::minimax(Position pos, int depth){

    // increase node on every call
    Search::nodes++;

    if(depth == 0){
        return Evaluator::evaluate(pos);
    }

    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);
    // std::cout << moves.size() << "\n";

    if (generator.isCheckmate(pos)){
        if (pos.sideToMove=='w'){
            return -100000;
        } else{
            return 100000;
        }
    }

    if (generator.isStalemate(pos)){
        return 0;
    }

    if(pos.sideToMove == 'w'){
        int best = -1000000;
        for(const auto& move : moves){
            Position copy = pos;
            generator.makeMove(copy, move);
            int score = minimax(copy, depth - 1);
            best = std::max(best, score);
        }
        return best;
    }
    else{
        int best = 1000000;
        for(const auto& move : moves){
            Position copy = pos;
            generator.makeMove(copy, move);
            int score = minimax(copy, depth - 1);
            best = std::min(best, score);
        }
        return best;
    }
}

Move Search::findBestMove(Position pos, int depth){
    // sets nodes to 0
    Search::nodes = 0;

    // generate all legal moves
    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);

    if(moves.empty()){
        return Move(-1, -1, -1, -1);
    }
    
    Move bestMove = moves[0];
    int bestScore = pos.sideToMove == 'w' ? -1000000 : 1000000;

    // searches for the best move using minimax
    if (pos.sideToMove == 'w'){
        for (const auto& move : moves){
            Position copy = pos;
            generator.makeMove(copy, move);
            int score = minimax(copy, depth-1);
            if (score > bestScore){
                bestMove = move;
                bestScore = score;
            }
        }

    } else {        
        for (const auto& move : moves){
            Position copy = pos;
            generator.makeMove(copy, move);
            int score = minimax(copy, depth-1);
            if (score < bestScore){
                bestMove = move;
                bestScore = score;
            }
        }
    }
    return bestMove;
}