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

##### Piece-Square Tables

* Pawn Piece-Square Tables
* Knight Piece-Square Tables
* Bishop Piece-Square Tables
* Rook Piece-Square Tables
* Queen Piece-Square Tables
* King Piece-Square Tables

##### Positional Evaluation

* Passed Pawn Detection
* Rank-Based Passed Pawn Bonuses
* Bishop Pair Bonus
* Doubled Pawn Penalties
* Isolated Pawn Penalties

##### Search

* Minimax Search
* Alpha-Beta Pruning
* Basic Move Ordering (MVV-LVA)
* Mate Distance Scoring
* Best Move Search (`findBestMove`)
* Node Counting / Search Statistics

### In Progress

* UCI Protocol Support

### Planned

* Iterative Deepening
* Transposition Tables

## Current Status

The engine currently supports all standard chess rules and legal move generation.

Capabilities include:

* Loading positions from FEN strings
* Generating legal moves for all pieces
* Executing legal moves on the board
* Detecting attacks, checks, checkmates, and stalemates
* Handling castling, en passant, and promotions
* Evaluating positions using both material and positional factors
* Applying Piece-Square Table evaluation for all chess pieces
* Detecting and rewarding passed pawns
* Rewarding bishop pair ownership
* Penalizing doubled pawns
* Penalizing isolated pawns
* Searching positions using Minimax
* Optimizing search using Alpha-Beta Pruning
* Ordering moves using MVV-LVA
* Preferring faster checkmates and delaying unavoidable losses
* Selecting the best move from a given position
* Tracking node counts for performance analysis

### Search Improvements

Performance improvements implemented:

#### Alpha-Beta Pruning

* Reduced node count from **9322 → 586** on the starting position depth-3 benchmark

#### Move Ordering (MVV-LVA)

* Reduced node count from **1271 → 340** on tactical capture positions

#### Mate Distance Scoring

* Prefers mate in 1 over mate in 2
* Delays unavoidable losses whenever possible

### Evaluation Improvements

#### Knight Piece-Square Tables

* Encourages central knight development
* Improved opening move selection
* Changed preferred opening development from **Na3** to **Nc3**

#### Pawn Piece-Square Tables

* Rewards pawn advancement
* Rewards central pawn presence
* Encourages stronger positional play

#### Bishop Piece-Square Tables

* Rewards active bishops
* Rewards central and diagonal control
* Penalizes passive bishop placement

#### Rook Piece-Square Tables

* Encourages active rook placement
* Slightly rewards central files
* Provides groundwork for future open-file evaluation

#### Queen Piece-Square Tables

* Encourages central queen activity
* Slightly discourages edge and corner placement
* Maintains conservative queen development bonuses

#### King Piece-Square Tables

* Encourages king safety
* Rewards castled king positions
* Penalizes exposed central kings

#### Passed Pawn Evaluation

* Detects passed pawns
* Rewards passed pawns based on advancement
* Increases promotion pressure in endgames

#### Bishop Pair Bonus

* Rewards ownership of both bishops
* Improves evaluation of open positions
* Encourages preservation of the bishop pair

#### Doubled Pawn Evaluation

* Detects doubled pawns
* Penalizes multiple pawns occupying the same file
* Encourages healthier pawn structures

#### Isolated Pawn Evaluation

* Detects isolated pawn files
* Penalizes pawns lacking support from adjacent files
* Improves pawn structure assessment

## Future Improvements / Backlog

### Evaluation

* Mobility Evaluation

  * Prefer pseudo-legal move counting for performance
  * Requires dedicated pseudo-legal move generation

* Pawn Chain Evaluation

* Endgame-Specific Evaluation

* Open File Evaluation

* Semi-Open File Evaluation

* Connected Rook Evaluation

### Search

* Iterative Deepening
* Transposition Tables (Zobrist Hashing)
* Killer Move Heuristic
* History Heuristic
* Quiescence Search
* Principal Variation Search (PVS)

### Engine Infrastructure

* UCI Protocol Support
* FEN Export
* PGN Parsing
* Perft Testing Suite
* Search Benchmarking Utilities
* Time Management

### Optimization

* Bitboards (Long-Term Refactor)
* Incremental Evaluation
* Incremental Move Generation
* Optimized Move Ordering
* Multi-Threaded Search

## Next Milestone

Implement:

* UCI Protocol Support

Goals:

* Communicate with standard chess GUIs
* Support Arena, CuteChess, and BanksiaGUI
* Enable automated engine testing
* Provide a foundation for future web integration

After this milestone, the engine will be compatible with standard chess GUI software and ready for external testing, benchmarking, engine-vs-engine matches, and future web-based integration.