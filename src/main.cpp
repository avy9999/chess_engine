#include <iostream>
#include "../include/position.h"
#include "../include/movegenerator.h"

int main() {
    MoveGenerator generator;

    Position pos;
    pos.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    pos.printBoard();

    Move move(6, 4, 4, 4); // e2 -> e4
    generator.makeMove(pos, move);

    std::cout << "\nAfter e2-e4:\n";
    pos.printBoard();
    std::cout << "\nSide: " << pos.sideToMove << "\n";

    Move move2(1, 4, 3, 4); // e7 -> e5
    generator.makeMove(pos, move2);

    std::cout << "\nAfter e7-e5:\n";
    pos.printBoard();
    
    auto knightMoves = generator.generateKnightMoves(pos);
    std::cout << "\nKnight Moves:\n";
    std::cout << "Total moves: " << knightMoves.size() << "\n";
    for (const auto& m : knightMoves){
        std::cout << "(" << m.fromRow << "," << m.fromCol << ") -> (" << m.toRow << "," << m.toCol << ")\n";
    }

    auto kingMoves = generator.generateKingMoves(pos);
    std::cout << "\nKing Moves:\n";
    std::cout << "Total moves: " << kingMoves.size() << "\n";
    for (const auto& m : kingMoves){
        std::cout << "(" << m.fromRow << "," << m.fromCol << ") -> (" << m.toRow << "," << m.toCol << ")\n";
    }

    auto pawnMoves = generator.generatePawnMoves(pos);
    std::cout << "\nPawn Moves:\n";
    std::cout << "Total moves: " << pawnMoves.size() << "\n";
    for (const auto& m : pawnMoves){
        std::cout << "(" << m.fromRow << "," << m.fromCol << ") -> (" << m.toRow << "," << m.toCol << ")\n";
    }

    auto bishopMoves = generator.generateBishopMoves(pos);
    std::cout << "\nBishop Moves:\n";
    std::cout << "Total moves: " << bishopMoves.size() << "\n";
    for (const auto& m : bishopMoves){
        std::cout << "(" << m.fromRow << "," << m.fromCol << ") -> (" << m.toRow << "," << m.toCol << ")\n";
    }

    auto rookMoves = generator.generateRookMoves(pos);
    std::cout << "\nRook Moves:\n";
    std::cout << "Total moves: " << rookMoves.size() << "\n";
    for (const auto& m : rookMoves){
        std::cout << "(" << m.fromRow << "," << m.fromCol << ") -> (" << m.toRow << "," << m.toCol << ")\n";
    }

    auto queenMoves = generator.generateQueenMoves(pos);
    std::cout << "\nQueen Moves:\n";
    std::cout << "Total moves: " << queenMoves.size() << "\n";
    for (const auto& m : queenMoves){
        std::cout << "(" << m.fromRow << "," << m.fromCol << ") -> (" << m.toRow << "," << m.toCol << ")\n";
    }

    auto moves = generator.generateAllMoves(pos);
    std::cout << moves.size() << "\n";
}