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
* Checkmate Detection
* Stalemate Detection

### In Progress

* En Passant
* Pawn Promotion

## Current Status

The engine can currently:

* Load positions from FEN strings
* Generate legal moves for all pieces
* Execute moves on the board
* Detect attacked squares
* Detect checks
* Detect checkmate positions
* Detect stalemate positions
* Filter illegal moves that leave the king in check
* Generate and execute castling moves
* Track and update castling rights
* Validate castling legality according to chess rules

## Next Milestone

Implement:

* En Passant
* Pawn Promotion

using:

* Move generation
* Move execution
* Position state tracking

After this milestone, the engine will support all standard chess moves and special move rules, providing a complete legal move generation system.