#include "../include/perft.h"
#include "../include/movegenerator.h"

#include <string>
#include <vector>

long long perft(Position& pos, int depth) {
    if (depth <= 0) return 1;

    MoveGenerator generator;
    auto moves = generator.generateLegalMoves(pos);

    long long nodes = 0;

    for (const Move& move : moves) {
        UndoInfo undo;
        generator.makeMove(pos, move, undo);

        nodes += perft(pos, depth - 1);

        generator.undoMove(pos, move, undo);
    }

    return nodes;
}

namespace {
    struct PerftExpected {
        int depth;
        long long nodes;
    };

    struct PerftCase {
        std::string name;
        std::string fen;
        std::vector<PerftExpected> expected;
    };

    const std::vector<PerftCase> perftCases = {
        {
            "startpos",
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
            {
                {1, 20},
                {2, 400},
                {3, 8902},
                {4, 197281},
                {5, 4865609}
            }
        },
        {
            "kiwipete",
            "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",
            {
                {1, 48},
                {2, 2039},
                {3, 97862},
                {4, 4085603}
            }
        },
        {
            "white en passant",
            "7k/8/8/3pP3/8/8/8/K7 w - d6 0 1",
            {
                {1, 5}
            }
        },
        {
            "black en passant",
            "7k/8/8/8/3Pp3/8/8/K7 b - d3 0 1",
            {
                {1, 5}
            }
        },
        {
            "white promotion",
            "7k/P7/8/8/8/8/8/K7 w - - 0 1",
            {
                {1, 7}
            }
        },
        {
            "black promotion",
            "7k/8/8/8/8/8/p7/7K b - - 0 1",
            {
                {1, 7}
            }
        },
        {
            "white castling",
            "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1",
            {
                {1, 26}
            }
        },
        {
            "black castling",
            "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1",
            {
                {1, 26}
            }
        },
        {
            "castling blocked by attack",
            "r3k2r/8/8/8/8/8/5r2/R3K2R w KQkq - 0 1",
            {
                {1, 22}
            }
        }
    };
}

bool runPerftTests(std::ostream& out) {
    int passed = 0;
    int failed = 0;

    for (const auto& testCase : perftCases) {
        for (const auto& expected : testCase.expected) {
            Position pos;
            pos.loadFEN(testCase.fen);

            long long nodes = perft(pos, expected.depth);

            if (nodes == expected.nodes) {
                out << "PASS "
                    << testCase.name
                    << " depth "
                    << expected.depth
                    << " = "
                    << nodes
                    << "\n";
                passed++;
            } else {
                out << "FAIL "
                    << testCase.name
                    << " depth "
                    << expected.depth
                    << " expected "
                    << expected.nodes
                    << " got "
                    << nodes
                    << "\n";
                failed++;
            }
        }
    }

    out << "perft tests: "
        << passed
        << " passed, "
        << failed
        << " failed\n";

    return failed == 0;
}
