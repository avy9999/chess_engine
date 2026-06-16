#include "../include/uci.h"
#include "../include/position.h"
#include "../include/search.h"
#include "../include/movegenerator.h"
#include <iostream>
#include <string>
#include <sstream>

namespace {
    const std::string STARTPOS_FEN =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::string moveToUCI(const Move& move){
        char fromFile = 'a' + move.fromCol;
        char toFile   = 'a' + move.toCol;

        char fromRank = '8' - move.fromRow;
        char toRank   = '8' - move.toRow;

        return std::string{
            fromFile,
            fromRank,
            toFile,
            toRank
        };
    }

    void applyUCIMoves(
        Position& pos,
        const std::string& movesPart,
        MoveGenerator& generator
    ){
        std::stringstream ss(movesPart);

        std::string moveStr;

        while(ss >> moveStr){
            std::vector<Move> moves =
                generator.generateLegalMoves(pos);

            for(const Move& move : moves){
                if(moveToUCI(move) == moveStr){
                    generator.makeMove(pos, move);
                    break;
                }
            }
        }
    }
}

void UCI::loop(){
    Position currentPos;
    Search search;
    MoveGenerator generator;
    std::string command;

    while(std::getline(std::cin, command)){

        if (command == "uci"){
            std::cout << "id name Avy\n";
            std::cout << "id author Avy\n";
            std::cout << "uciok\n";
            std::cout << std::flush;
        }

        else if(command == "position startpos"){
            currentPos.loadFEN(STARTPOS_FEN);
        }

        else if (command.rfind("go depth ", 0) == 0){
            int depth = std::stoi(command.substr(9));

            Move bestMove = search.findBestMove(currentPos, depth);

            std::cout << "bestmove " << moveToUCI(bestMove) << "\n";

            std::cout << std::flush;
        }

        else if(command.rfind("position startpos moves ", 0) == 0){

            currentPos.loadFEN(STARTPOS_FEN);

            std::string movesPart = command.substr(24);

            applyUCIMoves(
                currentPos,
                movesPart,
                generator
            );
        }

        else if(command == "ucinewgame"){
            currentPos.loadFEN(STARTPOS_FEN);
        }

        else if(command.rfind("position fen ", 0) == 0){
            size_t movesPos = command.find(" moves ");

            if (movesPos != std::string::npos){
                std::string fen =
                    command.substr(13, movesPos - 13);

                std::string movesPart =
                    command.substr(movesPos + 7);

                currentPos.loadFEN(fen);

                applyUCIMoves(
                    currentPos,
                    movesPart,
                    generator
                );
            }
            else{
                std::string fen = command.substr(13);
                currentPos.loadFEN(fen);
            }
        }

        else if (command == "isready"){
            std::cout << "readyok\n";
            std::cout << std::flush;
        }
        
        else if (command == "quit"){
            break;
        }
    }
}