#include "../include/movegenerator.h"
#include "../include/evaluator.h"
#include "../include/utils.h"
#include "../include/pst.h"

int Evaluator::evaluate(const Position& pos)
{
    int score = 0;

    int whiteBishops = 0, blackBishops = 0;
    int whitePawnsFile[8] = {0};
    int blackPawnsFile[8] = {0};

    int whiteMaterial = 0;
    int blackMaterial = 0;

    int whiteKingSafety = 0;
    int blackKingSafety = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char p = pos.board[i][j];
            if (p == '.') continue;

            bool white = isWhitePiece(p);
            char pc = tolower(p);

            int pieceValue = 0;

            switch (pc)
            {
                case 'p': pieceValue = 100; break;
                case 'n': pieceValue = 320; break;
                case 'b': pieceValue = 330; break;
                case 'r': pieceValue = 500; break;
                case 'q': pieceValue = 900; break;
                case 'k': pieceValue = 20000; break;
            }

            if (white)
            {
                whiteMaterial += pieceValue;
                score += pieceValue;

                if (pc == 'p')
                {
                    whitePawnsFile[j]++;
                    score += PST::pawn[i][j];
                }
                if (pc == 'b') whiteBishops++;
            }
            else
            {
                blackMaterial += pieceValue;
                score -= pieceValue;

                if (pc == 'p')
                {
                    blackPawnsFile[j]++;
                    score -= PST::pawn[7 - i][j];
                }
                if (pc == 'b') blackBishops++;
            }

            // PST for non-pawns
            if (pc == 'n')
                score += white ? PST::knight[i][j] : -PST::knight[7 - i][j];

            if (pc == 'b')
                score += white ? PST::bishop[i][j] : -PST::bishop[7 - i][j];

            if (pc == 'r')
                score += white ? PST::rook[i][j] : -PST::rook[7 - i][j];

            if (pc == 'q')
                score += white ? PST::queen[i][j] : -PST::queen[7 - i][j];

            if (pc == 'k')
                score += white ? PST::king[i][j] : -PST::king[7 - i][j];
        }
    }

    // -----------------------------
    // Pawn structure (SAFE version)
    // -----------------------------
    for (int f = 0; f < 8; f++)
    {
        if (whitePawnsFile[f] > 1)
            score -= 12 * (whitePawnsFile[f] - 1);

        if (blackPawnsFile[f] > 1)
            score += 12 * (blackPawnsFile[f] - 1);

        bool whiteIsolated =
            (whitePawnsFile[f] > 0) &&
            ( (f == 0 || whitePawnsFile[f - 1] == 0) &&
              (f == 7 || whitePawnsFile[f + 1] == 0) );

        bool blackIsolated =
            (blackPawnsFile[f] > 0) &&
            ( (f == 0 || blackPawnsFile[f - 1] == 0) &&
              (f == 7 || blackPawnsFile[f + 1] == 0) );

        if (whiteIsolated) score -= 8;
        if (blackIsolated) score += 8;
    }

    // -----------------------------
    // Bishop pair bonus
    // -----------------------------
    if (whiteBishops >= 2) score += 25;
    if (blackBishops >= 2) score -= 25;

    // -----------------------------
    // SIMPLE development bonus
    // (ONLY early pieces)
    // -----------------------------
    int whiteDev =
        (pos.board[7][1] != 'N') +
        (pos.board[7][6] != 'N') +
        (pos.board[7][2] != 'B') +
        (pos.board[7][5] != 'B');

    int blackDev =
        (pos.board[0][1] != 'n') +
        (pos.board[0][6] != 'n') +
        (pos.board[0][2] != 'b') +
        (pos.board[0][5] != 'b');

    score += 10 * (whiteDev - blackDev);

    // -----------------------------
    // VERY LIGHT king safety (no mobility)
    // -----------------------------
    if (whiteMaterial < blackMaterial)
        score -= 10;

    if (blackMaterial < whiteMaterial)
        score += 10;

    
    // White castled kingside
    if (pos.board[7][6] == 'K' && pos.board[7][5] == 'R')
        score += 40;

    // White castled queenside
    if (pos.board[7][2] == 'K' && pos.board[7][3] == 'R')
        score += 30;

    // Black castled kingside
    if (pos.board[0][6] == 'k' && pos.board[0][5] == 'r')
        score -= 40;

    // Black castled queenside
    if (pos.board[0][2] == 'k' && pos.board[0][3] == 'r')
        score -= 30;
        return score;
    }


// function to return piece value
int Evaluator::getPieceValue(char piece){
    switch(std::tolower(piece)){
        case 'p': return 100;
        case 'n': return 320;
        case 'b': return 330;
        case 'r': return 500;
        case 'q': return 900;
        default:  return 0;
    }
}


// function to check if its passed pawn
bool Evaluator::isPassedPawn(const Position& pos, int row, int col){
    char piece = pos.board[row][col];

    if (piece == 'P'){
        for (int r = 0; r < row; ++r){
            for (int c = col - 1; c <= col + 1; ++c){
                if (c < 0 || c > 7){
                    continue;
                }
                if (pos.board[r][c] == 'p'){
                    return false;
                }
            }
        }
        return true;
    }

    if (piece == 'p'){
        for (int r = row + 1; r < 8; ++r){
            for (int c = col - 1; c <= col + 1; ++c){
                if (c < 0 || c > 7){
                    continue;
                }
                if (pos.board[r][c] == 'P'){
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}


// passed pawn scores according to rows
const int Evaluator::passedPawnBonus[8] = {
    0,
    80,
    50,
    30,
    20,
    10,
    0,
    0
};