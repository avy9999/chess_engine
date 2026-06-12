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
* Square Attack Detection (`isSquareAttacked`)
* Move Generation Refactoring
* Utility Functions for Piece Handling
* Check Detection

### In Progress

* Legal Move Generation

### Planned

* Castling
* En Passant
* Checkmate Detection
* Stalemate Detection
* Evaluation Function
* Minimax Search
* Alpha-Beta Pruning
* Move Ordering
* UCI Support

## Current Status

The engine can currently:

- Load positions from FEN strings
- Generate pseudo-legal moves for all pieces
- Execute moves on the board
- Detect whether a square is attacked
- Detect whether a king is in check
- Generate all pseudo-legal moves for the side to move

## Next Milestone

Implement check detection using:

* `isSquareAttacked()`
* King location tracking
* Legal move validation
