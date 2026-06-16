#include "../include/evaluator.h"
#include "../include/utils.h"
#include "../include/pst.h"

int Evaluator::evaluate(const Position& pos) {
    int score = 0;

    // counts number of bishops
    int whiteBishops = 0;
    int blackBishops = 0;

    // counts pawn per file
    int whitePawnFiles[8] = {};
    int blackPawnFiles[8] = {};
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {

            char piece = pos.board[i][j];

            switch (tolower(piece)) {
                case 'p':
                    if (isWhitePiece(piece)){
                        whitePawnFiles[j]++;
                        score += 100 + PST::pawn[i][j];
                        if (isPassedPawn(pos, i, j)){
                            score += passedPawnBonus[i];
                        }
                    } else {
                        blackPawnFiles[j]++;
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
                    if (isWhitePiece(piece)){
                        whiteBishops++;
                    } else{
                        blackBishops++;
                    }
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

    for(int file = 0; file < 8; file++){
        if(whitePawnFiles[file] > 1){
            score -= 15 * (whitePawnFiles[file] - 1);
        }

        if(blackPawnFiles[file] > 1){
            score += 15 * (blackPawnFiles[file] - 1);
        }
    }
    
    for (int file = 0; file < 8; file++){
        if(whitePawnFiles[file] > 0){
            bool isolated = false;
            if (file == 0){
                isolated = (whitePawnFiles[1] == 0);
            } else if (file == 7){
                isolated = (whitePawnFiles[6] == 0);
            } else{
                isolated = whitePawnFiles[file - 1] == 0 && whitePawnFiles[file + 1] == 0;
            }
            if (isolated){
                score -= 10;
            }
        }

        if(blackPawnFiles[file] > 0){
            bool isolated = false;
            if (file == 0){
                isolated = (blackPawnFiles[1] == 0);
            } else if (file == 7){
                isolated = (blackPawnFiles[6] == 0);
            } else{
                isolated = blackPawnFiles[file - 1] == 0 && blackPawnFiles[file + 1] == 0;
            }
            if (isolated){
                score += 10;
            }
        }
    }

    if(whiteBishops >= 2)
        score += 30;

    if(blackBishops >= 2)
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