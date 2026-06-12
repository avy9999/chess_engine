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
* Check Detection (`isKingInCheck`)
* Legal Move Generation

### In Progress

* Castling
* En Passant

### Planned

* Checkmate Detection
* Stalemate Detection
* Evaluation Function
* Minimax Search
* Alpha-Beta Pruning
* Move Ordering
* UCI Support

## Current Status

The engine can currently:

* Load positions from FEN strings
* Generate pseudo-legal moves for all chess pieces
* Generate legal moves by filtering out moves that leave the king in check
* Execute moves on the board
* Detect attacked squares
* Detect checks
* Handle pinned pieces correctly through legal move validation

## Next Milestone

Implement special chess moves:

* Castling
* En Passant

After that:

* Checkmate Detection
* Stalemate Detection