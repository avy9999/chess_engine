# Avy Chess Engine

Avy is a chess engine built from scratch in modern C++. It supports legal move generation, FEN loading, make/undo search, positional evaluation, alpha-beta search, quiescence search, iterative deepening, and UCI communication.

The project is currently focused on building a correct classical chess engine first, then improving strength through better search, evaluation, opening books, and eventually a playable web interface.

---

## Highlights

- Complete legal move generation
- Check, checkmate, and stalemate detection
- Castling, en passant, and pawn promotion
- FEN parsing
- Make/undo move system
- Incremental king tracking
- Material and positional evaluation
- Piece-square tables
- Alpha-beta search
- Quiescence search
- Iterative deepening
- MVV-LVA capture ordering
- Principal variation move preference
- Mate distance scoring
- UCI support
- Perft and divide debugging tools
- Automated perft regression suite

---

## Project Structure

```text
chess_engine/
  include/
    position.h        Board state and game metadata
    move.h            Move representation
    movegenerator.h   Legal move generation and make/undo
    evaluator.h       Evaluation interface
    search.h          Search interface
    perft.h           Perft and perft test runner
    uci.h             UCI loop interface

  src/
    main.cpp          Starts the UCI loop
    position.cpp      Board setup and FEN parsing
    move.cpp          Move constructors and comparison
    movegenerator.cpp Piece moves, legal filtering, make/undo
    evaluator.cpp     Material, PST, and positional scoring
    search.cpp        Alpha-beta, quiescence, iterative deepening
    perft.cpp         Perft, divide support, regression positions
    uci.cpp           UCI command handling

  docs/
    design.md
    perft_positions.md
```

---

## Build

From the project directory:

```powershell
cmake --build build --config Debug
```

Run the debug executable:

```powershell
.\build\Debug\chess_engine.exe
```

Run the release executable:

```powershell
.\build\Release\chess_engine.exe
```

---

## UCI Commands

Implemented commands:

```text
uci
isready
ucinewgame
quit
position startpos
position startpos moves ...
position fen ...
position fen ... moves ...
go depth N
go
perft N
divide N
perfttest
```

The engine has been tested with BanksiaGUI.

---

## Perft Testing

Perft is used to verify move generation correctness. It counts all legal leaf positions at a given depth.

Example:

```text
position startpos
perft 1
perft 2
perft 3
perft 4
perft 5
```

Expected start position results:

```text
perft 1 = 20
perft 2 = 400
perft 3 = 8902
perft 4 = 197281
perft 5 = 4865609
```

Use `divide` to debug mismatches by printing the node count for each legal root move:

```text
position startpos
divide 3
```

Run the automated regression suite:

```text
perfttest
```

Current regression coverage includes:

- Start position
- Kiwipete
- White en passant
- Black en passant
- White promotion
- Black promotion
- White castling
- Black castling
- Castling blocked by attack

The expected positions are documented in `docs/perft_positions.md`.

---

## Evaluation

Avy's evaluation currently includes:

- Standard material values
- Pawn piece-square table
- Knight piece-square table
- Bishop piece-square table
- Rook piece-square table
- Queen piece-square table
- King piece-square table
- Bishop pair bonus
- Doubled pawn penalties
- Isolated pawn penalties
- Simple development bonus
- Light castling and king-safety scoring

---

## Search

Implemented search features:

- Alpha-beta pruning
- Quiescence search
- Iterative deepening
- MVV-LVA capture ordering
- Principal variation move preference
- Mate distance scoring
- Search statistics and node counting
- Make/undo move search path

---

## Current Status

Avy can play complete legal chess through UCI and can search positions to a fixed depth. The core move generator has passed manual and automated perft checks for standard and rule-focused positions.

The next development focus is engine strength and usability:

1. Keep expanding automated perft coverage.
2. Add stronger UCI time management.
3. Add an opening book.
4. Improve search with transposition tables and move-ordering heuristics.
5. Improve evaluation with mobility, king safety, and endgame knowledge.
6. Build a web interface for playing against the engine.

---

## Roadmap

### Engine Correctness

- More perft positions
- FEN export
- PGN parsing
- Dedicated test runner outside the UCI loop

### UCI Infrastructure

- `go movetime`
- `go infinite`
- `stop`
- `setoption`
- Full time-control handling

### Opening Book

- Simple text or JSON opening book
- Opening line matching from move history
- Popular opening move selection
- Later support for PGN import or Polyglot books

### Search Improvements

- Zobrist hashing
- Transposition tables
- Killer move heuristic
- History heuristic
- Principal Variation Search
- Negamax refactor
- Aspiration windows

### Evaluation Improvements

- Mobility evaluation
- Pawn chains
- Passed pawn scaling
- Open and semi-open files
- Connected rooks
- Rook activity
- Better king safety
- Endgame evaluation

### Long-Term Goals

- Incremental evaluation
- Bitboards
- Multi-threaded search
- Web backend for engine play
- Browser-based chess UI
