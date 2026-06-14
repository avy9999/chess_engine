# Chess Engine

A chess engine built from scratch in C++.

## Features

### Completed

* FEN Parsing

* Board Representation

* Move Representation (`Move` class)

* Knight Move Generation

* King Move Generation

* Pawn Move Generation

* Bishop Move Generation

* Rook Move Generation

* Queen Move Generation

* All-Moves Generation

* Move Execution (`makeMove`)

* Utility Functions for Piece Handling

* Square Attack Detection (`isSquareAttacked`)

* Check Detection (`isKingInCheck`)

* Legal Move Generation

* Castling Move Generation

* Castling Move Execution

* Castling Rights Management

* Castling Validation

  * Cannot castle while in check
  * Cannot castle through check
  * Cannot castle into check
  * Requires correct castling rights
  * Requires unmoved rook
  * Requires empty squares between king and rook

* En Passant Move Generation

* En Passant Move Execution

* En Passant State Tracking

* Checkmate Detection

* Stalemate Detection

* Pawn Promotion Move Generation

* Pawn Promotion Execution

* Promotion Piece Selection (Queen, Rook, Bishop, Knight)

* Minimax Search

### In Progress

* Alpha-Beta Pruning

### Planned

* Move Ordering
* Transposition Tables
* UCI Support

## Current Status

The engine currently supports all standard chess rules and legal move generation.

Capabilities include:

* Loading positions from FEN strings
* Generating legal moves for all pieces
* Executing moves on the board
* Detecting attacked squares
* Detecting checks
* Detecting checkmate positions
* Detecting stalemate positions
* Filtering illegal moves that leave the king in check
* Generating and executing castling moves
* Tracking and updating castling rights
* Generating and executing en passant captures
* Tracking and updating en passant target squares
* Generating and executing pawn promotions
* Supporting all standard chess move rules
* Evaluation Function

## Next Milestone

Implement:

* Alpha-Beta Pruning

After this milestone, the engine will be able to evaluate positions and determine which side has a material advantage, providing the foundation for Minimax search.