#pragma once
#include <vector>
#include "move.h"
#include "position.h"
#include "undoinfo.h"

class MoveGenerator {
    public:
        static long long legalMoveCalls;
        static long long kingCheckCalls;
        static long long positionCopies;
        static long long generateAllMovesCalls;
        std::vector<Move> generateKnightMoves(const Position& pos);
        std::vector<Move> generateKingMoves(const Position& pos);
        std::vector<Move> generatePawnMoves(const Position& pos);
        std::vector<Move> generateBishopMoves(const Position& pos);
        std::vector<Move> generateRookMoves(const Position& pos);
        std::vector<Move> generateQueenMoves(const Position& pos);
        std::vector<Move> generateAllMoves(const Position& pos);
        std::vector<Move> generateLegalMoves(Position& pos);
        std::vector<Move> generateSlidingMoves(const Position& pos, char pieceType, const std::vector<std::pair<int,int>>& directions);
        void makeMove(Position& pos, const Move& move);
        void makeMove(Position& pos, const Move& move, UndoInfo& undo);
        void undoMove(Position& pos, const Move& move, const UndoInfo& undo);
        void addPromotionMoves(std::vector<Move>& moves, int fromRow, int fromCol, int toRow, int toCol);
        bool isSquareAttacked(const Position& pos, int row, int col, char attackingSide);
        bool checkPawnAttack(const Position& pos, int row, int col, char attackingSide);
        bool checkKnightAttack(const Position& pos, int row, int col, char attackingSide);
        bool checkKingAttack(const Position& pos, int row, int col, char attackingSide);
        bool checkDiagonalAttack(const Position& pos, int row, int col, char attackingSide);
        bool checkStraightAttack(const Position& pos, int row, int col, char attackingSide);
        bool isKingInCheck(const Position& pos, char side);
        bool isCheckmate(Position& pos);
        bool isStalemate(Position& pos);
};