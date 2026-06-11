#include "../include/utils.h"
#include <cctype>

bool isWhitePiece(char piece){
    return isupper(piece);
};

bool isBlackPiece(char piece){
    return islower(piece);
};

bool isFriendlyPiece(char piece, char sideToMove){
    if (sideToMove == 'w'){
        return isWhitePiece(piece);
    }
    return isBlackPiece(piece);
};

bool isEnemyPiece(char piece, char sideToMove){
    if (sideToMove == 'w'){
        return isBlackPiece(piece);
    }
    return isWhitePiece(piece);
};

bool isEmptySquare(char piece){
    return piece == '.';
};