#include <iostream>
#include "../include/position.h"
#include "../include/movegenerator.h"

int main() {
    Position pos;
    MoveGenerator generator;

    pos.loadFEN("8/8/8/8/4p3/8/8/8 b - - 0 1");

    std::cout << "d3 attacked by black: "
            << generator.isSquareAttacked(pos, 5, 3, 'b') << "\n";

    std::cout << "f3 attacked by black: "
            << generator.isSquareAttacked(pos, 5, 5, 'b') << "\n";

    std::cout << "e5 attacked by white: "
          << generator.isSquareAttacked(pos, 3, 4, 'w') << "\n";
    
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