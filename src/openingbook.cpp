#include "../include/openingbook.h"

#include <fstream>
#include <random>
#include <sstream>

namespace {
    bool openBookFile(std::ifstream& file) {
        const std::vector<std::string> paths = {
            "../data/opening_book.txt"
        };

        for (const auto& path : paths) {
            file.open(path);

            if (file.is_open()) {
                return true;
            }

            file.clear();
        }

        return false;
    }

    std::vector<std::string> parseLine(const std::string& line) {
        std::stringstream ss(line);
        std::vector<std::string> moves;
        std::string token;

        while (ss >> token) {
            if (!token.empty() && token[0] == '#') {
                break;
            }

            moves.push_back(token);
        }

        return moves;
    }

    bool matchesHistory(
        const std::vector<std::string>& bookLine,
        const std::vector<std::string>& moveHistory
    ) {
        if (bookLine.size() <= moveHistory.size()) {
            return false;
        }

        for (size_t i = 0; i < moveHistory.size(); i++) {
            if (bookLine[i] != moveHistory[i]) {
                return false;
            }
        }

        return true;
    }
}

std::string OpeningBook::findMove(
    const std::vector<std::string>& moveHistory
) {
    std::ifstream file;

    if (!openBookFile(file)) {
        return "";
    }

    std::vector<std::string> candidates;
    std::string line;

    while (std::getline(file, line)) {
        auto bookLine = parseLine(line);

        if (matchesHistory(bookLine, moveHistory)) {
            candidates.push_back(bookLine[moveHistory.size()]);
        }
    }

    if (candidates.empty()) {
        return "";
    }

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(
        0,
        candidates.size() - 1
    );

    return candidates[dist(rng)];
}
