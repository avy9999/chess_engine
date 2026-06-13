#pragma once
#include "move.h"
#include "movegenerator.h"

bool isWhitePiece(char piece);
bool isBlackPiece(char piece);

bool isFriendlyPiece(char piece, char sideToMove);
bool isEnemyPiece(char piece, char sideToMove);

bool isEmptySquare(char piece);

bool isInsideBoard(int row, int col);
bool isPieceType(char piece, char pieceType);

bool isCastleMove(const Move& move);