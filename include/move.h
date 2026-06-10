#pragma once

class Move{
    public:
        int fromRow;
        int fromCol;
        int toRow;
        int toCol;

        Move(int fr, int fc, int tr, int tc);
};