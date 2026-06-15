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
                    score += isWhitePiece(piece) ? 100 + PST::pawn[i][j] : -100 - PST::pawn[7-i][j];
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