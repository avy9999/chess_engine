#include "iostream"
#include "random"
#include "algorithm"
#include "../include/search.h"
#include "../include/evaluator.h"
#include "../include/movegenerator.h"
#include "../include/undoinfo.h"

long long Search::nodes = 0;


Move random_choice(const std::vector<Move>& moves)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::uniform_int_distribution<int> dist(0, moves.size() - 1);
    return moves[dist(rng)];
}

int Search::alphabeta(Position& pos, int depth, int alpha, int beta)
{
    Search::nodes++;

    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);

    if (moves.empty())
    {
        if (generator.isKingInCheck(pos, pos.sideToMove))
        {
            return (pos.sideToMove == 'w')
                ? -100000 - depth
                : 100000 + depth;
        }
        return 0;
    }

    if (depth == 0)
        return quiescence(pos, alpha, beta);

    std::sort(
        moves.begin(),
        moves.end(),
        [&](const Move& a, const Move& b)
        {
            return scoreMove(pos, a) > scoreMove(pos, b);
        }
    );

    int best;

    if (pos.sideToMove == 'w')
    {
        best = -1000000;

        for (const auto& move : moves)
        {
            UndoInfo undo;
            generator.makeMove(pos, move, undo);

            int score = alphabeta(pos, depth - 1, alpha, beta);

            generator.undoMove(pos, move, undo);

            best = std::max(best, score);
            alpha = std::max(alpha, best);

            if (beta <= alpha)
                break;
        }
    }
    else
    {
        best = 1000000;

        for (const auto& move : moves)
        {
            UndoInfo undo;
            generator.makeMove(pos, move, undo);

            int score = alphabeta(pos, depth - 1, alpha, beta);

            generator.undoMove(pos, move, undo);

            best = std::min(best, score);
            beta = std::min(beta, best);

            if (beta <= alpha)
                break;
        }
    }

    return best;
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
    Search::nodes = 0;

    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);

    static std::mt19937 rng(std::random_device{}());


    std::sort(
        moves.begin(),
        moves.end(),
        [&](const Move& a, const Move& b)
        {
            return scoreMove(pos, a) >
                   scoreMove(pos, b);
        }
    );

    std::shuffle(moves.begin() + 0, moves.begin() + std::min(5, (int)moves.size()), rng);

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

    int bestScore =
        (pos.sideToMove == 'w')
        ? std::numeric_limits<int>::min()
        : std::numeric_limits<int>::max();

    std::vector<Move> bestMoves;

    // small opening noise
    std::uniform_int_distribution<int> noise(-8, 8);

    // estimate game phase
    int pieces = 0;
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (pos.board[r][c] != '.')
                pieces++;
        }
    }

    bool openingPhase = (pieces >= 28);

    if (pos.sideToMove == 'w')
    {
        for (const auto& move : moves)
        {
            Position copy = pos;
            MoveGenerator::positionCopies++;

            generator.makeMove(copy, move);

            int score = alphabeta(
                copy,
                depth - 1,
                -1000000,
                1000000
            );

            if (openingPhase)
            {
                score += noise(rng);
            }

            if (score > bestScore)
            {
                bestScore = score;
                bestMoves.clear();
                bestMoves.push_back(move);
            }
            else if (score == bestScore)
            {
                bestMoves.push_back(move);
            }
        }
    }
    else
    {
        for (const auto& move : moves)
        {
            Position copy = pos;
            MoveGenerator::positionCopies++;

            generator.makeMove(copy, move);

            int score = alphabeta(
                copy,
                depth - 1,
                -1000000,
                1000000
            );

            if (openingPhase)
            {
                score += noise(rng);
            }

            if (score < bestScore)
            {
                bestScore = score;
                bestMoves.clear();
                bestMoves.push_back(move);
            }
            else if (score == bestScore)
            {
                bestMoves.push_back(move);
            }
        }
    }

    if (!bestMoves.empty())
        bestMove = random_choice(bestMoves);
    else
        bestMove = moves[0];

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