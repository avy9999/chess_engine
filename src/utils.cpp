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

bool isInsideBoard(int row, int col){
    return row >= 0 && row < 8 &&
           col >= 0 && col < 8;
}

bool isPieceType(char piece, char pieceType){
    return std::tolower(piece) == pieceType;
}