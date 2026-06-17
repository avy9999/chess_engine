#include "iostream"
#include "algorithm"
#include "../include/search.h"
#include "../include/evaluator.h"
#include "../include/movegenerator.h"
#include "../include/undoinfo.h"

long long Search::nodes = 0;

// alphabeta algorithm for a given depth
int Search::alphabeta(Position& pos, int depth, int alpha, int beta)
{

    // increase node on every call
    Search::nodes++;

    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);

    if(moves.empty())
    {
        if(generator.isKingInCheck(pos, pos.sideToMove))
        {
            if(pos.sideToMove == 'w')
                return -100000 - depth;
            else
                return 100000 + depth;
        }

        return 0;
    }

    if (depth == 0)
    {
        return quiescence(pos, alpha, beta);
        // return Evaluator::evaluate(pos);
    }

    // sort moves according to capture scores
    std::sort(
        moves.begin(),
        moves.end(),
        [&](const Move &a, const Move &b)
        {
            return Search::scoreMove(pos, a) >
                Search::scoreMove(pos, b);
        });

    if (pos.sideToMove == 'w')
    {
        int best = -1000000;
        for (const auto &move : moves)
        {
            UndoInfo undo;

            generator.makeMove(
                pos,
                move,
                undo);

            int score = alphabeta(
                pos,
                depth - 1,
                alpha,
                beta);

            generator.undoMove(
                pos,
                move,
                undo);

            best = std::max(best, score);
            alpha = std::max(alpha, best);

            if (beta <= alpha)
            {
                break;
            }
        }
        return best;
    }
    else
    {
        int best = 1000000;
        for (const auto &move : moves)
        {
            UndoInfo undo;

            generator.makeMove(
                pos,
                move,
                undo);

            int score = alphabeta(
                pos,
                depth - 1,
                alpha,
                beta);

            generator.undoMove(
                pos,
                move,
                undo);

            best = std::min(best, score);
            beta = std::min(beta, best);

            if (beta <= alpha)
            {
                break;
            }
        }
        return best;
    }
}

Move Search::findBestMove(Position pos, int maxDepth)
{
    Move bestMove;

    Move pvMove;

    for(int depth = 1; depth <= maxDepth; depth++)
    {
        bestMove = findBestMoveAtDepth(pos, depth, pvMove);

        pvMove = bestMove;

        // std::cout
        //     << "Depth "
        //     << depth
        //     << " complete\n";
    }

    return bestMove;
}

Move Search::findBestMoveAtDepth(Position pos, int depth, const Move& pvMove)
{
    // sets nodes to 0
    Search::nodes = 0;

    // generate all legal moves
    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);

    std::sort(
        moves.begin(),
        moves.end(),
        [&](const Move& a, const Move& b){
            return scoreMove(pos, a) >
                scoreMove(pos, b);
        }
    );

    if (pvMove.fromRow != -1)
    {
        auto it = std::find(
            moves.begin(),
            moves.end(),
            pvMove
        );

        if (it != moves.end())
        {
            std::iter_swap(
                moves.begin(),
                it
            );
        }
    }

    if (moves.empty())
    {
        return Move(-1, -1, -1, -1);
    }

    Move bestMove = moves[0];
    int bestScore = pos.sideToMove == 'w' ? -1000000 : 1000000;

    // searches for the best move using minimax
    if (pos.sideToMove == 'w')
    {
        for (const auto &move : moves)
        {
            Position copy = pos;
            MoveGenerator::positionCopies++;
            generator.makeMove(copy, move);
            int score = alphabeta(
                copy,
                depth - 1,
                -1000000,
                1000000);
            if (score > bestScore)
            {
                bestMove = move;
                bestScore = score;
            }
            // std::cout
            //     << move.fromRow << "," << move.fromCol
            //     << " -> "
            //     << move.toRow << "," << move.toCol
            //     << " score = "
            //     << score << "\n";
        }
    }
    else
    {
        for (const auto &move : moves)
        {
            Position copy = pos;
            MoveGenerator::positionCopies++;
            generator.makeMove(copy, move);
            int score = alphabeta(
                copy,
                depth - 1,
                -1000000,
                1000000);
            if (score < bestScore)
            {
                bestMove = move;
                bestScore = score;
            }
        //     std::cout
        //         << move.fromRow << "," << move.fromCol
        //         << " -> "
        //         << move.toRow << "," << move.toCol
        //         << " score = "
        //         << score << "\n";
        }
    }
    // std::cout << "Nodes: " << Search::nodes << "\n";
    return bestMove;
}

// a simple function to measure capture move score
int Search::scoreMove(const Position &pos, const Move &move)
{
    char target = pos.board[move.toRow][move.toCol];

    if (target != '.')
    {
        char piece = pos.board[move.fromRow][move.fromCol];
        return 100 * Evaluator::getPieceValue(target) - Evaluator::getPieceValue(piece);
    }

    return 0;
}


// quiescence function
int Search::quiescence(
    Position& pos,
    int alpha,
    int beta
){
    Search::nodes++;

    int standPat = Evaluator::evaluate(pos);

    return standPat;
    
    if(pos.sideToMove == 'w'){
        if(standPat >= beta)
            return beta;

        alpha = std::max(alpha, standPat);
    }
    else{
        if(standPat <= alpha)
            return alpha;

        beta = std::min(beta, standPat);
    }

    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);

    std::sort(
    moves.begin(),
    moves.end(),
        [&](const Move& a, const Move& b){
            return scoreMove(pos, a) >
                scoreMove(pos, b);
        }
    );

    for(const auto& move : moves){

        // only search captures
        bool isCapture =
            pos.board[move.toRow][move.toCol] != '.';

        if(!isCapture && !move.isEnPassant)
        {
            continue;
        }

        UndoInfo undo;

        generator.makeMove(
            pos,
            move,
            undo
        );

        int score =
            quiescence(
                pos,
                alpha,
                beta
            );

        generator.undoMove(
            pos,
            move,
            undo
        );

        if(pos.sideToMove == 'w'){
            alpha = std::max(alpha, score);

            if(alpha >= beta)
                break;
        }
        else{
            beta = std::min(beta, score);

            if(beta <= alpha)
                break;
        }
    }

    return pos.sideToMove == 'w'
        ? alpha
        : beta;
}