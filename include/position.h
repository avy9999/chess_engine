#pragma once

#include <string>

class Position{
    public:
        char board[8][8];

        int whiteKingRow;
        int whiteKingCol;

        int blackKingRow;
        int blackKingCol;
        char sideToMove;
        bool castlingRights[4];
        int enPassantRow;
        int enPassantCol;
        int halfMoveClock;
        int fullMoveNumber;
        
        Position();

        void initializeBoard();

        void printBoard();

        void loadFEN(const std::string& fen);
};