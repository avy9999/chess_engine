#include "../include/evaluator.h"
#include "../include/utils.h"
#include "../include/pst.h"

int Evaluator::evaluate(const Position& pos) {
    int score = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {

            char piece = pos.board[i][j];

            switch (tolower(piece)) {
                case 'p':
                    if (isWhitePiece(piece)){
                        score += 100 + PST::pawn[i][j];
                        if (isPassedPawn(pos, i, j)){
                            score += passedPawnBonus[i];
                        }
                    } else {
                        score -= 100 + PST::pawn[7-i][j];
                        if (isPassedPawn(pos, i, j)){
                            score -= passedPawnBonus[7 - i];
                        }
                    }
                    break;

                case 'n':
                    score += isWhitePiece(piece) ? 320 + PST::knight[i][j] : -320 - PST::knight[7-i][j];
                    break;

                case 'b':
                    score += isWhitePiece(piece) ? 330 + PST::bishop[i][j] : -330 - PST::bishop[7-i][j];
                    break;

                case 'r':
                    score += isWhitePiece(piece) ? 500 : -500;
                    break;

                case 'q':
                    score += isWhitePiece(piece) ? 900 : -900;
                    break;
                case 'k':
                    score += isWhitePiece(piece)
                        ? PST::king[i][j]
                        : -PST::king[7-i][j];
                    break;
            }
        }
    }

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