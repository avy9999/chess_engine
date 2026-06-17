# Chess Engine (Avy)

A chess engine built from scratch in modern C++ featuring full legal move generation, positional evaluation, alpha-beta search, iterative deepening, and UCI support.

---

## Features

### Chess Rules

* Full legal move generation
* Check detection
* Checkmate detection
* Stalemate detection
* Castling
* En Passant
* Pawn Promotion
* FEN Parsing

### Move Generation

* Pawn moves
* Knight moves
* Bishop moves
* Rook moves
* Queen moves
* King moves
* Legal move filtering

### Evaluation

#### Material Evaluation

* Standard piece values

#### Piece-Square Tables

* Pawn PST
* Knight PST
* Bishop PST
* Rook PST
* Queen PST
* King PST

#### Positional Evaluation

* Passed Pawn Bonuses
* Bishop Pair Bonus
* Doubled Pawn Penalties
* Isolated Pawn Penalties

### Search

* Minimax Search
* Alpha-Beta Pruning
* Iterative Deepening
* MVV-LVA Move Ordering
* Principal Variation (PV) Move Ordering
* Mate Distance Scoring
* Search Statistics & Node Counting

### Engine Optimizations

* Make/Undo Move System
* Incremental King Tracking
* Reduced Position Copying
* Search Profiling Utilities

### UCI Support

Implemented commands:

* `uci`
* `isready`
* `ucinewgame`
* `quit`
* `position startpos`
* `position startpos moves`
* `position fen`
* `position fen moves`
* `go depth N`

Compatible with:

* BanksiaGUI
---

## Current Capabilities

The engine currently supports complete legal chess gameplay and search.

Capabilities include:

* Loading positions from FEN strings
* Generating legal moves for all pieces
* Executing and undoing moves efficiently
* Detecting checks, checkmates, and stalemates
* Handling castling, en passant, and promotions
* Evaluating positions using material and positional factors
* Searching positions using Alpha-Beta pruning
* Ordering moves using MVV-LVA and PV ordering
* Preferring faster checkmates and delaying losses
* Communicating through the Universal Chess Interface (UCI)

---

## Performance Highlights

Implemented optimizations include:

### Alpha-Beta Pruning

* Significant reduction in explored nodes compared to plain minimax

### Move Ordering

* MVV-LVA capture ordering
* Principal Variation ordering through iterative deepening

### Search Optimizations

* Make/Undo search instead of full position copying
* Incremental king position tracking
* Search profiling and benchmarking utilities

---

## Roadmap

### Search

* Quiescence Search Improvements
* Killer Move Heuristic
* History Heuristic
* Transposition Tables
* Principal Variation Search (PVS)
* Negamax Refactor

### Evaluation

* Mobility Evaluation
* Pawn Chains
* Open Files
* Semi-Open Files
* Connected Rooks
* Endgame Evaluation

### Engine Infrastructure

* Full UCI Time Management
* `go movetime`
* `go infinite`
* `stop`
* `setoption`
* Perft Testing Suite
* PGN Parsing
* FEN Export

### Long-Term Goals

* Zobrist Hashing
* Incremental Evaluation
* Bitboards
* Multi-Threaded Search