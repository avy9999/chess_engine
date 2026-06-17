#pragma once

class Move{
    public:
        int fromRow;
        int fromCol;
        int toRow;
        int toCol;

        bool isEnPassant = false;
        char promotionPiece = '\0';

        Move();
        Move(int fr, int fc, int tr, int tc);
        bool operator==(const Move& other) const;
};