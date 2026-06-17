#include "../include/move.h"

Move::Move()
    : fromRow(-1),
      fromCol(-1),
      toRow(-1),
      toCol(-1)
{
}

Move::Move(int fr, int fc, int tr, int tc)
    : fromRow(fr),
      fromCol(fc),
      toRow(tr),
      toCol(tc)
{
}

bool Move::operator==(const Move& other) const {
    return fromRow == other.fromRow &&
           fromCol == other.fromCol &&
           toRow == other.toRow &&
           toCol == other.toCol &&
           promotionPiece == other.promotionPiece;
}