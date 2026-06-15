#include "iostream"
#include "algorithm"
#include "../include/search.h"
#include "../include/evaluator.h"
#include "../include/movegenerator.h"

long long Search::nodes = 0;


// alphabeta algorithm for a given depth
int Search::alphabeta(Position pos, int depth, int alpha, int beta){

    // increase node on every call
    Search::nodes++;

    if(depth == 0){
        return Evaluator::evaluate(pos);
    }

    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);
    // std::cout << moves.size() << "\n";

    // sort moves according to capture scores
    std::sort(
        moves.begin(),
        moves.end(),
        [&](const Move& a, const Move& b){
            return Search::scoreMove(pos, a) >
                Search::scoreMove(pos, b);
        }
    );

    if (generator.isCheckmate(pos)){
        if (pos.sideToMove=='w'){
            return -100000 - depth;
        } else{
            return 100000 + depth;
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
            int score = alphabeta(copy, depth - 1, alpha, beta);
            best = std::max(best, score);
            alpha = std::max(alpha, best);
            if (beta <= alpha){
                break;
            }
        }
        return best;
    }
    else{
        int best = 1000000;
        for(const auto& move : moves){
            Position copy = pos;
            generator.makeMove(copy, move);
            int score = alphabeta(copy, depth - 1, alpha, beta);
            best = std::min(best, score);
            beta = std::min(beta, best);
            if (beta <= alpha){
                break;
            }
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
            int score = alphabeta(
                copy,
                depth - 1,
                -1000000,
                1000000
            );
            if (score > bestScore){
                bestMove = move;
                bestScore = score;
            }
            std::cout
            << move.fromRow << "," << move.fromCol
            << " -> "
            << move.toRow << "," << move.toCol
            << " score = "
            << score << "\n";
        }

    } else {        
        for (const auto& move : moves){
            Position copy = pos;
            generator.makeMove(copy, move);
            int score = alphabeta(
                copy,
                depth - 1,
                -1000000,
                1000000
            );
            if (score < bestScore){
                bestMove = move;
                bestScore = score;
            }
            std::cout
            << move.fromRow << "," << move.fromCol
            << " -> "
            << move.toRow << "," << move.toCol
            << " score = "
            << score << "\n";
        }
    }
    return bestMove;
}

// a simple function to measure capture move score
int Search::scoreMove(const Position& pos, const Move& move){
    char target = pos.board[move.toRow][move.toCol];
    
    if (target != '.'){
        char piece = pos.board[move.fromRow][move.fromCol];
        return Evaluator::getPieceValue(target) - Evaluator::getPieceValue(piece);
    }

    return 0;
}