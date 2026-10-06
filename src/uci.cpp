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
#include <cctype>

namespace
{
    const std::string STARTPOS_FEN =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    std::string moveToUCI(const Move &move)
    {
        char fromFile = 'a' + move.fromCol;
        char toFile = 'a' + move.toCol;

        char fromRank = '8' - move.fromRow;
        char toRank = '8' - move.toRow;

        std::string uci{
            fromFile,
            fromRank,
            toFile,
            toRank};

        if (move.promotionPiece != '\0')
        {
            uci += std::tolower(move.promotionPiece);
        }

        return uci;
    }

    void divide(Position &pos, int depth)
    {
        if (depth <= 0)
        {
            std::ofstream log("uci.log", std::ios::app);
            log << "total: 1\n";
            return;
        }

        MoveGenerator generator;
        auto moves = generator.generateLegalMoves(pos);

        long long total = 0;

        for (const Move &move : moves)
        {
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
        Position &pos,
        const std::string &movesPart,
        MoveGenerator &generator,
        std::vector<std::string> *moveHistory)
    {
        std::stringstream ss(movesPart);

        std::string moveStr;

        while (ss >> moveStr)
        {

            std::vector<Move> moves =
                generator.generateLegalMoves(pos);

            bool found = false;

            for (const Move &move : moves)
            {
                if (moveToUCI(move) == moveStr)
                {
                    {
                        std::ofstream log("uci.log", std::ios::app);

                        log << "Applying move: "
                            << moveStr
                            << "\n";
                    }
                    generator.makeMove(pos, move);

                    if (moveHistory != nullptr)
                    {
                        moveHistory->push_back(moveStr);
                    }
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                std::ofstream log("uci.log", std::ios::app);

                log << "FAILED TO APPLY: "
                    << moveStr
                    << '\n';

                log << "Legal moves were:\n";

                for (const Move &move : moves)
                {
                    log << moveToUCI(move) << ' ';
                }

                log << "\n";
            }
        }
    }

    bool findLegalMoveFromUCI(
        Position &pos,
        MoveGenerator &generator,
        const std::string &moveStr,
        Move &result)
    {
        auto moves = generator.generateLegalMoves(pos);

        for (const Move &move : moves)
        {
            if (moveToUCI(move) == moveStr)
            {
                result = move;
                return true;
            }
        }

        return false;
    }

    void validateAndLogMove(
        const Move &bestMove,
        Position &pos,
        MoveGenerator &generator)
    {
        auto legalMoves =
            generator.generateLegalMoves(pos);

        std::string bestMoveUCI = moveToUCI(bestMove);
        bool legal = false;

        for (const Move &m : legalMoves)
        {
            if (moveToUCI(m) == bestMoveUCI)
            {
                legal = true;
                break;
            }
        }

        std::ofstream log("uci.log", std::ios::app);

        log << "Bestmove candidate: " << bestMoveUCI << "\n";

        if (!legal)
        {
            log << "!!! ILLEGAL BESTMOVE !!!\n";
            log << "Illegal move: " << bestMoveUCI << "\n";
            log << "Legal moves (" << legalMoves.size() << "): ";

            for (const Move &m : legalMoves)
            {
                log << moveToUCI(m) << ' ';
            }

            log << "\n";
        }
        else
        {
            log << "Bestmove is legal: " << bestMoveUCI << "\n";
        }
    }

    void logBoard(const Position &pos)
    {
        std::ofstream log("uci.log", std::ios::app);

        log << "Board:\n";

        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                log << pos.board[r][c] << ' ';
            }

            log << '\n';
        }

        log << "SideToMove: "
            << pos.sideToMove
            << "\n";

        log << "Castling: "
            << pos.castlingRights[0]
            << pos.castlingRights[1]
            << pos.castlingRights[2]
            << pos.castlingRights[3]
            << "\n";

        log << "EP: "
            << pos.enPassantRow
            << ","
            << pos.enPassantCol
            << "\n\n";
    }

    void logLegalMoves(
        Position &pos,
        MoveGenerator &generator)
    {
        std::ofstream log("uci.log", std::ios::app);

        auto legalMoves =
            generator.generateLegalMoves(pos);

        log << "Legal moves ("
            << legalMoves.size()
            << "): ";

        for (const auto &m : legalMoves)
        {
            log << moveToUCI(m) << ' ';
        }

        log << "\n\n";
    }
}

void UCI::loop()
{
    Position currentPos;
    Search search;
    MoveGenerator generator;
    std::vector<std::string> moveHistory;
    bool bookEligible = true;
    std::string command;

    auto logUCI = [](const std::string &message)
    {
        std::ofstream log("uci.log", std::ios::app);
        log << message << '\n';
        log.flush();
    };

    auto sendUCI = [&](const std::string &message)
    {
        logUCI("--> " + message);
        std::cout << message << '\n';
        std::cout << std::flush;
    };

    logUCI("\n========== UCI SESSION START ==========");

    while (std::getline(std::cin, command))
    {

        // Log EVERYTHING Banksia sends to stdin.
        logUCI("<-- " + command);

        if (command == "uci")
        {
            sendUCI("id name Avy");
            sendUCI("id author Avy");
            sendUCI("uciok");
        }

        else if (command == "isready")
        {
            sendUCI("readyok");
        }

        else if (command == "ucinewgame")
        {
            currentPos.loadFEN(STARTPOS_FEN);
            moveHistory.clear();
            bookEligible = true;

            logUCI("=== NEW GAME ===");
            logBoard(currentPos);
        }

        else if (command == "position startpos")
        {

            currentPos.loadFEN(STARTPOS_FEN);
            moveHistory.clear();
            bookEligible = true;

            logUCI("=== POSITION STARTPOS ===");
            logBoard(currentPos);
        }

        else if (command.rfind("position startpos moves ", 0) == 0)
        {

            currentPos.loadFEN(STARTPOS_FEN);
            moveHistory.clear();
            bookEligible = true;

            std::string movesPart =
                command.substr(24);

            logUCI("=== POSITION STARTPOS MOVES ===");

            applyUCIMoves(
                currentPos,
                movesPart,
                generator,
                &moveHistory);

            logBoard(currentPos);
        }

        else if (command.rfind("position fen ", 0) == 0)
        {

            size_t movesPos =
                command.find(" moves ");

            if (movesPos != std::string::npos)
            {

                std::string fen =
                    command.substr(
                        13,
                        movesPos - 13);

                std::string movesPart =
                    command.substr(
                        movesPos + 7);

                currentPos.loadFEN(fen);
                moveHistory.clear();
                bookEligible = fen == STARTPOS_FEN;

                logUCI("=== POSITION FEN + MOVES ===");
                logUCI("FEN: " + fen);

                applyUCIMoves(
                    currentPos,
                    movesPart,
                    generator,
                    bookEligible ? &moveHistory : nullptr);

                logBoard(currentPos);
            }
            else
            {
                std::string fen =
                    command.substr(13);

                currentPos.loadFEN(fen);
                moveHistory.clear();
                bookEligible = fen == STARTPOS_FEN;

                logUCI("=== POSITION FEN ===");
                logUCI("FEN: " + fen);
                logBoard(currentPos);
            }
        }

        else if (command.rfind("go depth ", 0) == 0)
        {

            int depth =
                std::stoi(command.substr(9));

            logUCI("========== SEARCH ==========");
            logUCI("Depth: " + std::to_string(depth));

            logBoard(currentPos);
            logLegalMoves(currentPos, generator);

            if (bookEligible)
            {
                std::string bookMove =
                    OpeningBook::findMove(moveHistory);

                Move bestMove;

                if (!bookMove.empty() &&
                    findLegalMoveFromUCI(
                        currentPos,
                        generator,
                        bookMove,
                        bestMove))
                {
                    validateAndLogMove(
                        bestMove,
                        currentPos,
                        generator);

                    logUCI("Book move: " + bookMove);

                    sendUCI("info string book move");
                    sendUCI("bestmove " + bookMove);

                    logUCI("============================");
                    continue;
                }
            }

            auto start =
                std::chrono::steady_clock::now();

            Move bestMove =
                search.findBestMove(
                    currentPos,
                    depth);

            auto end =
                std::chrono::steady_clock::now();

            auto ms =
                std::chrono::duration_cast<
                    std::chrono::milliseconds>(end - start)
                    .count();

            validateAndLogMove(
                bestMove,
                currentPos,
                generator);

            {
                std::ofstream log("uci.log", std::ios::app);

                log << "Engine move: "
                    << moveToUCI(bestMove)
                    << "\n";

                log << "Time: "
                    << ms
                    << " ms\n";

                log << "NPS: "
                    << (ms > 0
                            ? (Search::nodes * 1000LL / ms)
                            : 0)
                    << "\n";

                log << "Nodes: "
                    << Search::nodes
                    << "\n";

                log << "LegalMoveCalls: "
                    << MoveGenerator::legalMoveCalls
                    << "\n";

                log << "KingCheckCalls: "
                    << MoveGenerator::kingCheckCalls
                    << "\n";

                log << "PositionCopies: "
                    << MoveGenerator::positionCopies
                    << "\n";

                log << "AllMoveCalls: "
                    << MoveGenerator::generateAllMovesCalls
                    << "\n";
            }

            // IMPORTANT:
            // Only valid UCI protocol output goes to stdout.
            // All diagnostics above go exclusively to uci.log.
            sendUCI(
                "bestmove " +
                moveToUCI(bestMove));

            logUCI("============================");
        }

        else if (command.rfind("go", 0) == 0)
        {

            logUCI("========== SEARCH ==========");
            logUCI("Default depth: 3");

            logBoard(currentPos);
            logLegalMoves(currentPos, generator);

            if (bookEligible)
            {
                std::string bookMove =
                    OpeningBook::findMove(moveHistory);

                Move bestMove;

                if (!bookMove.empty() &&
                    findLegalMoveFromUCI(
                        currentPos,
                        generator,
                        bookMove,
                        bestMove))
                {
                    validateAndLogMove(
                        bestMove,
                        currentPos,
                        generator);

                    logUCI("Book move: " + bookMove);

                    sendUCI("info string book move");
                    sendUCI("bestmove " + bookMove);

                    logUCI("============================");
                    continue;
                }
            }

            auto start =
                std::chrono::steady_clock::now();

            Move bestMove =
                search.findBestMove(
                    currentPos,
                    3);

            auto end =
                std::chrono::steady_clock::now();

            auto ms =
                std::chrono::duration_cast<
                    std::chrono::milliseconds>(end - start)
                    .count();

            validateAndLogMove(
                bestMove,
                currentPos,
                generator);

            {
                std::ofstream log("uci.log", std::ios::app);

                log << "Engine move: "
                    << moveToUCI(bestMove)
                    << "\n";

                log << "Time: "
                    << ms
                    << " ms\n";

                log << "NPS: "
                    << (ms > 0
                            ? (Search::nodes * 1000LL / ms)
                            : 0)
                    << "\n";

                log << "Nodes: "
                    << Search::nodes
                    << "\n";

                log << "LegalMoveCalls: "
                    << MoveGenerator::legalMoveCalls
                    << "\n";

                log << "KingCheckCalls: "
                    << MoveGenerator::kingCheckCalls
                    << "\n";

                log << "PositionCopies: "
                    << MoveGenerator::positionCopies
                    << "\n";

                log << "AllMoveCalls: "
                    << MoveGenerator::generateAllMovesCalls
                    << "\n";
            }

            sendUCI(
                "bestmove " +
                moveToUCI(bestMove));

            logUCI("============================");
        }

        else if (command.rfind("perft ", 0) == 0)
        {

            int depth =
                std::stoi(command.substr(6));

            long long nodes =
                perft(currentPos, depth);

            logUCI(
                "PERFT depth " +
                std::to_string(depth) +
                " = " +
                std::to_string(nodes));
        }

        else if (command.rfind("divide ", 0) == 0)
        {

            int depth =
                std::stoi(command.substr(7));

            logUCI(
                "DIVIDE depth " +
                std::to_string(depth));

            // Keep divide output out of stdout so it cannot
            // interfere with Banksia's UCI parser.
            if (depth <= 0)
            {
                logUCI("total: 1");
            }
            else
            {
                auto moves =
                    generator.generateLegalMoves(currentPos);

                long long total = 0;

                for (const Move &move : moves)
                {
                    UndoInfo undo;
                    generator.makeMove(
                        currentPos,
                        move,
                        undo);

                    long long nodes =
                        perft(
                            currentPos,
                            depth - 1);

                    generator.undoMove(
                        currentPos,
                        move,
                        undo);

                    total += nodes;

                    logUCI(
                        moveToUCI(move) +
                        ": " +
                        std::to_string(nodes));
                }

                logUCI(
                    "total: " +
                    std::to_string(total));
            }
        }

        else if (command == "perfttest")
        {
            logUCI("=== PERFT TEST ===");

            // runPerftTests() writes to a stream, so capture it
            // into a string stream instead of stdout.
            std::ostringstream output;
            runPerftTests(output);
            logUCI(output.str());
        }

        else if (command == "quit")
        {
            logUCI("<-- quit");
            logUCI("========== UCI SESSION END ==========");
            break;
        }

        else if (command.empty())
        {
            // Ignore empty lines.
            logUCI("(empty command)");
        }

        else
        {
            // Log unknown commands but DO NOT print anything to stdout.
            logUCI("UNKNOWN COMMAND: " + command);
        }
    }
}