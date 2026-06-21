#pragma once

#include <ostream>
#include "position.h"

long long perft(Position& pos, int depth);
bool runPerftTests(std::ostream& out);
