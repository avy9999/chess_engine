#pragma once

bool isWhitePiece(char piece);
bool isBlackPiece(char piece);

bool isFriendlyPiece(char piece, char sideToMove);
bool isEnemyPiece(char piece, char sideToMove);

bool isEmptySquare(char piece);