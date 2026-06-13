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

### In Progress

* Checkmate Detection
* Stalemate Detection

### Planned

* En Passant
* Pawn Promotion
* Draw Detection

  * Fifty-Move Rule
  * Threefold Repetition
  * Insufficient Material
* Evaluation Function
* Minimax Search
* Alpha-Beta Pruning
* Move Ordering
* UCI Support
* Web Interface

## Current Status

The engine can currently:

* Load positions from FEN strings
* Generate legal moves for all pieces
* Execute moves on the board
* Detect attacked squares
* Detect checks
* Filter illegal moves that leave the king in check
* Generate and execute castling moves
* Track and update castling rights
* Validate castling legality according to chess rules

## Next Milestone

Implement:

* Checkmate Detection
* Stalemate Detection

using:

* `generateLegalMoves()`
* `isKingInCheck()`

After this milestone, the engine will be able to correctly determine game-ending positions before moving on to advanced rules such as en passant, promotion, and draw detection.