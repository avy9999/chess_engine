#pragma once

struct UndoInfo
{
    char capturedPiece;

    bool castlingRights[4];

    int enPassantRow;
    int enPassantCol;

    int halfMoveClock;
    int fullMoveNumber;

    int whiteKingRow;
    int whiteKingCol;

    int blackKingRow;
    int blackKingCol;

    char movedPiece;

    bool wasCastle;
    bool wasEnPassant;
    bool wasPromotion;
};