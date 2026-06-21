#include "../include/uci.h"
#include "../include/position.h"
#include "../include/search.h"
#include "../include/movegenerator.h"
#include "../include/perft.h"
#include "../include/openingbook.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <vector>

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

    void divide(Position& pos, int depth) {
        if (depth <= 0) {
            std::cout << "total: 1\n";
            return;
        }

        MoveGenerator generator;
        auto moves = generator.generateLegalMoves(pos);

        long long total = 0;

        for (const Move& move : moves) {
            UndoInfo undo;
            generator.makeMove(pos, move, undo);

            long long nodes = perft(pos, depth - 1);

            generator.undoMove(pos, move, undo);

            total += nodes;

            std::cout << moveToUCI(move) << ": " << nodes << "\n";
        }

        std::cout << "total: " << total << "\n";
    }

    void applyUCIMoves(
        Position& pos,
        const std::string& movesPart,
        MoveGenerator& generator,
        std::vector<std::string>* moveHistory
    ){
        std::stringstream ss(movesPart);

        std::string moveStr;

        while(ss >> moveStr){

            std::vector<Move> moves =
                generator.generateLegalMoves(pos);

            bool found = false;

            for(const Move& move : moves){
                if(moveToUCI(move) == moveStr){
                    // std::cout << "\nApplying: "
                    //         << moveToUCI(move)
                    //         << "\n";

                    // pos.printBoard();
                    // std::cout << "\n";
                    generator.makeMove(pos, move);

                    if(moveHistory != nullptr){
                        moveHistory->push_back(moveStr);
                    }

                    // std::cout << "After:\n";
                    // pos.printBoard();
                    // std::cout << "\n";
                    
                    // std::cout
                    //     << "White King: "
                    //     << pos.whiteKingRow
                    //     << ","
                    //     << pos.whiteKingCol
                    //     << "\n";

                    // std::cout
                    //     << "Black King: "
                    //     << pos.blackKingRow
                    //     << ","
                    //     << pos.blackKingCol
                    //     << "\n";

                    // std::cout
                    //     << "White in check = "
                    //     << generator.isKingInCheck(pos, 'w')
                    //     << "\n";

                    // std::cout
                    //     << "Black in check = "
                    //     << generator.isKingInCheck(pos, 'b')
                    //     << "\n";
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

    bool findLegalMoveFromUCI(
        Position& pos,
        MoveGenerator& generator,
        const std::string& moveStr,
        Move& result
    ){
        auto moves = generator.generateLegalMoves(pos);

        for(const Move& move : moves){
            if(moveToUCI(move) == moveStr){
                result = move;
                return true;
            }
        }

        return false;
    }

    void validateAndLogMove(
        const Move& bestMove,
        Position& pos,
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

        // if(!legal){
        //     std::cout
        //         << "\nILLEGAL BESTMOVE DETECTED: "
        //         << moveToUCI(bestMove)
        //         << "\n";

        //     std::cout << "Legal moves are:\n";

        //     for(const Move& m : legalMoves){
        //         std::cout << moveToUCI(m) << " ";
        //     }

        //     std::cout << "\n";
        // }

        log << "SENDING "
            << moveToUCI(bestMove)
            << "\n";
    }
}

void UCI::loop(){
    Position currentPos;
    Search search;
    MoveGenerator generator;
    std::vector<std::string> moveHistory;
    bool bookEligible = true;
    std::string command;

    while(std::getline(std::cin, command)){

        {
            std::ofstream log("uci.log", std::ios::app);
            log << command << '\n';
        }

        if(command == "uci"){
            std::cout << "id name Avy\n";
            std::cout << "id author Avy\n";
            std::cout << "uciok\n";
            std::cout << std::flush;
        }

        else if(command == "position startpos"){

            {
                std::ofstream log("uci.log", std::ios::app);
                log << "\n=== POSITION STARTPOS ===\n";
                log << command << "\n";
            }

            currentPos.loadFEN(STARTPOS_FEN);
            moveHistory.clear();
            bookEligible = true;
        }

        else if(command.rfind("position startpos moves ", 0) == 0){

            {
                std::ofstream log("uci.log", std::ios::app);
                log << "\n=== POSITION STARTPOS MOVES ===\n";
                log << command << "\n";
            }

            currentPos.loadFEN(STARTPOS_FEN);
            moveHistory.clear();
            bookEligible = true;

            std::string movesPart =
                command.substr(24);

            applyUCIMoves(
                currentPos,
                movesPart,
                generator,
                &moveHistory
            );
        }

        else if(command == "ucinewgame"){
            currentPos.loadFEN(STARTPOS_FEN);
            moveHistory.clear();
            bookEligible = true;
        }

        else if(command.rfind("position fen ", 0) == 0){

            {
                std::ofstream log("uci.log", std::ios::app);
                log << "\n=== POSITION FEN ===\n";
                log << command << "\n";
            }

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
                moveHistory.clear();
                bookEligible = fen == STARTPOS_FEN;

                applyUCIMoves(
                    currentPos,
                    movesPart,
                    generator,
                    bookEligible ? &moveHistory : nullptr
                );
            }
            else{
                std::string fen =
                    command.substr(13);

                currentPos.loadFEN(fen);
                moveHistory.clear();
                bookEligible = fen == STARTPOS_FEN;
            }
        }

        else if(command == "isready"){
            std::cout << "readyok\n";
            std::cout << std::flush;
        }

        else if(command.rfind("go depth ", 0) == 0){

            if(bookEligible){
                std::string bookMove =
                    OpeningBook::findMove(moveHistory);

                Move bestMove;

                if(!bookMove.empty() &&
                    findLegalMoveFromUCI(
                        currentPos,
                        generator,
                        bookMove,
                        bestMove
                    )
                ){
                    validateAndLogMove(
                        bestMove,
                        currentPos,
                        generator
                    );

                    std::cout
                        << "info string book move\n";

                    std::cout
                        << "bestmove "
                        << bookMove
                        << "\n";

                    std::cout << std::flush;
                    continue;
                }
            }

            // std::cout << "Before search:\n";
            // currentPos.printBoard();
            // std::cout << "\n";

            auto start =
                std::chrono::steady_clock::now();

            int depth =
                std::stoi(command.substr(9));

            Move bestMove =
                search.findBestMove(
                    currentPos,
                    depth
                );

            auto end =
                std::chrono::steady_clock::now();

            // std::cout << "After search:\n";
            // currentPos.printBoard();
            // std::cout << "\n";

            validateAndLogMove(
                bestMove,
                currentPos,
                generator
            );

            auto ms =
                std::chrono::duration_cast<
                    std::chrono::milliseconds
                >(end - start).count();

            std::cout
                << "Time: "
                << ms
                << " ms\n";

            std::cout
                << "NPS: "
                << (ms > 0
                    ? (Search::nodes * 1000LL / ms)
                    : 0)
                << "\n";

            std::cout
                << "Legal Move Calls "
                << MoveGenerator::legalMoveCalls
                << "\n";

            std::cout
                << "Legal King Check Calls "
                << MoveGenerator::kingCheckCalls
                << "\n";

            std::cout
                << "Position Copied "
                << MoveGenerator::positionCopies
                << "\n";

            std::cout
                << "All Move Calls "
                << MoveGenerator::generateAllMovesCalls
                << "\n";

            auto legalMoves =
                generator.generateLegalMoves(currentPos);

            bool found = false;

            for(const auto& m : legalMoves){
                if(moveToUCI(m) == moveToUCI(bestMove)){
                    found = true;
                    break;
                }
            }

            if(!found){
                std::cout
                    << "\nENGINE IS ABOUT TO SEND AN ILLEGAL MOVE: "
                    << moveToUCI(bestMove)
                    << "\n";
            }
            std::cout
                << "bestmove "
                << moveToUCI(bestMove)
                << "\n";

            std::cout << std::flush;
        }

        else if(command.rfind("go", 0) == 0){

            if(bookEligible){
                std::string bookMove =
                    OpeningBook::findMove(moveHistory);

                Move bestMove;

                if(!bookMove.empty() &&
                    findLegalMoveFromUCI(
                        currentPos,
                        generator,
                        bookMove,
                        bestMove
                    )
                ){
                    validateAndLogMove(
                        bestMove,
                        currentPos,
                        generator
                    );

                    std::cout
                        << "info string book move\n";

                    std::cout
                        << "bestmove "
                        << bookMove
                        << "\n";

                    std::cout << std::flush;
                    continue;
                }
            }

            // std::cout << "Before search:\n";
            // currentPos.printBoard();
            // std::cout << "\n";

            Move bestMove =
                search.findBestMove(
                    currentPos,
                    3
                );

            // std::cout << "After search:\n";
            // currentPos.printBoard();
            // std::cout << "\n";

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

        else if(command.rfind("perft ", 0) == 0){
            int depth = std::stoi(command.substr(6));

            long long nodes = perft(currentPos, depth);

            std::cout << "perft " << depth << " = " <<  nodes << "\n";
            std::cout << std::flush;
        }

        else if(command.rfind("divide ", 0) == 0){
            int depth = std::stoi(command.substr(7));

            divide(currentPos, depth);
            std::cout << std::flush;
        }

        else if(command == "perfttest"){
            runPerftTests(std::cout);
            std::cout << std::flush;
        }

        else if(command == "quit"){
            break;
        }
    }
}
