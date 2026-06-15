# Chess Engine

A chess engine built from scratch in C++.

## Features

### Completed

* FEN Parsing
* Board Representation
* Move Representation (`Move` class)

#### Move Generation

* Knight Move Generation
* King Move Generation
* Pawn Move Generation
* Bishop Move Generation
* Rook Move Generation
* Queen Move Generation
* All-Moves Generation
* Legal Move Generation

#### Move Execution

* Move Execution (`makeMove`)
* Castling Move Execution
* En Passant Move Execution
* Pawn Promotion Execution

#### Special Chess Rules

* Castling Move Generation

* Castling Rights Management

* Castling Validation

  * Cannot castle while in check
  * Cannot castle through check
  * Cannot castle into check
  * Requires correct castling rights
  * Requires unmoved rook
  * Requires empty squares between king and rook

* En Passant Move Generation

* En Passant State Tracking

* Pawn Promotion Move Generation

* Promotion Piece Selection (Queen, Rook, Bishop, Knight)

#### Position Analysis

* Square Attack Detection (`isSquareAttacked`)
* Check Detection (`isKingInCheck`)
* Checkmate Detection
* Stalemate Detection

#### Evaluation & Search

* Material Evaluation Function
* Minimax Search
* Alpha-Beta Pruning
* Basic Move Ordering (MVV-LVA)
* Best Move Search (`findBestMove`)
* Node Counting / Search Statistics

### In Progress

* Mate Distance Scoring

### Planned

* Piece-Square Tables
* Iterative Deepening
* Transposition Tables
* UCI Support

## Current Status

The engine currently supports all standard chess rules and legal move generation.

Capabilities include:

* Loading positions from FEN strings
* Generating legal moves for all pieces
* Executing legal moves on the board
* Detecting attacks, checks, checkmates, and stalemates
* Handling castling, en passant, and promotions
* Evaluating positions using material balance
* Searching positions using Minimax
* Optimizing search with Alpha-Beta Pruning
* Ordering moves using MVV-LVA
* Selecting the best move from a given position
* Tracking node counts for performance analysis

## Next Milestone

Implement:

* Mate Distance Scoring

Goals:

* Prefer faster checkmates
* Delay unavoidable losses
* Improve search quality in tactical positions

After this milestone, the engine will correctly distinguish between mate in 1, mate in 2, and longer mating sequences.