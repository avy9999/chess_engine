#pragma once

class Move{
    public:
        int fromRow;
        int fromCol;
        int toRow;
        int toCol;

        bool isEnPassant = false;

        Move(int fr, int fc, int tr, int tc);
};