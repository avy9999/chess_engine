#include "../include/uci.h"
#include "../include/position.h"
#include "../include/search.h"
#include "../include/movegenerator.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

namespace {
    const std::string STARTPOS_FEN =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::string moveToUCI(const Move& move){
        char fromFile = 'a' + move.fromCol;
        char toFile   = 'a' + move.toCol;

        char fromRank = '8' - move.fromRow;
        char toRank   = '8' - move.toRow;

        std::string uci{
            fromFile,
            fromRank,
            toFile,
            toRank
        };

        if(move.promotionPiece != '\0'){
            uci += std::tolower(move.promotionPiece);
        }

        return uci;
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

            bool found = false;

            for(const Move& move : moves){
                if(moveToUCI(move) == moveStr){
                    generator.makeMove(pos, move);
                    found = true;
                    break;
                }
            }

            if(!found){
                std::ofstream log("uci.log", std::ios::app);

                log << "FAILED TO APPLY: "
                    << moveStr
                    << '\n';

                log << "Legal moves were:\n";

                for(const Move& move : moves){
                    log << moveToUCI(move) << ' ';
                }

                log << "\n";
            }
        }
    }

    void validateAndLogMove(
        const Move& bestMove,
        const Position& pos,
        MoveGenerator& generator
    ){
        auto legalMoves =
            generator.generateLegalMoves(pos);

        bool legal = false;

        for(const Move& m : legalMoves){
            if(moveToUCI(m) == moveToUCI(bestMove)){
                legal = true;
                break;
            }
        }

        std::ofstream log("uci.log", std::ios::app);

        if(!legal){
            log << "ILLEGAL BESTMOVE "
                << moveToUCI(bestMove)
                << "\n";

            log << "Legal moves:\n";

            for(const Move& m : legalMoves){
                log << moveToUCI(m) << ' ';
            }

            log << "\n";
        }

        log << "SENDING "
            << moveToUCI(bestMove)
            << "\n";
    }
}

void UCI::loop(){
    Position currentPos;
    Search search;
    MoveGenerator generator;
    std::string command;

    while(std::getline(std::cin, command)){

        {
            std::ofstream log("uci.log", std::ios::app);
            log << command << '\n';
        }

        if (command == "uci"){
            std::cout << "id name Avy\n";
            std::cout << "id author Avy\n";
            std::cout << "uciok\n";
            std::cout << std::flush;
        }

        else if(command == "position startpos"){
            currentPos.loadFEN(STARTPOS_FEN);
        }

        else if(command.rfind("position startpos moves ", 0) == 0){

            currentPos.loadFEN(STARTPOS_FEN);

            std::string movesPart =
                command.substr(24);

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

            size_t movesPos =
                command.find(" moves ");

            if(movesPos != std::string::npos){

                std::string fen =
                    command.substr(
                        13,
                        movesPos - 13
                    );

                std::string movesPart =
                    command.substr(
                        movesPos + 7
                    );

                currentPos.loadFEN(fen);

                applyUCIMoves(
                    currentPos,
                    movesPart,
                    generator
                );
            }
            else{
                std::string fen =
                    command.substr(13);

                currentPos.loadFEN(fen);
            }
        }

        else if(command == "isready"){
            std::cout << "readyok\n";
            std::cout << std::flush;
        }

        else if(command.rfind("go depth ", 0) == 0){

            int depth =
                std::stoi(command.substr(9));

            Move bestMove =
                search.findBestMove(
                    currentPos,
                    depth
                );

            validateAndLogMove(
                bestMove,
                currentPos,
                generator
            );

            std::cout
                << "bestmove "
                << moveToUCI(bestMove)
                << "\n";

            std::cout << std::flush;
        }

        else if(command.rfind("go", 0) == 0){

            Move bestMove =
                search.findBestMove(
                    currentPos,
                    3
                );

            validateAndLogMove(
                bestMove,
                currentPos,
                generator
            );

            std::cout
                << "bestmove "
                << moveToUCI(bestMove)
                << "\n";

            std::cout << std::flush;
        }

        else if(command == "quit"){
            break;
        }
    }
}