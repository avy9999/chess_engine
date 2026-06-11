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

### In Progress

* Check Detection

### Planned

* Castling
* En Passant
* Legal Move Generation
* Checkmate Detection
* Stalemate Detection
* Evaluation Function
* Minimax Search
* Alpha-Beta Pruning
* Move Ordering
* UCI Support

## Current Status

The engine can:

* Load positions from FEN strings
* Generate pseudo-legal moves for all pieces
* Execute moves on the board
* Detect whether a square is attacked by a given side
* Generate all available moves for the side to move

## Next Milestone

Implement check detection using:

* `isSquareAttacked()`
* King location tracking
* Legal move validation
