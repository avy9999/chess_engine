#pragma once

class Move{
    public:
        int fromRow;
        int fromCol;
        int toRow;
        int toCol;

        bool isEnPassant = false;

        // \0 means not a promotion
        char promotionPiece = '\0';
        
        Move(int fr, int fc, int tr, int tc);
};